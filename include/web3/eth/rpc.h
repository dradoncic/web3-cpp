#pragma once

#include <jsonrpccxx/client.hpp>
#include <nlohmann/json.hpp>
#include <string>

#include "core/client.h"
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
    std::string chainId();
    std::string gasPrice();

    type::response::Block getBlockByNumber(uint64_t number);
    type::response::Block getBlockByHash(const std::string& hash);

    std::string getBlockTransactionCountByNumber(uint64_t number);
    std::string getBlockTransactionCountByHash(const std::string& hash);

    type::response::Transaction getTransactionByHash(const std::string& hash);
    type::response::Receipt getTransactionReceipt(const std::string& hash);

    std::string getBalance(const type::request::Address& s);
    std::string getTransactionCount(const type::request::Address& s);

    std::string estimateGas(const type::request::Transaction& t);
    std::string sendRawTransaction(const type::request::Transaction& t);

   protected:
    jsonrpccxx::JsonRpcClient client_;
    rpc::HTTPClient& connector_;
};

}  // namespace web3::eth
