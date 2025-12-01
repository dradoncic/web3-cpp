#pragma once
#include <string>

#pragma once
#include <string>

namespace web3::rpc
{
class IConnector
{
   public:
    virtual ~IConnector() = default;
    virtual std::string send(const std::string& request) = 0;
};
}  // namespace web3::rpc
