#pragma once
#include <map>
#include <string>
#include <vector>

namespace web3::type
{
struct uint256;
class address;
using bytes = std::vector<uint8_t>;
}  // namespace web3::type

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

web3::type::uint256 toWei(const web3::type::uint256& amount,
                          const std::string& unit = "ether");
web3::type::uint256 fromWei(const web3::type::uint256& wei,
                            const std::string& unit = "ether");

// Hex/Bytes Utilities
bool isHex(const std::string& hex);
web3::type::bytes hexToBytes(const std::string& hex);
std::string bytesToHex(const web3::type::bytes& bytes);
std::string ensureHexPrefix(const std::string& hex);
std::string removeHexPrefix(const std::string& hex);
std::string padLeft(const std::string& hex, size_t length);
std::string stripLeadingZeros(const std::string& hex);
web3::type::bytes concat(const web3::type::bytes& a,
                         const web3::type::bytes& b);

// Keccak Hash
std::string keccak256(const web3::type::bytes& data);

// Signing & Address
std::string privateKeyToPublicKey(const std::string& privateKey);
web3::type::address publicKeyToAddress(const std::string& publicKey);
web3::type::address privateKeyToAddress(const std::string& privateKey);

// RLP Encoding
web3::type::bytes rlpEncode(const web3::type::bytes& input);
web3::type::bytes rlpEncodeList(const std::vector<web3::type::bytes>& inputs);

// ABI Encoding Helpers
std::string encodeFunctionSelector(const std::string& signature);
std::string encodeUint(web3::type::uint256& value);
std::string encodeAddress(const web3::type::address& address);
std::string encodeBool(bool val);
std::string encodeBytes(std::vector<uint8_t> bytes);
}  // namespace web3::utils
