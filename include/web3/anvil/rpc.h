#pragma once

#include <jsonrpccxx/client.hpp>
#include <nlohmann/json.hpp>
#include <string>

#include "eth/rpc.h"
#include "types/request.h"

namespace web3::anvil
{

class RPC : public eth::RPC
{
   public:
    using eth::RPC::RPC;

    void setBalance(const type::request::Balance balance);
    void dropTransaction(const std::string& hash);
};

}  // namespace web3::anvil
