#pragma once

#include <cpp-httplib/httplib.h>

#include <jsonrpccxx/client.hpp>
#include <jsonrpccxx/iclientconnector.hpp>
#include <string>

namespace web3::rpc {

class HTTPClient : public jsonrpccxx::IClientConnector
{
   public:
    explicit HTTPClient(const std::string& host, int port)
        : client(host.c_str(), port) {};

    std::string Send(const std::string& request) override
    {
        auto res = client.Post("/jsonrpc", request, "application/json");
        if (!res || res->status != 200)
        {
            throw jsonrpccxx::JsonRpcException(
                -32003, "Client Connection Error - Recieved Status Not 200 ");
        }
        return res->body;
    }

   private:
    httplib::Client client;
};

} // namespace web3::rpc
