#pragma once

#include <jsonrpccxx/client.hpp>
#include <nlohmann/json.hpp>
#include <string>

#include "rpc/client.h"
#include "types/request.h"
#include "types/response.h"

namespace web3::eth
{

class RPC
{
   public:
    explicit RPC(web3::rpc::HTTPClient& connector)
        : connector_{connector},
          client_{jsonrpccxx::JsonRpcClient(connector, jsonrpccxx::version::v2)}
    {
    }

    std::string blockNumber();
    web3::type::response::Block getBlock(const std::string& blockNumber);
    web3::type::response::Transaction getTransaction(const std::string& hash);

    web3::type::response::Account getAccount(
        const web3::type::request::GetInfo& s);
    std::string getBalance(const web3::type::request::GetInfo& s);
    std::string getTransactionCount(const web3::type::request::GetInfo& s);

    std::string estimateGas(const web3::type::request::Transaction& t);
    std::string gasPrice();

    std::string sendTransaction(const std::string& t);
    std::string call(const web3::type::request::Transaction& t);

   protected:
    jsonrpccxx::JsonRpcClient client_;
    web3::rpc::HTTPClient connector_;
};

}  // namespace web3::eth
