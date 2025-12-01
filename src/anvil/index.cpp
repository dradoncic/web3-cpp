#include "anvil/index.h"

namespace web3::anvil
{

Anvil::Anvil(RPC& rpc) : rpc_{rpc}, accounts_{}
{
}

RPC& Anvil::rpc()
{
    return rpc_;
}

eth::Accounts& Anvil::accounts()
{
    return accounts_;
}

eth::Contract Anvil::contract(const std::string& address, nlohmann::json& abi)
{
    return eth::Contract(address, abi, rpc_);
}

}  // namespace web3::anvil
