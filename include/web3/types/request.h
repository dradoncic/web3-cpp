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

    uint8_t type;
    uint256 nonce;
    address to;
    address from;
    uint256 gas;
    uint256 value;
    bytes input;
    uint256 gasPrice;
    uint256 maxPriorityFeePerGas;
    uint256 maxFeePerGas;
    uint256 maxFeePerBlobGas;
    std::vector<response::AccessList> accessList;
    std::vector<web3::type::uint256> blobVersionedHashes;
    web3::type::uint256 chainId;
    std::vector<response::AuthorizationList> authorizationList;

    // Legacy Transaction
    Transaction(const uint256& nonce, const uint256& gasPrice, const uint256& gas,
                const address& to, const address& from, const uint256& value,
                const bytes& input = {})
        : from(from),
          type(0),
          nonce(nonce),
          gasPrice(gasPrice),
          gas(gas),
          to(to),
          value(value),
          input(input)
    {
    }

    // EIP-2930 Transaction
    Transaction(const uint256& nonce, const uint256& gasPrice, const uint256& gas,
                const address& to, const address& from, const uint256& value,
                const std::vector<response::AccessList>& accessList,
                const uint256& chainId, const bytes& input = {})
        : from(from),
          type(1),
          chainId(chainId),
          nonce(nonce),
          gasPrice(gasPrice),
          gas(gas),
          to(to),
          value(value),
          input(input),
          accessList(accessList)
    {
    }

    // EIP-1559 Transaction
    Transaction(const uint256& nonce, const uint256& gas, const address& to,
                const address& from, const uint256& value,
                const std::vector<response::AccessList>& accessList,
                const uint256& chainId, const uint256& maxPriorityFeePerGas,
                const uint256& maxFeePerGas, const bytes& input = {})
        : from(from),
          type(2),
          chainId(chainId),
          nonce(nonce),
          maxPriorityFeePerGas(maxPriorityFeePerGas),
          maxFeePerGas(maxFeePerGas),
          gas(gas),
          to(to),
          value(value),
          input(input),
          accessList(accessList)
    {
    }

    // EIP-4844 Transaction
    Transaction(const uint256& nonce, const uint256& gas, const address& to,
                const address& from, const uint256& value,
                const std::vector<response::AccessList>& accessList,
                const uint256& chainId, const uint256& maxPriorityFeePerGas,
                const uint256& maxFeePerGas, const uint256& maxFeePerBlobGas,
                const std::vector<uint256>& blobVersionedHashes,
                const bytes& input = {})
        : from(from),
          type(3),
          chainId(chainId),
          nonce(nonce),
          maxPriorityFeePerGas(maxPriorityFeePerGas),
          maxFeePerGas(maxFeePerGas),
          gas(gas),
          to(to),
          value(value),
          input(input),
          accessList(accessList),
          maxFeePerBlobGas(maxFeePerBlobGas),
          blobVersionedHashes(blobVersionedHashes)
    {
    }

    // EIP-7702 Transaction
    Transaction(const uint256& nonce, const uint256& gas, const address& to,
                const address& from, const uint256& value,
                const std::vector<response::AccessList>& accessList,
                const uint256& chainId, const uint256& maxPriorityFeePerGas,
                const uint256& maxFeePerGas,
                const std::vector<response::AuthorizationList>& authorizationList,
                const bytes& input = {})
        : from(from),
          type(4),
          chainId(chainId),
          nonce(nonce),
          maxPriorityFeePerGas(maxPriorityFeePerGas),
          maxFeePerGas(maxFeePerGas),
          gas(gas),
          to(to),
          value(value),
          input(input),
          accessList(accessList),
          authorizationList(authorizationList)
    {
    }
};

struct Address
{
    address address;
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

    put("address", b.address.toHex());
    put("block", b.block);
}

struct Balance
{
    address address;
    uint256 balance; // amount of wei
};

inline void to_json(nlohmann::json& j, const Balance& b)
{
    j = nlohmann::json{};

    auto put = [&](const char* key, const std::string& value)
    {
        if (!value.empty())
            j[key] = value;
    };

    put("address", b.address.toHex());
    put("balance", b.balance.toHex());
}

}  // namespace web3::type::request
