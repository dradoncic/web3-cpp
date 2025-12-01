#pragma once

#include <types/response.h>

#include <nlohmann/json.hpp>
#include <string>

#include "utils.h"
#include "types/native.h"

namespace web3::type::request
{

struct Transaction
{
    std::string type = {};
    std::string nonce;
    std::string to = {};
    std::string from;
    std::string gas = {};
    std::string value = {};
    std::string input = {};
    std::string gasPrice = {};
    std::string maxPriorityFeePerGas = {};
    std::string maxFeePerGas = {};
    std::string maxFeePerBlobGas = {};
    std::vector<response::AccessList> accessList = {};
    std::vector<std::string> blobVersionedHashes = {};
    std::vector<std::string> blobs = {};
    std::string chainId = {};
    std::vector<response::AuthorizationList> authorizationList = {};

    // Legacy Transaction
    Transaction(const uint256& nonce, const uint256& gasPrice, const uint256& gas,
                const std::string& to, const std::string& from, const uint256& value,
                const std::string& input = {})
        : from(from),
          type(uint256(0).toHex()),
          nonce(nonce.toHex()),
          gasPrice(gasPrice.toHex()),
          gas(gas.toHex()),
          to(to),
          value(value.toHex()),
          input(input)
    {
    }

    // EIP-2930 Transaction
    Transaction(const uint256& nonce, const uint256& gasPrice, const uint256& gas,
                const std::string& to, const std::string& from, const uint256& value,
                const std::vector<response::AccessList>& accessList,
                const uint256& chainId, const std::string& input = {})
        : from(from),
          type(uint256(1).toHex()),
          chainId(chainId.toHex()),
          nonce(nonce.toHex()),
          gasPrice(gasPrice.toHex()),
          gas(gas.toHex()),
          to(to),
          value(value.toHex()),
          input(input),
          accessList(accessList)
    {
    }

    // EIP-1559 Transaction
    Transaction(const uint256& nonce, const uint256& gas, const std::string& to,
                const std::string& from, const uint256& value,
                const std::vector<response::AccessList>& accessList,
                const uint256& chainId, const uint256& maxPriorityFeePerGas,
                const uint256& maxFeePerGas, const std::string& input = {})
        : from(from),
          type(uint256(2).toHex()),
          chainId(chainId.toHex()),
          nonce(nonce.toHex()),
          maxPriorityFeePerGas(maxPriorityFeePerGas.toHex()),
          maxFeePerGas(maxFeePerGas.toHex()),
          gas(gas.toHex()),
          to(to),
          value(value.toHex()),
          input(input),
          accessList(accessList)
    {
    }

    // EIP-4844 Transaction
    Transaction(const uint256& nonce, const uint256& gas, const std::string& to,
                const std::string& from, const uint256& value,
                const std::vector<response::AccessList>& accessList,
                const uint256& chainId, const uint256& maxPriorityFeePerGas,
                const uint256& maxFeePerGas, const uint256& maxFeePerBlobGas,
                const std::vector<std::string>& blobVersionedHashes,
                const std::string& input = {})
        : from(from),
          type(uint256(3).toHex()),
          chainId(chainId.toHex()),
          nonce(nonce.toHex()),
          maxPriorityFeePerGas(maxPriorityFeePerGas.toHex()),
          maxFeePerGas(maxFeePerGas.toHex()),
          gas(gas.toHex()),
          to(to),
          value(value.toHex()),
          input(input),
          accessList(accessList),
          maxFeePerBlobGas(maxFeePerBlobGas.toHex()),
          blobVersionedHashes(blobVersionedHashes)
    {
    }

    // EIP-7702 Transaction
    Transaction(const uint256& nonce, const uint256& gas, const std::string& to,
                const std::string& from, const uint256& value,
                const std::vector<response::AccessList>& accessList,
                const uint256& chainId, const uint256& maxPriorityFeePerGas,
                const uint256& maxFeePerGas,
                const std::vector<response::AuthorizationList>& authorizationList,
                const std::string& input = {})
        : from(from),
          type(uint256(4).toHex()),
          chainId(chainId.toHex()),
          nonce(nonce.toHex()),
          maxPriorityFeePerGas(maxPriorityFeePerGas.toHex()),
          maxFeePerGas(maxFeePerGas.toHex()),
          gas(gas.toHex()),
          to(to),
          value(value.toHex()),
          input(input),
          accessList(accessList),
          authorizationList(authorizationList)
    {
    }
};

struct Address
{
    std::string address;
    std::string block = "latest";
};

inline void to_json(nlohmann::json& j, const Address& b)
{
    j = nlohmann::json{};

    auto put = [&](const char* key, const std::string& value)
    {
        if (!value.empty())
            j[key] = value;
    };

    put("address", b.address);
    put("block", b.block);
}

struct Balance
{
    std::string address;
    std::string balance;
};

inline void to_json(nlohmann::json& j, const Balance& b)
{
    j = nlohmann::json{};

    auto put = [&](const char* key, const std::string& value)
    {
        if (!value.empty())
            j[key] = value;
    };

    put("address", b.address);
    put("balance", b.balance);
}

}  // namespace web3::type::request
