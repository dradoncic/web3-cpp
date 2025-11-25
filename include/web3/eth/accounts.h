#pragma once

#include <map>
#include <string>

#include "types/request.h"

namespace web3::eth
{

class Wallet
{
   public:
    void add(const web3::type::request::Account& account);
    void remove(const std::string& address);
    void clear();

    web3::type::request::Account get(const std::string& address);
    const std::map<std::string, web3::type::request::Account> getAll() const;

   private:
    std::map<std::string, web3::type::request::Account> accounts_;
};

class Account
{
   public:
    web3::type::request::Account create();
    web3::type::request::Account privateKeyToAccount(
        const std::string& privateKey);

    std::string signTransaction(const web3::type::request::Transaction& tx,
                                const std::string& privateKey);

    Wallet& wallet()
    {
        return wallet_;
    };

   private:
    Wallet wallet_;
};

}  // namespace web3::eth
