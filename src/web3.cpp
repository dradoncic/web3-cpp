#include "web3.h"

#include <stdexcept>

web3::Web3::Web3(const std::string& host, int port, web3::RPCType type)
    : type_{type},
      connector_{host, port},
      eth_rpc_{connector_},
      anvil_rpc_{connector_},
      eth_{eth_rpc_},
      anvil_{anvil_rpc_}
{
}

web3::eth::Eth& web3::Web3::eth()
{
    if (type_ != web3::RPCType::Ethereum)
        throw std::runtime_error(
            "Web3 was initialized with RPCType::Anvil. Cannot access eth() "
            "API.");
    return eth_;
}

web3::anvil::Anvil& web3::Web3::anvil()
{
    if (type_ != web3::RPCType::Anvil)
        throw std::runtime_error(
            "Web3 was initialized with RPCType::Ethereum. Cannot access anvil() "
            "API.");
    return anvil_;
}
