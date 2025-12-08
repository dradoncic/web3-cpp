#pragma once
#include <gmpxx.h>

#include <array>
#include <string>
#include <vector>

namespace web3::type
{

class uint256
{
   public:
    mpz_class v;

    uint256() : v(0)
    {
    }
    uint256(uint64_t x)
    {
        mpz_set_ui(v.get_mpz_t(), x);
    }
    uint256(const std::string& s, int base = 10) : v(s, base)
    {
    }
    uint256(const mpz_class& x) : v(x)
    {
    }

    std::string toHex() const
    {
        return "0x" + v.get_str(16);
    }

    std::string toDec() const
    {
        return v.get_str(10);
    }

    uint64_t toU64() const
    {
        return v.get_ui();
    }

    uint256 operator+(const uint256& o) const
    {
        mpz_class x = v + o.v;
        return uint256(x.get_str());
    }

    uint256 operator-(const uint256& o) const
    {
        if (o.v > v)
            throw std::runtime_error("uint256 underflow");
        mpz_class x = v - o.v;
        return uint256(x.get_str());
    }

    uint256 operator*(const uint256& o) const
    {
        mpz_class x = v * o.v;
        return uint256(x.get_str());
    }

    uint256 operator/(const uint256& o) const
    {
        mpz_class x = v / o.v;
        return uint256(x.get_str());
    }

    uint256 operator%(const uint256& o) const
    {
        mpz_class x = v % o.v;
        return uint256(x.get_str());
    }

    uint256& operator+=(const uint256& o)
    {
        v += o.v;
        return *this;
    }

    uint256& operator-=(const uint256& o)
    {
        if (o.v > v)
            throw std::runtime_error("uint256 underflow");
        v -= o.v;
        return *this;
    }

    // shifts
    uint256 operator<<(size_t c) const
    {
        mpz_class r;
        mpz_mul_2exp(r.get_mpz_t(), v.get_mpz_t(), c);
        return uint256(r.get_str());
    }

    uint256 operator>>(size_t c) const
    {
        mpz_class r;
        mpz_div_2exp(r.get_mpz_t(), v.get_mpz_t(), c);
        return uint256(r.get_str());
    }

    // comparisons
    bool operator<(const uint256& o) const
    {
        return v < o.v;
    }
    bool operator>(const uint256& o) const
    {
        return v > o.v;
    }
    bool operator<=(const uint256& o) const
    {
        return v <= o.v;
    }
    bool operator>=(const uint256& o) const
    {
        return v >= o.v;
    }
    bool operator==(const uint256& o) const
    {
        return v == o.v;
    }
    bool operator!=(const uint256& o) const
    {
        return v != o.v;
    }

    uint256 operator&(const uint256 o) const
    {
        mpz_class x = v & o.v;
        return uint256(x.get_str());
    }
};

class address
{
   public:
    std::array<uint8_t, 20> bytes;

    address()
    {
        bytes.fill(0);
    }

    explicit address(const std::array<uint8_t, 20>& b) : bytes(b)
    {
    }

    explicit address(const std::string& hex);

    std::string toHex() const;

    std::string toChecksumAddress() const;

    bool operator==(const address& other) const
    {
        return bytes == other.bytes;
    }
    bool operator!=(const address& other) const
    {
        return !(*this == other);
    }
};

using bytes = std::vector<uint8_t>;

}  // namespace web3::type
