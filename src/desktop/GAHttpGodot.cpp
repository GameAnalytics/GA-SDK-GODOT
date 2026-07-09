#include "GAHttpGodot.h"

#include <cstring>

#include <godot_cpp/classes/http_client.hpp>
#include <godot_cpp/classes/os.hpp>
#include <godot_cpp/classes/time.hpp>
#include <godot_cpp/classes/tls_options.hpp>
#include <godot_cpp/variant/packed_byte_array.hpp>
#include <godot_cpp/variant/packed_string_array.hpp>

using namespace godot;

namespace gameanalytics
{
    namespace
    {
        struct ParsedUrl
        {
            bool useTls = false;
            String host;
            int port = -1;
            String path;
        };

        ParsedUrl parseUrl(std::string const& url)
        {
            ParsedUrl parsed;
            std::string rest = url;

            if(rest.rfind("https://", 0) == 0)
            {
                parsed.useTls = true;
                rest = rest.substr(8);
            }
            else if(rest.rfind("http://", 0) == 0)
            {
                rest = rest.substr(7);
            }

            auto pathPos = rest.find('/');
            std::string hostPort = pathPos == std::string::npos ? rest : rest.substr(0, pathPos);
            std::string path = pathPos == std::string::npos ? "/" : rest.substr(pathPos);

            auto colonPos = hostPort.find(':');
            if(colonPos == std::string::npos)
            {
                parsed.host = hostPort.c_str();
            }
            else
            {
                parsed.host = hostPort.substr(0, colonPos).c_str();
                parsed.port = std::atoi(hostPort.substr(colonPos + 1).c_str());
            }

            parsed.path = path.c_str();
            return parsed;
        }

        // polls the client until the predicate is satisfied or timeoutSeconds elapses
        bool pollUntil(Ref<HTTPClient> const& client, bool (*isDone)(HTTPClient::Status), double timeoutSeconds)
        {
            uint64_t deadline = Time::get_singleton()->get_ticks_msec() + (uint64_t)(timeoutSeconds * 1000.0);
            while(!isDone(client->get_status()))
            {
                if(Time::get_singleton()->get_ticks_msec() > deadline)
                {
                    return false;
                }
                client->poll();
                OS::get_singleton()->delay_msec(10);
            }
            return true;
        }
    }

    void GAHttpGodot::initialize()
    {
    }

    void GAHttpGodot::cleanup()
    {
    }

    GAHttpClient::Response GAHttpGodot::sendRequest(
        std::string const& url,
        std::string const& auth,
        std::vector<uint8_t> const& payloadData,
        bool useGzip,
        void* userData)
    {
        (void)userData;

        Response response;
        ParsedUrl parsed = parseUrl(url);

        Ref<HTTPClient> client;
        client.instantiate();

        Ref<TLSOptions> tlsOptions = parsed.useTls ? TLSOptions::client() : Ref<TLSOptions>();

        if(client->connect_to_host(parsed.host, parsed.port, tlsOptions) != OK)
        {
            return response;
        }

        bool connected = pollUntil(client, [](HTTPClient::Status status)
        {
            return status != HTTPClient::STATUS_RESOLVING && status != HTTPClient::STATUS_CONNECTING;
        }, 15.0);

        if(!connected || client->get_status() != HTTPClient::STATUS_CONNECTED)
        {
            client->close();
            return response;
        }

        PackedByteArray body;
        body.resize((int64_t)payloadData.size());
        if(!payloadData.empty())
        {
            memcpy(body.ptrw(), payloadData.data(), payloadData.size());
        }

        PackedStringArray headers;
        headers.append("Content-Type: application/json");
        if(!auth.empty())
        {
            // auth is already a full "Authorization: <value>" header line
            headers.append(auth.c_str());
        }
        if(useGzip)
        {
            headers.append("Content-Encoding: gzip");
        }

        if(client->request_raw(HTTPClient::METHOD_POST, parsed.path, headers, body) != OK)
        {
            client->close();
            return response;
        }

        bool requested = pollUntil(client, [](HTTPClient::Status status)
        {
            return status != HTTPClient::STATUS_REQUESTING;
        }, 30.0);

        if(!requested || !client->has_response())
        {
            client->close();
            return response;
        }

        response.code = client->get_response_code();

        while(client->get_status() == HTTPClient::STATUS_BODY)
        {
            client->poll();
            PackedByteArray chunk = client->read_response_body_chunk();
            if(chunk.size() == 0)
            {
                OS::get_singleton()->delay_msec(1);
                continue;
            }
            const uint8_t* ptr = chunk.ptr();
            response.packet.insert(response.packet.end(), ptr, ptr + chunk.size());
        }

        client->close();
        return response;
    }
}
