#pragma once

#include <string>

#include <nlohmann/json.hpp>

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


struct Account
{
    std::string address;
    std::string privateKey;
};


struct Standard
{
    std::string address;
    std::string block = "latest";
};

inline void to_json(nlohmann::json& j, const Standard& b)
{
    j = nlohmann::json{
        {"address", b.address},
        {"block", b.block}
    };
}

inline void from_json(const nlohmann::json& j, Standard& b)
{
    j.at("address").get_to(b.address);
    j.at("block").get_to(b.block);
}




}  // namespace web3::type::request
