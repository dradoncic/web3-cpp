#pragma once

#include <utils.h>

#include <nlohmann/json.hpp>
#include <string>

namespace web3::type::request
{

// empty fields are by default 0x80
struct Transaction
{
    std::string nonce;
    std::string to;
    std::string from;
    std::string gas;
    std::string gasPrice;
    std::string value;
    std::string input;
    std::string chainId;

    Transaction(const std::string& from, const std::string& to, uint64_t value,
                uint64_t nonce, uint64_t chainId, uint64_t gasPrice,
                uint64_t gas = 21000, const std::string& input = {})
        : from(from),
          to(to),
          value(web3::utils::intToHex(value)),
          nonce(web3::utils::intToHex(nonce)),
          chainId(web3::utils::intToHex(chainId)),
          gasPrice(web3::utils::intToHex(gasPrice)),
          gas(web3::utils::intToHex(gas)),
          input(input)
    {
    }

    Transaction(const std::string& from, const std::string& to, uint64_t value,
                const std::string input = {})
        : from(from),
          to(to),
          value(web3::utils::intToHex(value)),
          nonce(""),
          chainId(""),
          gasPrice(""),
          gas(""),
          input(input)
    {
    }
};

inline void to_json(nlohmann::json& j, const Transaction& t)
{
    j = nlohmann::json{};

    auto put = [&](const char* key, const std::string& value)
    {
        if (!value.empty())
            j[key] = value;
    };

    put("nonce", t.nonce);
    put("to", t.to);
    put("from", t.from);
    put("gas", t.gas);
    put("gasPrice", t.gasPrice);
    put("value", t.value);
    put("input", t.input);
    put("chainId", t.chainId);
}

struct Account
{
    std::string address;
    std::string privateKey;
    uint64_t nonce = 0;
};

struct GetInfo
{
    std::string address;
    std::string block = "latest";
};

inline void to_json(nlohmann::json& j, const GetInfo& b)
{
    j = nlohmann::json{{"address", b.address}, {"block", b.block}};
}

struct SetBalance
{
    std::string address;
    std::string balance;
};

inline void to_json(nlohmann::json& j, const SetBalance& b)
{
    j = nlohmann::json{{"address", b.address}, {"balance", b.balance}};
}

inline void from_json(const nlohmann::json& j, SetBalance& b)
{
    j.at("address").get_to(b.address);
    j.at("balance").get_to(b.balance);
}

}  // namespace web3::type::request
