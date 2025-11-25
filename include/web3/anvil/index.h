#pragma once

#include "anvil/rpc.h"
#include "eth/accounts.h"
#include "eth/contract.h"

namespace web3::anvil
{

class Anvil
{
   public:
    Anvil(RPC& rpc);

    RPC& rpc();

    web3::eth::Accounts& accounts();

    web3::eth::Contract contract(const std::string& address,
                                 nlohmann::json& abi);

   private:
    RPC rpc_;
    web3::eth::Accounts accounts_;
};

}  // namespace web3::anvil
