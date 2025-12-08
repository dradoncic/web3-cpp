#include "utils.h"

#include <cryptopp/eccrypto.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/integer.h>
#include <cryptopp/keccak.h>
#include <cryptopp/oids.h>
#include <cryptopp/osrng.h>
#include <gmpxx.h>

#include <cctype>
#include <stdexcept>

#include "types/native.h"

namespace web3::utils
{

type::uint256 toWei(const type::uint256& amount, const std::string& unit)
{
    auto it = unitMap.find(unit);
    if (it == unitMap.end())
        throw std::runtime_error("Unknown unit: " + unit);

    mpz_class factor = 1;
    mpz_ui_pow_ui(factor.get_mpz_t(), 10, static_cast<int>(it->second));
    return type::uint256(amount.v * factor);
}

type::uint256 fromWei(const type::uint256& amount, const std::string& unit)
{
    auto it = unitMap.find(unit);
    if (it == unitMap.end())
        throw std::runtime_error("Unknown unit: " + unit);

    mpz_class factor = 1;
    mpz_ui_pow_ui(factor.get_mpz_t(), 10, static_cast<int>(it->second));
    return type::uint256(amount.v / factor);
}

bool isHex(const std::string& hex)
{
    std::string hex_n = removeHexPrefix(hex);
    if (hex_n.empty())
        return false;

    return std::all_of(hex_n.begin(), hex_n.end(),
                       [](unsigned char c) { return std::isxdigit(c); });
}

std::string ensureHexPrefix(const std::string& hex)
{
    if (hex.size() >= 2 && hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X'))
        return hex;
    return "0x" + hex;
}

std::string removeHexPrefix(const std::string& hex)
{
    if (hex.size() >= 2 && hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X'))
        return hex.substr(2);
    return hex;
}

type::bytes hexToBytes(const std::string& hex)
{
    std::string hex_n = removeHexPrefix(hex);
    if (hex_n.size() & 1)
        hex_n = "0" + hex_n;

    type::bytes out(hex_n.size() / 2);

    CryptoPP::StringSource ss(hex_n, true,
                              new CryptoPP::HexDecoder(new CryptoPP::ArraySink(
                                  out.data(), out.size())));

    return out;
}

std::string bytesToHex(const type::bytes& bytes)
{
    std::string hex;
    CryptoPP::HexEncoder encoder(new CryptoPP::StringSink(hex), false);

    encoder.Put(bytes.data(), bytes.size());
    encoder.MessageEnd();

    return "0x" + hex;
}

std::string padLeft(const std::string& hex, size_t length)
{
    auto hex_n = removeHexPrefix(hex);
    hex_n.insert(0, length - hex_n.size(), '0');
    return "0x" + hex_n;
}

std::string stripLeadingZeros(const std::string& hex)
{
    auto hex_n = removeHexPrefix(hex);
    auto pos = hex_n.find_first_not_of('0');
    if (pos == std::string::npos)
        return "0x0";
    return "0x" + hex_n.substr(pos);
}

type::bytes concat(const type::bytes& a, const type::bytes& b)
{
    type::bytes out = a;
    out.insert(out.end(), b.begin(), b.end());
    return out;
}

/**
 * @brief Computes the Keccak-256 hash of the given data.
 *
 * This function takes a vector of bytes as input and returns
 * the Keccak-256 hash of the data as a hexadecimal string
 * prefixed with "0x".
 *
 * @param data A vector of bytes to hash.
 * @return std::string The Keccak-256 hash as a "0x"-prefixed hexadecimal
 * string.
 *
 * @note Uses Crypto++ library's Keccak_256 implementation.
 *
 * @example
 * std::vector<uint8_t> myData = {0x01, 0x02, 0x03};
 * std::string hash = keccak256(myData);
 * // hash = "0x..." (64 hex characters)
 */
std::string keccak256(const type::bytes& data)
{
    CryptoPP::Keccak_256 hash;

    std::vector<uint8_t> digest(32);
    hash.Update(data.data(), data.size());
    hash.TruncatedFinal(digest.data(), digest.size());

    return bytesToHex(digest);
}

std::string privateKeyToPublicKey(const std::string& privateKey)
{
    // auto privBytes = hexToBytes(privateKey);
    // if (privBytes.size() != 32)
    //     throw std::runtime_error("Invalid private key length!");

    // CryptoPP::Integer privBigInt(privBytes.data(), privBytes.size());

    // CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PrivateKey priv;
    // priv.Initialize(CryptoPP::ASN1::secp256k1(), privBigInt);

    // CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PublicKey pub;
    // priv.MakePublicKey(pub);

    // const CryptoPP::ECP::Point& Q = pub.GetPublicElement();
    // std::vector<uint8_t> pubBytes;
    // pubBytes.resize(64);
    // Q.x.Encode(pubBytes.data(), 32);
    // Q.y.Encode(pubBytes.data() + 32, 32);

    // return bytesToHex(pubBytes);
}

type::address publicKeyToAddress(const std::string& publicKey)
{
    auto pubBytes = hexToBytes(publicKey);
    if (pubBytes.size() != 64)
        throw std::runtime_error("Invalid public key length.");

    CryptoPP::Keccak_256 hash;

    std::vector<uint8_t> digest(32);
    hash.Update(pubBytes.data(), pubBytes.size());
    hash.TruncatedFinal(digest.data(), digest.size());

    type::address addr;
    std::copy(digest.end() - 20, digest.end(), addr.bytes.begin());
    return addr;
}

type::address privateKeyToAddress(const std::string& privateKey)
{
    return publicKeyToAddress(privateKeyToPublicKey(privateKey));
}

type::bytes uint256ToBytes(const type::uint256& value)
{
    type::bytes bytes(32);

    mpz_export(bytes.data(),        // output buffer
               nullptr,             // number of limbs written (can ignore)
               1,                   // most significant word first
               1,                   // size of each word in bytes
               1,                   // big-endian within each word
               0,                   // no nails
               value.v.get_mpz_t()  // GMP integer
    );

    return bytes;
}

namespace sign
{

Signature signHash(const std::string& privKey, const std::string& hash)
{

}

}


// type::bytes rlpEncode(const type::bytes& input)
// {
//     size_t len = input.size();
//     type::bytes out;
//     if (len == 0)
//         out.push_back(0x80);
//     else if (len == 1 && input[0] <= 0x7f)
//         out.push_back(input[0]);
//     else if (len <= 55)
//     {
//         out.push_back(0x80 + len);
//         out.insert(out.end(), input.begin(), input.end());
//     }
//     else
//     {
//         type::bytes lenBytes = uint256ToBytes(type::uint256(len));
//         // remove leading zeros
//         auto pos = std::find_if(lenBytes.begin(), lenBytes.end(),
//                                 [](uint8_t b) { return b != 0; });
//         lenBytes = type::bytes(pos, lenBytes.end());
//         out.push_back(0xB7 + lenBytes.size());
//         out.insert(out.end(), lenBytes.begin(), lenBytes.end());
//         out.insert(out.end(), input.begin(), input.end());
//     }
//     return out;
// }

// type::bytes rlpEncodeList(const std::vector<type::bytes>& inputs)
// {
//     type::bytes encoded;
//     for (const auto& item : inputs)
//     {
//         auto e = rlpEncode(item);
//         encoded.insert(encoded.end(), e.begin(), e.end());
//     }

//     size_t len = encoded.size();
//     type::bytes out;
//     if (len <= 55)
//     {
//         out.push_back(0xC0 + len);
//     }
//     else
//     {
//         type::bytes lenBytes = uint256ToBytes(type::uint256(len));
//         auto pos = std::find_if(lenBytes.begin(), lenBytes.end(),
//                                 [](uint8_t b) { return b != 0; });
//         lenBytes = type::bytes(pos, lenBytes.end());
//         out.push_back(0xF7 + lenBytes.size());
//         out.insert(out.end(), lenBytes.begin(), lenBytes.end());
//     }
//     out.insert(out.end(), encoded.begin(), encoded.end());
//     return out;
// }


}  // namespace web3::utils
