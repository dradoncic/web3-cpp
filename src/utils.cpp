#include "utils.h"

#include <cctype>
#include <cryptopp/eccrypto.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/integer.h>
#include <cryptopp/keccak.h>
#include <cryptopp/oids.h>
#include <cryptopp/osrng.h>
#include <gmpxx.h>
#include <stdexcept>

namespace web3::utils
{

std::string BN::add(const std::string& a, const std::string& b, int base)
{
    mpz_class sum(a, base);
    sum += mpz_class(b, base);
    return sum.get_str(base);
}

std::string BN::sub(const std::string& a, const std::string& b, int base)
{
    mpz_class diff(a, base);
    diff -= mpz_class(b, base);
    return diff.get_str(base);
}

std::string BN::mul(const std::string& a, const std::string& b, int base)
{
    mpz_class prod(a, base);
    prod *= mpz_class(b, base);
    return prod.get_str(base);
}

std::string BN::div(const std::string& a, const std::string& b, int base)
{
    mpz_class quotient(a, base);
    quotient /= mpz_class(b, base);
    return quotient.get_str(base);
}

std::string toWei(const std::string& amount, const std::string& unit)
{
    auto it = unitMap.find(unit);
    if (it == unitMap.end())
        throw std::runtime_error("Unknown unit: " + unit);
    int exp = static_cast<int>(it->second);

    auto dotPos = amount.find('.');

    std::string intPart = (dotPos == std::string::npos) ? amount : amount.substr(0, dotPos);
    std::string fracPart = (dotPos == std::string::npos) ? "0" : amount.substr(dotPos + 1);

    if (fracPart.size() > static_cast<size_t>(exp))
        fracPart = fracPart.substr(0, exp);
    else
        fracPart.append(exp - fracPart.size(), '0');

    return intPart + fracPart;
}

std::string fromWei(const std::string& amount, const std::string& unit)
{
    auto it = unitMap.find(unit);
    if (it == unitMap.end())
        throw std::runtime_error("Unknown unit: " + unit);
    int exp = static_cast<int>(it->second);

    std::string result;
    if (amount.size() <= static_cast<size_t>(exp))
        result = "0." + std::string(exp - amount.size(), '0') + amount;
    else
        result = amount.substr(0, amount.size() - exp) + "." + amount.substr(amount.size() - exp);

    while (result.back() == '0')
        result.pop_back();
    if (result.back() == '.')
        result.pop_back();

    return result;
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

std::vector<uint8_t> hexToBytes(const std::string& hex)
{
    std::string hex_n = removeHexPrefix(hex);
    if (hex_n.size() & 1)
        hex_n = "0" + hex_n;

    std::vector<uint8_t> bytes(hex_n.size() / 2);

    CryptoPP::StringSource ss(
        hex_n, true, new CryptoPP::HexDecoder(new CryptoPP::ArraySink(bytes.data(), bytes.size())));

    return bytes;
}

std::string bytesToHex(const std::vector<uint8_t>& bytes)
{
    std::string hex;
    CryptoPP::HexEncoder encoder(new CryptoPP::StringSink(hex), false);

    encoder.Put(bytes.data(), bytes.size());
    encoder.MessageEnd();

    return "0x" + hex;
}

std::string hexToDec(const std::string& hex)
{
    if (!isHex(hex))
        return "0";
    mpz_class dec(removeHexPrefix(hex), 16);
    return dec.get_str();
}

std::string decToHex(const std::string& dec)
{
    mpz_class hex(dec);
    return "0x" + hex.get_str(16);
}

std::vector<uint8_t> decToBytes(const std::string& dec)
{
    std::string hex = decToHex(dec);
    return hexToBytes(hex);
}

std::string padLeft(const std::string& hex, size_t length)
{
    auto hex_n = removeHexPrefix(hex);
    hex_n.insert(0, length - hex.size(), '0');
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

std::vector<uint8_t> concat(const std::vector<uint8_t>& a, const std::vector<uint8_t>& b)
{
    std::vector<uint8_t> newVec;
    newVec.insert(newVec.end(), a.begin(), a.end());
    newVec.insert(newVec.end(), b.begin(), b.end());
    return newVec;
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
std::string keccak256(const std::vector<uint8_t>& data)
{
    CryptoPP::Keccak_256 hash;

    std::vector<uint8_t> digest(32);
    hash.Update(data.data(), data.size());
    hash.TruncatedFinal(digest.data(), digest.size());

    return bytesToHex(digest);
}

std::string privateKeyToPublicKey(const std::string& privateKey)
{
    auto privBytes = hexToBytes(privateKey);
    if (privBytes.size() != 32)
        throw std::runtime_error("Invalid private key length!");

    CryptoPP::Integer privBigInt(privBytes.data(), privBytes.size());

    CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PrivateKey priv;
    priv.Initialize(CryptoPP::ASN1::secp256k1(), privBigInt);

    CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PublicKey pub;
    priv.MakePublicKey(pub);

    const CryptoPP::ECP::Point& Q = pub.GetPublicElement();
    std::vector<uint8_t> pubBytes;
    pubBytes.resize(64);
    Q.x.Encode(pubBytes.data(), 32);
    Q.y.Encode(pubBytes.data() + 32, 32);

    return bytesToHex(pubBytes);
}

std::string publicKeyToAddress(const std::string& publicKey)
{
    auto pubBytes = hexToBytes(publicKey);
    if (pubBytes.size() != 64)
        throw std::runtime_error("Invalid public key length.");

    CryptoPP::Keccak_256 hash;

    std::vector<uint8_t> digest(32);
    hash.Update(pubBytes.data(), pubBytes.size());
    hash.TruncatedFinal(digest.data(), digest.size());

    std::vector<uint8_t> addr(digest.end() - 20, digest.end());
    auto raw_addr = bytesToHex(addr);

    return toChecksumAddress(raw_addr);
}

std::vector<uint8_t> intToBytes(uint64_t value)
{
    if (value == 0)
        return {0x00};
    std::vector<uint8_t> bytes;
    while (value)
    {
        bytes.push_back(value & 0XFF);
        value >>= 8;
    }

    std::reverse(bytes.begin(), bytes.end());
    return bytes;
}

std::vector<uint8_t> rlpEncode(const std::vector<uint8_t>& input)
{
    auto len = input.size();
    std::vector<uint8_t> encoded;

    if (len == 0)
        encoded.push_back(0x80);
    else if (len == 1 && input[0] <= 0x7f)
        encoded.push_back(input[0]);
    else if (len <= 55)
    {
        encoded.push_back(0x80 + static_cast<uint8_t>(len));
        encoded.insert(encoded.end(), input.begin(), input.end());
    }
    else
    {
        auto lenBytes = intToBytes(len);
        encoded.push_back(0xB7 + static_cast<uint8_t>(lenBytes.size()));
        encoded.insert(encoded.end(), lenBytes.begin(), lenBytes.end());
        encoded.insert(encoded.end(), input.begin(), input.end());
    }
    return encoded;
}

std::vector<uint8_t> rlpEncodeList(const std::vector<std::vector<uint8_t>>& inputs)
{
    std::vector<uint8_t> encoded;
    for (auto& it : inputs)
    {
        auto encodedItem = rlpEncode(it);
        encoded.insert(encoded.end(), encodedItem.begin(), encodedItem.end());
    }

    size_t len = encoded.size();
    std::vector<uint8_t> res;

    if (len <= 55)
    {
        res.push_back(0xC0 + static_cast<uint8_t>(len));
        res.insert(res.end(), encoded.begin(), encoded.end());
    }
    else
    {
        auto lenBytes = intToBytes(len);
        res.push_back(0xF7 + static_cast<uint8_t>(lenBytes.size()));
        res.insert(res.end(), lenBytes.begin(), lenBytes.end());
        res.insert(res.end(), encoded.begin(), encoded.end());
    }

    return res;
}

bool isAddress(const std::string& address)
{
    auto addr = removeHexPrefix(address);

    if (addr.size() != 40)
        return false;

    return isHex(addr);
}

std::string toChecksumAddress(const std::string& address)
{
    auto addr = removeHexPrefix(address);
    std::transform(addr.begin(), addr.end(), addr.begin(), ::tolower);

    auto addrBytes = hexToBytes(addr);
    auto hashHex = removeHexPrefix(keccak256(addrBytes));

    for (auto i = 0; i < addr.size(); i++)
    {
        char c = addr[i];
        char h = hashHex[i];

        uint8_t hval = (h >= '0' && h <= '9') ? h - '0' : (tolower(h) - 'a' + 10);

        if (hval >= 8)
            addr[i] = toupper(c);
    }

    return ensureHexPrefix(addr);
}

} // namespace web3::utils
