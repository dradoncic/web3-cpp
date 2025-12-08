#pragma once
#include <map>
#include <string>
#include <vector>

#include "types/response.h"

namespace web3::type  // forward declaration
{
struct uint256;
class address;
using bytes = std::vector<uint8_t>;
}  // namespace web3::type

namespace web3::type::request  // forward declaration
{
class Transaction;
class Address;
}  // namespace web3::type::request

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

type::uint256 toWei(const web3::type::uint256& amount,
                    const std::string& unit = "ether");
type::uint256 fromWei(const web3::type::uint256& wei,
                      const std::string& unit = "ether");

// Hex/Bytes Utilities
bool isHex(const std::string& hex);
type::bytes hexToBytes(const std::string& hex);
std::string bytesToHex(const web3::type::bytes& bytes);
std::string ensureHexPrefix(const std::string& hex);
std::string removeHexPrefix(const std::string& hex);
std::string padLeft(const std::string& hex, size_t length);
std::string stripLeadingZeros(const std::string& hex);
type::bytes concat(const web3::type::bytes& a, const web3::type::bytes& b);

// Uint256 Utilities
type::bytes uint256ToBytes(const type::uint256& value);

// Keccak256 & secp256k1
std::string keccak256(const web3::type::bytes& data);

// Address
std::string privateKeyToPublicKey(const std::string& privateKey);
type::address publicKeyToAddress(const std::string& publicKey);
type::address privateKeyToAddress(const std::string& privateKey);

// Signing
namespace sign
{

std::string computeHash(const type::request::Transaction& tx);

struct Signature
{
    std::string r;
    std::string s;
    uint8_t yParity;
    uint8_t v;
};

Signature signHash(const std::string& privKey, const std::string& hash);

std::string buildSignedLegacy(const type::request::Transaction& tx,
                              const Signature& sig);
std::string buildSignedTyped(const type::request::Transaction& tx,
                             const Signature& sig);

type::bytes signTransaction(const type::request::Transaction& tx,
                            const std::string& privKey);
}  // namespace sign

// RLP Encoding
namespace rlp
{

type::bytes encodeBytes(const type::bytes& bytes);
type::bytes encodeUint256(const type::uint256& value);
type::bytes encodeAddress(const type::address& addr);
type::bytes encodeList(const std::vector<type::bytes>& items);
type::bytes encodeAccessList(
    const std::vector<type::response::AccessList>& accessList);
type::bytes encodeAuthorizationList(
    const std::vector<type::response::AuthorizationList>& authList);

type::bytes encodeLegacyTransaction(const type::request::Transaction& tx);
type::bytes encodeEIP2930Transaction(const type::request::Transaction& tx);
type::bytes encodeEIP1559Transaction(const type::request::Transaction& tx);
type::bytes encodeEIP4844Transaction(const type::request::Transaction& tx);
type::bytes encodeEIP7702Tranasction(const type::request::Transaction& tx);

type::bytes encodeTransaction(const type::request::Transaction& tx);
}  // namespace rlp

// web3::type::bytes rlpEncode(const web3::type::bytes& input);
// web3::type::bytes rlpEncodeList(const std::vector<web3::type::bytes>&
// inputs);

// ABI Encoding Helpers
std::string encodeFunctionSelector(const std::string& signature);
std::string encodeUint(web3::type::uint256& value);
std::string encodeAddress(const web3::type::address& address);
std::string encodeBool(bool val);
std::string encodeBytes(type::bytes bytes);
}  // namespace web3::utils
