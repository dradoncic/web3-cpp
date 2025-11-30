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

web3::eth::Accounts& Anvil::accounts()
{
    return accounts_;
}

web3::eth::Contract Anvil::contract(const std::string& address,
                                    nlohmann::json& abi)
{
    return web3::eth::Contract(address, abi, rpc_);
}

}  // namespace web3::anvil
