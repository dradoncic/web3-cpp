#include "eth/index.h"

namespace web3::eth
{

Eth::Eth(RPC& rpc) : rpc_{rpc}, accounts_{}
{
}

RPC& Eth::rpc()
{
    return rpc_;
}

Accounts& Eth::accounts()
{
    return accounts_;
}

Contract Eth::contract(const std::string& address, nlohmann::json& abi)
{
    return Contract(address, abi, rpc_);
}

}  // namespace web3::eth
