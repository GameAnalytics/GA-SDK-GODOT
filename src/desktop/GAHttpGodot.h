#pragma once

#include "GameAnalytics/GAHttpClient.h"

namespace gameanalytics
{
    class GAHttpGodot : public GAHttpClient
    {
        public:

            void initialize() override;

            void cleanup() override;

            Response sendRequest(
                std::string const& url,
                std::string const& auth,
                std::vector<uint8_t> const& payloadData,
                bool useGzip,
                void* userData) override;
    };
}
