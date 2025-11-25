#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace web3::utils
{

class BN
{
    static std::string add(const std::string& a, const std::string& b);
    static std::string sub(const std::string& a, const std::string& b);
    static std::string mul(const std::string& a, const std::string& b);
    static std::string div(const std::string& a, const std::string& b);
};

std::string toWei(const std::string& amount, const std::string& unit = "ether");
std::string fromWei(const std::string& wei, const std::string& unit = "ether");

std::string toHex(const std::string& str);
std::string hexToBytes(const std::string& hex);
std::string bytesToHex(const std::vector<uint8_t>& bytes);

std::string sha3(const std::string& data);
std::string keccak256(const std::string& data);

bool isAddress(const std::string& address);
bool isHexStrict(const std::string& hex);

std::string toChecksumAddress(const std::string& address);

}  // namespace web3::utils
