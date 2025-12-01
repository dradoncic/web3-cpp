#pragma once

#include <types/response.h>
#include <utils.h>

#include <nlohmann/json.hpp>
#include <string>

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
    Transaction(uint64_t nonce, uint64_t gasPrice, uint64_t gas,
                const std::string& to, const std::string& from, uint64_t value,
                const std::string& input = {})
        : from(from),
          type(utils::intToHex(0)),
          nonce(utils::intToHex(nonce)),
          gasPrice(utils::intToHex(gasPrice)),
          gas(utils::intToHex(gas)),
          to(to),
          value(utils::intToHex(value)),
          input(input)
    {
    }

    // EIP-2930 Transaction
    Transaction(uint64_t nonce, uint64_t gasPrice, uint64_t gas,
                const std::string& to, const std::string& from, uint64_t value,
                const std::vector<response::AccessList>& accessList,
                uint64_t chainId, const std::string& input = {})
        : from(from),
          type(utils::intToHex(1)),
          chainId(utils::intToHex(chainId)),
          nonce(utils::intToHex(nonce)),
          gasPrice(utils::intToHex(gasPrice)),
          gas(utils::intToHex(gas)),
          to(to),
          value(utils::intToHex(value)),
          input(input),
          accessList(accessList)
    {
    }

    // EIP-1559 Transaction
    Transaction(uint64_t nonce, uint64_t gas, const std::string& to,
                const std::string& from, uint64_t value,
                const std::vector<response::AccessList>& accessList,
                uint64_t chainId, uint64_t maxPriorityFeePerGas,
                uint64_t maxFeePerGas, const std::string& input = {})
        : from(from),
          type(utils::intToHex(2)),
          chainId(utils::intToHex(chainId)),
          nonce(utils::intToHex(nonce)),
          maxPriorityFeePerGas(utils::intToHex(maxPriorityFeePerGas)),
          maxFeePerGas(utils::intToHex(maxFeePerGas)),
          gas(utils::intToHex(gas)),
          to(to),
          value(utils::intToHex(value)),
          input(input),
          accessList(accessList)
    {
    }

    // EIP-4844 Transaction
    Transaction(uint64_t nonce, uint64_t gas, const std::string& to,
                const std::string& from, uint64_t value,
                const std::vector<response::AccessList>& accessList,
                uint64_t chainId, uint64_t maxPriorityFeePerGas,
                uint64_t maxFeePerGas, uint64_t maxFeePerBlobGas,
                const std::vector<std::string>& blobVersionedHashes,
                const std::string& input = {})
        : from(from),
          type(utils::intToHex(3)),
          chainId(utils::intToHex(chainId)),
          nonce(utils::intToHex(nonce)),
          maxPriorityFeePerGas(utils::intToHex(maxPriorityFeePerGas)),
          maxFeePerGas(utils::intToHex(maxFeePerGas)),
          gas(utils::intToHex(gas)),
          to(to),
          value(utils::intToHex(value)),
          input(input),
          accessList(accessList),
          maxFeePerBlobGas(utils::intToHex(maxFeePerBlobGas)),
          blobVersionedHashes(blobVersionedHashes)
    {
    }

    // EIP-7702 Transaction
    Transaction(
        uint64_t nonce, uint64_t gas, const std::string& to,
        const std::string& from, uint64_t value,
        const std::vector<response::AccessList>& accessList, uint64_t chainId,
        uint64_t maxPriorityFeePerGas, uint64_t maxFeePerGas,
        const std::vector<response::AuthorizationList>& authorizationList,
        const std::string& input = {})
        : from(from),
          type(utils::intToHex(4)),
          chainId(utils::intToHex(chainId)),
          nonce(utils::intToHex(nonce)),
          maxPriorityFeePerGas(utils::intToHex(maxPriorityFeePerGas)),
          maxFeePerGas(utils::intToHex(maxFeePerGas)),
          gas(utils::intToHex(gas)),
          to(to),
          value(utils::intToHex(value)),
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
