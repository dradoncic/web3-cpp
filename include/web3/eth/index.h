#pragma once

#include "eth/accounts.h"
#include "eth/contract.h"
#include "eth/rpc.h"

namespace web3::eth
{

class Eth
{
public:
    explicit Eth(RPC& rpc);

    RPC& rpc();

    Accounts& accounts();

    Contract contract(const std::string& address, nlohmann::json& abi);

private:
    RPC& rpc_;
    Accounts accounts_;
};

} // namespace web3::eth
