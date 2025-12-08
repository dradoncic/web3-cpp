#pragma once
#include <map>
#include <string>
#include <vector>

#include "types/native.h"
#include "types/request.h"
#include "types/response.h"

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
type::bytes keccak256(const web3::type::bytes& data);

// Address
type::bytes privateKeyToPublicKey(const std::string& privateKey);
type::address publicKeyToAddress(const type::bytes& publicKey);
type::address privateKeyToAddress(const std::string& privateKey);

// Signing
namespace sign
{

struct Signature
{
    std::string r;
    std::string s;
    uint8_t yParity;
};

Signature signHash(const std::string& privKey, const type::bytes& hash);

std::string buildSignedLegacy(const type::request::Transaction& tx,
                              const Signature& sig);
std::string buildSignedTyped(const type::request::Transaction& tx,
                             const Signature& sig);

type::bytes signTransaction(const std::vector<type::bytes>& items,
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

std::vector<type::bytes> encodeLegacyTransaction(
    const type::request::Transaction& tx);
std::vector<type::bytes> encodeEIP2930Transaction(
    const type::request::Transaction& tx);
std::vector<type::bytes> encodeEIP1559Transaction(
    const type::request::Transaction& tx);
std::vector<type::bytes> encodeEIP4844Transaction(
    const type::request::Transaction& tx);
std::vector<type::bytes> encodeEIP7702Transaction(
    const type::request::Transaction& tx);

std::vector<type::bytes> getEncodedTransactionItems(
    const type::request::Transaction& tx);
type::bytes encodeTransactionFromItems(const std::vector<type::bytes>& items);
}  // namespace rlp

// web3::type::bytes rlpEncode(const web3::type::bytes& input);
// web3::type::bytes rlpEncodeList(const std::vector<web3::type::bytes>&
// inputs);

// ABI Encoding Helpers
type::bytes encodeFunctionSelector(const std::string& signature);
type::bytes encodeUint(web3::type::uint256& value);
type::bytes encodeAddress(const web3::type::address& address);
type::bytes encodeBool(bool val);
type::bytes encodeBytes(type::bytes bytes);
}  // namespace web3::utils
