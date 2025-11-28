#pragma once

#include <curl/curl.h>
#include <jsonrpccxx/iclientconnector.hpp>
#include <string>

namespace web3::rpc
{

class HTTPClient : public jsonrpccxx::IClientConnector
{
public:
    HTTPClient(const std::string& host, int port);

    ~HTTPClient() override;

    std::string Send(const std::string& request) override;

private:
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);

    std::string host_;
    int port_;
};

} // namespace web3::rpc
