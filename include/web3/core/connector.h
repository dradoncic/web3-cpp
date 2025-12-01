#pragma once

#include <curl/curl.h>

#include <string>

#include "core/iconnector.h"

namespace web3::rpc
{

class HTTPClient : public IConnector
{
   public:
    HTTPClient(const std::string& host, int port);

    ~HTTPClient() override;

    std::string send(const std::string& request) override;

   private:
    static size_t writeCallback(void* contents, size_t size, size_t nmemb,
                                void* userp);

    std::string host_;
    int port_;
};

}  // namespace web3::rpc
