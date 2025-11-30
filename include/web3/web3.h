#pragma once

#include "anvil/index.h"
#include "eth/index.h"

namespace web3
{

enum class RPCType
{
    Ethereum,
    Anvil
};

class Web3
{
   public:
    explicit Web3(const std::string& host, int port, RPCType type);

    eth::Eth& eth();

    anvil::Anvil& anvil();

    RPCType type() const
    {
        return type_;
    }

   private:
    RPCType type_;
    web3::rpc::HTTPClient connector_;

    web3::eth::RPC eth_rpc_;
    web3::anvil::RPC anvil_rpc_;

    eth::Eth eth_;
    anvil::Anvil anvil_;
};

}  // namespace web3
