#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <cstdint>

namespace gameanalytics
{ 
    class GAHttpClient
    {
        public:

            struct Response
            {
                long code = -1;
                std::vector<uint8_t> packet;
                
                inline std::string_view toString() const
                {
                    if(packet.empty()) return {};
                    return std::string_view((const char*)packet.data(), packet.size());
                }
            };

            virtual ~GAHttpClient() {};

            virtual void initialize() = 0;

            virtual void cleanup() = 0;

            virtual Response sendRequest(
                std::string const& url, 
                std::string const& auth,
                std::vector<uint8_t> const& payloadData, 
                bool useGzip,
                void* userData) = 0;
    };
    
} // namespace gameanalytics
