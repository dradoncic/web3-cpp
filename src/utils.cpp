#include "utils.h"

#include <gmpxx.h>

#include <array>
#include <cctype>
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

    std::string intPart =
        (dotPos == std::string::npos) ? amount : amount.substr(0, dotPos);
    std::string fracPart =
        (dotPos == std::string::npos) ? "0" : amount.substr(dotPos + 1);

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
        result = amount.substr(0, amount.size() - exp) + "." +
                 amount.substr(amount.size() - exp);

    while (result.back() == '0')
        result.pop_back();
    if (result.back() == '.')
        result.pop_back();

    return result;
}

bool isHex(const std::string& hex)
{
    if (hex.size() < 3) return false;
    if (hex[0] != '0' || (hex[1] != 'x' && hex[1] != 'X')) return false;

    return std::all_of(hex.begin() + 2, hex.end(), [](unsigned char c){ return std::isxdigit(c); });
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
    std::vector<uint8_t> bytes;
    if (!isHex(hex)) return bytes;

    std::string hex_n = removeHexPrefix(hex);
    if (hex_n.size() % 2 != 0) hex_n = "0" + hex_n;

    for (size_t i = 0; i < hex_n.size(); i += 2)
    {
        uint8_t byte =
            static_cast<uint8_t>(std::stoi(hex_n.substr(i, 2), nullptr, 16));
        bytes.push_back(byte);
    }

    return bytes;
}

std::string bytesToHex(const std::vector<uint8_t> bytes)
{
    static const char* hex_chars = "0123456789ABCDEF";
    std::string hex;
    hex.reserve(bytes.size() * 2);

    for (auto byte : bytes)
    {
        hex += hex_chars[(byte >> 4) & 0x0F];
        hex += hex_chars[(byte & 0x0F)];
    }

    return "0x" + hex;
}

std::string hexToDec(const std::string& hex)
{
    if (!isHex(hex)) return "0";
    mpz_class dec(removeHexPrefix(hex), 16);
    return dec.get_str();
}

std::string decToHex(const std::string& dec)
{
    mpz_class hex(dec);
    return "0x" + hex.get_str(16);
}

std::string padLeft(const std::string& hex, size_t length)
{
    auto hex_n = removeHexPrefix(hex);
    if (hex_n.size() < length) hex_n.insert(0, length - hex.size(), '0');
    return "0x" + hex_n;
}

std::string stripLeadingZeros(const std::string& hex)
{
    auto hex_n = removeHexPrefix(hex);
    auto pos = hex_n.find_first_not_of('0');
    if (pos == std::string::npos) return "0x0";
    return "0x" + hex_n.substr(pos);
}

}  // namespace web3::utils
