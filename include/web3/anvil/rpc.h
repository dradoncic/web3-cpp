#pragma once

#include <jsonrpccxx/client.hpp>
#include <nlohmann/json.hpp>
#include <string>

#include "eth/rpc.h"
#include "types/request.h"

namespace web3::anvil
{

class RPC : public web3::eth::RPC
{
   public:
    using web3::eth::RPC::RPC;

    void setBalance(const web3::type::request::SetBalance balance);
    void dropTransaction(const std::string& hash);
};

}  // namespace web3::anvil
