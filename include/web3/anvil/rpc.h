#pragma once

#include <jsonrpccxx/client.hpp>
#include <nlohmann/json.hpp>
#include <string>

#include "eth/rpc.h"

namespace web3::anvil
{

class RPC : public web3::eth::RPC
{
   public:
    RPC(web3::rpc::HTTPClient& connector) : web3::eth::RPC(connector)
    {
    }

    void setBalance(const std::string& address, const std::string& amount);
    void dropTransaction(const std::string& hash);
};

}  // namespace web3::anvil
