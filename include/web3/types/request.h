#pragma once

#include <nlohmann/json.hpp>
#include <string>

namespace web3::type::request
{

struct Transaction
{
    std::string from;
    std::string to;
    std::string gas;
    std::string gasPrice;
    std::string value;
    std::string data;
    std::string nonce;
};

inline void to_json(nlohmann::json& j, const Transaction& t)
{
    j = nlohmann::json{{"from", t.from},   {"to", t.to},
                       {"gas", t.gas},     {"gasPrice", t.gasPrice},
                       {"value", t.value}, {"data", t.data},
                       {"nonce", t.nonce}};
}

inline void from_json(const nlohmann::json& j, Transaction& t)
{
    j.at("from").get_to(t.from);
    j.at("to").get_to(t.to);
    j.at("gas").get_to(t.gas);
    j.at("gasPrice").get_to(t.gasPrice);
    j.at("value").get_to(t.value);
    j.at("data").get_to(t.data);
    j.at("nonce").get_to(t.nonce);
}

struct Account
{
    std::string address;
    std::string privateKey;
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

inline void from_json(const nlohmann::json& j, GetInfo& b)
{
    j.at("address").get_to(b.address);
    j.at("block").get_to(b.block);
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
