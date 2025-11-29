#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace web3::utils
{

enum class Unit
{
    WEI = 1,
    GWEI = 9,
    ETHER = 18
};

inline std::map<std::string, Unit> unitMap = {
    {"wei", Unit::WEI}, {"gwei", Unit::GWEI}, {"ether", Unit::ETHER}};

class BN
{
public:
    static std::string add(const std::string& a, const std::string& b, int base = 10);
    static std::string sub(const std::string& a, const std::string& b, int base = 10);
    static std::string mul(const std::string& a, const std::string& b, int base = 10);
    static std::string div(const std::string& a, const std::string& b, int base = 10);
};

std::string toWei(const std::string& amount, const std::string& unit = "ether");
std::string fromWei(const std::string& wei, const std::string& unit = "ether");

bool isHex(const std::string& hex);
std::vector<uint8_t> hexToBytes(const std::string& hex);
std::string bytesToHex(const std::vector<uint8_t>& bytes);
std::string ensureHexPrefix(const std::string& hex);
std::string removeHexPrefix(const std::string& hex);
std::string hexToDec(const std::string& hex);
std::string decToHex(const std::string& dec);
std::vector<uint8_t> decToBytes(const std::string& dec);

std::string padLeft(const std::string& hex, size_t length);
std::string stripLeadingZeros(const std::string& hex);
std::vector<uint8_t> concat(const std::vector<uint8_t>& a, const std::vector<uint8_t>& b);

std::string keccak256(const std::vector<uint8_t>& data);

std::string sign(const std::string& msg, const std::string& privateKey);
int recoverV(std::string hash, std::string signature);

std::vector<uint8_t> rlpEncode(const std::vector<uint8_t>& input);
std::vector<uint8_t> rlpEncodeList(const std::vector<std::vector<uint8_t>>& inputs);
std::vector<uint8_t> intToBytes(uint64_t value);

bool isAddress(const std::string& address);
std::string toChecksumAddress(const std::string& address);

std::string encodeFunctionSelector(const std::string& signature);
std::string encodeUint(uint64_t value);
std::string encodeAddress(const std::string& address);
std::string encodeBool(bool val);
std::string encodeBytes(std::vector<uint8_t> bytes);

std::string privateKeyToPublicKey(const std::string& privateKey);
std::string publicKeyToAddress(const std::string& publicKey);
std::string privateKeyToAddres(const std::string& privateKey);
} // namespace web3::utils
