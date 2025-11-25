#pragma once

#include "eth/index.h"
#include "anvil/index.h"

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

private:
    eth::Eth eth_;
    anvil::Anvil anvil_;
    rpc::HTTPClient connector_;
};


}
