#include "types/native.h"

#include "utils.h"

namespace web3::type
{

address::address(const std::string& hex)
{
    auto b = utils::hexToBytes(hex);
    if (b.size() != 20)
        throw std::runtime_error("Invalid address length");
    std::copy(b.begin(), b.end(), bytes.begin());
}

std::string address::toHex() const
{
    return utils::bytesToHex(std::vector<uint8_t>(bytes.begin(), bytes.end()));
}

std::string address::toChecksumAddress() const
{
    std::string addr = web3::utils::removeHexPrefix(toHex());

    auto hashHex = web3::utils::keccak256(
        std::vector<uint8_t>(bytes.begin(), bytes.end()));

    for (size_t i = 0; i < addr.size(); i++)
    {
        uint8_t hval = (hashHex[i] >= '0' && hashHex[i] <= '9')
                           ? hashHex[i] - '0'
                           : (tolower(hashHex[i]) - 'a' + 10);
        if (hval >= 8)
            addr[i] = toupper(addr[i]);
        else
            addr[i] = tolower(addr[i]);
    }

    return web3::utils::ensureHexPrefix(addr);
}
}  // namespace web3::type
