#include "utils.h"

#include <gmpxx.h>

#include <cctype>
#include <stdexcept>
#include <array>

namespace web3::utils
{

std::string BN::add(const std::string& a, const std::string& b)
{
    mpz_class sum(a);
    sum += mpz_class(b);
    return sum.get_str();
}

std::string BN::sub(const std::string& a, const std::string& b)
{
    mpz_class diff(a);
    diff -= mpz_class(b);
    return diff.get_str();
}

std::string BN::mul(const std::string& a, const std::string& b)
{
    mpz_class prod(a);
    prod *= mpz_class(b);
    return prod.get_str();
}

std::string BN::div(const std::string& a, const std::string& b)
{
    mpz_class quotient(a);
    quotient /= mpz_class(b);
    return quotient.get_str();
}

std::string toWei(const std::string& amount, const std::string& unit)
{
    auto it = unitMap.find(unit);
    if (it == unitMap.end())
        throw std::runtime_error("Unknonw unit: " + unit);
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
        throw std::runtime_error("Unknonw unit: " + unit);
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
    if (hex.size() < 3)
        return false;
    if (hex[0] != '0' || (hex[1] != 'x' && hex[1] != 'X'))
        return false;

    for (auto i = 2; i < hex.size(); ++i)
    {
        char c = hex[i];
        if (!std::isxdigit(static_cast<unsigned char>(c)))
            return false;
    }
    return true;
}

std::vector<uint8_t> hexToBytes(const std::string& hex)
{
    std::vector<uint8_t> bytes;

    if (!isHex(hex))
        return bytes;

    auto hex_n = removeHexPrefix(hex);
    if (hex_n.size() % 2 != 0)
        hex_n = "0" + hex_n;

    for (size_t i = 0; i < hex_n.size(); i += 2)
    {
        uint8_t byte =
            static_cast<uint8_t>(std::stoi(hex.substr(i, 2), nullptr, 16));
        bytes.push_back(byte);
    }

    return bytes;
}

std::string bytesToHex(const std::vector<uint8_t> bytes)
{
    static const std::array<char, 16> hex_chars = {'0', '1', '2', '3', '4', '5',
                                                   '6', '7', '8', '9', 'A', 'B',
                                                   'C', 'D', 'E', 'F'};
    std::string hex;
    hex.reserve(bytes.size() * 2);

    for (auto byte : bytes)
    {
        hex += hex_chars[(byte >> 4) & 0x0F];
        hex += hex_chars[(byte >> 0x0F)];
    }

    return hex;
}

std::string ensureHexPrefix(const std::string &hex)
{
    if (hex.size() >= 2 && hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X'))
        return hex;
    return "0x" + hex;
}

std::string removeHexPrefix(const std::string &hex)
{
    if (hex.size() >= 2 && hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X'))
        return hex.substr(2);
    return hex;
}

}  // namespace web3::utils
