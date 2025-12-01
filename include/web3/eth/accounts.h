#pragma once

#include <map>
#include <string>

#include "types/native.h"
#include "types/request.h"

namespace web3::eth
{

struct Account
{
    type::address address;
    std::string privateKey;
    uint64_t nonce = 0;

    Account() = default;
    Account(const type::address& addr, const std::string& privKey,
            uint64_t nonce = 0)
        : address(addr), privateKey(privKey), nonce(nonce)
    {
    }

    std::string checksumAddress() const
    {
        return address.toChecksumAddress();
    }
};

class Wallet
{
   public:
    void add(const Account& account);
    void remove(const std::string& address);
    void clear();

    Account get(const std::string& address);
    const std::map<std::string, Account> getAll() const;

   private:
    std::map<std::string, Account> accounts_;
};

class Accounts
{
   public:
    Account create();
    Account privateKeyToAccount(const std::string& privateKey);

    std::string signTransaction(const type::request::Transaction& tx,
                                const std::string& privateKey);

    Wallet& wallet()
    {
        return wallet_;
    };

   private:
    Wallet wallet_;
};

}  // namespace web3::eth
