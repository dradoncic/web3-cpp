#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "eth/rpc.h"

namespace web3::eth
{

class ContractMethod
{
public:
    ContractMethod(const std::string& name, const nlohmann::json& abi, web3::eth::RPC& rpc);

    ContractMethod& param(const std::string& value);
    ContractMethod& params(const std::vector<std::string>& values);

    std::string call(const std::string& to, const std::string& from = "");
    std::string send(const std::string& from, const std::string& to, const std::string& value = "0",
                     const std::string& gas = "");

private:
    void reset();
    std::string encodeFunctionCall();
    std::string getFunctionSelector();

    std::string name_;
    std::string stateMutability_;
    nlohmann::json abi_;
    web3::eth::RPC& rpc_;
    std::vector<std::string> parameters_;
};

class Contract
{
public:
    Contract(const std::string& address, const nlohmann::json& abi, web3::eth::RPC& rpc);

    ContractMethod methods(const ::std::string& name);

    static std::string deploy(const nlohmann::json& abi, const std::string& bytecode,
                              const std::string& from, web3::eth::RPC& rpc);

    std::string address() const;

private:
    std::string address_;
    nlohmann::json abi_;
    web3::eth::RPC& rpc;
};

} // namespace web3::eth
