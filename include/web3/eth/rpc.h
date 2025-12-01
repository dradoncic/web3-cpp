#pragma once

#include <nlohmann/json.hpp>
#include <optional>
#include <string>

#include "core/client.h"
#include "core/connector.h"
#include "types/request.h"
#include "types/response.h"

namespace web3::eth
{

class RPC
{
   public:
    explicit RPC(rpc::HTTPClient& connector)
        : connector_{connector}, client_{rpc::JsonRPCClient(connector)}
    {
    }

    std::string blockNumber();
    std::string chainId();
    std::string gasPrice();

    std::optional<type::response::Block> getBlockByNumber(uint64_t number);
    std::optional<type::response::Block> getBlockByHash(
        const std::string& hash);

    std::optional<std::string> getBlockTransactionCountByNumber(
        uint64_t number);
    std::optional<std::string> getBlockTransactionCountByHash(
        const std::string& hash);

    std::optional<type::response::Transaction> getTransactionByHash(
        const std::string& hash);
    std::optional<type::response::Receipt> getTransactionReceipt(
        const std::string& hash);

    std::string getBalance(const type::request::Address& s);
    std::string getTransactionCount(const type::request::Address& s);

    std::string estimateGas(const type::request::Transaction& t);
    std::string sendRawTransaction(const std::string& signedTx);

   protected:
    rpc::JsonRPCClient client_;
    rpc::HTTPClient& connector_;
};

}  // namespace web3::eth
