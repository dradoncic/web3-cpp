#pragma once

#include <map>
#include <string>

#include "web3/types.h"

namespace web3::eth
{

class Wallet
{
   public:
    void add(const web3::Account& account);
    void remove(const std::string& address);
    void clear();

    web3::Account get(const std::string& address);
    const std::map<std::string, web3::Account> getAll() const;

   private:
    std::map<std::string, web3::Account> accounts_;
};

class Account
{
   public:
    web3::Account create();
    web3::Account privateKeyToAccount(const std::string& privateKey);

    std::string sign(const std::string& data, const std::string& privateKey);
    std::string signTransaction(const web3::Transaction& tx,
                                const std::string& privateKey);

    Wallet& wallet()
    {
        return wallet_;
    };

   private:
    Wallet wallet_;
};

}  // namespace web3::eth
