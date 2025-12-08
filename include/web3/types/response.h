#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "types/native.h"

namespace web3::type::response
{

struct AccessList
{
    type::address address;
    std::vector<std::string> storageKeys = {};
};

inline void from_json(const nlohmann::json& j, AccessList& a)
{
    a.address = address(j.value("address", ""));
    a.storageKeys = j.value("storageKeys", std::vector<std::string>{});
}

struct AuthorizationList
{
    type::uint256 chainId;
    type::uint256 nonce;
    type::address address;
    uint8_t yParity;
    std::string r;
    std::string s;
};

inline void from_json(const nlohmann::json& j, AuthorizationList& a)
{
    a.chainId = j.value("chainId", "");
    a.nonce = j.value("nonce", "");
    a.address = address(j.value("address", ""));
    a.yParity = j.at("yParity").get<uint8_t>();
    a.r = j.value("r", "");
    a.s = j.value("s", "");
}

struct Transaction
{
    std::string blockHash = {};
    std::string blockNumber = {};
    std::string from = {};
    std::string transactionIndex = {};
    std::string type;
    std::string nonce;
    std::string to = {};
    std::string gas;
    std::string value;
    std::string input;
    std::string maxPriorityFeePerGas = {};
    std::string maxFeePerGas = {};
    std::string maxFeePerBlobGas = {};
    std::string gasPrice;
    std::vector<AccessList> accessList = {};
    std::vector<std::string> blobVersionedHashes = {};
    std::string chainId = {};
    std::string yParity = {};
    std::string r;
    std::string s;
    std::string v = {};
};

inline void from_json(const nlohmann::json& j, Transaction& t)
{
    t.blockHash = j.value("blockHash", "");
    t.blockNumber = j.value("blockNumber", "");
    t.from = j.value("from", "");
    t.transactionIndex = j.value("transactionIndex", "");
    t.type = j.value("type", "");
    t.nonce = j.value("nonce", "");
    t.gas = j.value("gas", "");
    t.value = j.value("value", "");
    t.input = j.value("input", "");
    t.maxPriorityFeePerGas = j.value("maxPriorityFeePerGas", "");
    t.maxFeePerGas = j.value("maxFeePerGas", "");
    t.maxFeePerBlobGas = j.value("maxFeePerBlobGas", "");
    t.gasPrice = j.value("gasPrice", "");

    // For vectors, default to empty vector
    t.accessList = j.value("accessList", std::vector<AccessList>{});
    t.blobVersionedHashes =
        j.value("blobVersionedHashes", std::vector<std::string>{});

    t.chainId = j.value("chainId", "");
    t.yParity = j.value("yParity", "");
    t.r = j.value("r", "");
    t.s = j.value("s", "");
    t.v = j.value("v", "");

    if (j.contains("to") && !j["to"].is_null())
        t.to = j["to"].get<std::string>();
    else
        t.to = "";
}

struct Withdrawal
{
    std::string index;
    std::string validatorIndex;
    std::string address;
    std::string amount;
};

inline void from_json(const nlohmann::json& j, Withdrawal& w)
{
    w.index = j.value("index", "");
    w.validatorIndex = j.value("validatorIndex", "");
    w.address = j.value("address", "");
    w.amount = j.value("amount", "");
}

struct Block
{
    std::string hash;
    std::string parentHash;
    std::string sha3Uncles;
    std::string miner;
    std::string stateRoot;
    std::string transactionsRoot;
    std::string receiptsRoot;
    std::string logsBloom;
    std::string difficulty = {};
    std::string number;
    std::string gasLimit;
    std::string gasUsed;
    std::string timestamp;
    std::string extraData;
    std::string mixHash;
    std::string nonce;
    std::string baseFeePerGas = {};
    std::string withdrawalsRoot = {};
    std::string size;
    std::vector<Transaction> transactions = {};
    std::vector<std::string> transactionHashes = {};
    std::vector<Withdrawal> withdrawals = {};
    std::vector<std::string> uncles = {};
};

inline void from_json(const nlohmann::json& j, Block& b)
{
    b.number = j.value("number", "");
    b.hash = j.value("hash", "");
    b.parentHash = j.value("parentHash", "");
    b.nonce = j.value("nonce", "");
    b.sha3Uncles = j.value("sha3Uncles", "");
    b.logsBloom = j.value("logsBloom", "");
    b.transactionsRoot = j.value("transactionsRoot", "");
    b.stateRoot = j.value("stateRoot", "");
    b.receiptsRoot = j.value("receiptsRoot", "");
    b.miner = j.value("miner", "");
    b.mixHash = j.value("mixHash", "");
    b.difficulty = j.value("difficulty", "");
    b.extraData = j.value("extraData", "");
    b.size = j.value("size", "");
    b.gasLimit = j.value("gasLimit", "");
    b.gasUsed = j.value("gasUsed", "");
    b.timestamp = j.value("timestamp", "");
    b.uncles = j.value("uncles", std::vector<std::string>{});
    b.baseFeePerGas = j.value("baseFeePerGas", "");
    b.withdrawals = j.value("withdrawals", std::vector<Withdrawal>{});
    b.withdrawalsRoot = j.value("withdrawalsRoot", "");

    if (j.contains("transactions"))
    {
        if (!j["transactions"].empty() && j["transactions"][0].is_object())
            j.at("transactions").get_to(b.transactions);
        else if (!j["transactions"].empty() && j["transactions"][0].is_string())
            j.at("transactions").get_to(b.transactionHashes);
    }
}

struct Log
{
    bool removed = false;
    std::string logIndex = {};
    std::string transactionIndex = {};
    std::string transactionHash;
    std::string blockHash = {};
    std::string blockNumber = {};
    std::string blockTimestamp = {};
    std::string address = {};
    std::string data = {};
    std::vector<std::string> topics = {};
};

inline void from_json(const nlohmann::json& j, Log& l)
{
    if (j.is_string())
    {
        l.transactionHash = j.get<std::string>();
        return;
    }

    l.removed = j.value("removed", false);
    l.logIndex = j.value("logIndex", "");
    l.transactionIndex = j.value("transactionIndex", "");
    l.transactionHash = j.value("transactionHash", "");
    l.blockHash = j.value("blockHash", "");
    l.blockNumber = j.value("blockNumber", "");
    l.blockTimestamp = j.value("blockTimestamp", "");
    l.address = j.value("address", "");
    l.data = j.value("data", "");
    l.topics = j.value("topics", std::vector<std::string>{});
}

struct Receipt
{
    std::string type = {};
    std::string transactionHash;
    std::string transactionIndex;
    std::string blockHash;
    std::string blockNumber;
    std::string from;
    std::string to = {};
    std::string cumulativeGasUsed;
    std::string gasUsed;
    std::string blobGasUsed = {};
    std::string contractAddress = {};
    std::string logsBloom;
    std::string root = {};
    std::string status = {};
    std::string effectiveGasPrice;
    std::string blobGasPrice = {};
};

inline void from_json(const nlohmann::json& j, Receipt& r)
{
    r.type = j.value("type", "");
    r.transactionHash = j.value("transactionHash", "");
    r.transactionIndex = j.value("transactionIndex", "");
    r.blockHash = j.value("blockHash", "");
    r.blockNumber = j.value("blockNumber", "");
    r.from = j.value("from", "");
    r.to = j.value("to", "");
    r.cumulativeGasUsed = j.value("cumulativeGasUsed", "");
    r.gasUsed = j.value("gasUsed", "");
    r.blobGasUsed = j.value("blobGasUsed", "");
    r.logsBloom = j.value("logsBloom", "");
    r.root = j.value("root", "");
    r.status = j.value("status", "");
    r.effectiveGasPrice = j.value("effectiveGasPrice", "");
    r.blobGasPrice = j.value("blobGasPrice", "");

    if (j.contains("contractAddress") && !j["contractAddress"].is_null())
        r.contractAddress = j["contractAddress"].get<std::string>();
    else
        r.contractAddress = "";

    if (j.contains("to") && !j["to"].is_null())
        r.to = j["to"].get<std::string>();
    else
        r.to = "";
}

struct FeeHistory
{
    std::string oldestBlock;
    std::vector<std::string> baseFeePerGas = {};
    std::vector<std::string> baseFerPerBlobGas = {};
    std::vector<uint64_t> gasUsedRatio = {};
    std::vector<uint64_t> blobGasUsedRatio = {};
    std::vector<std::vector<std::string>> reward;
};

inline void from_json(const nlohmann::json& j, FeeHistory& f)
{
    f.oldestBlock = j.value("oldestBlock", "");

    f.baseFeePerGas = j.value("baseFeePerGas", std::vector<std::string>{});
    f.baseFerPerBlobGas =
        j.value("baseFerPerBlobGas", std::vector<std::string>{});

    if (j.contains("gasUsedRatio") && j["gasUsedRatio"].is_array())
    {
        f.gasUsedRatio.clear();
        for (const auto& v : j["gasUsedRatio"])
        {
            if (!v.is_null())
                f.gasUsedRatio.push_back(v.get<uint64_t>());
        }
    }

    if (j.contains("blobGasUsedRatio") && j["blobGasUsedRatio"].is_array())
    {
        f.blobGasUsedRatio.clear();
        for (const auto& v : j["blobGasUsedRatio"])
        {
            if (!v.is_null())
                f.blobGasUsedRatio.push_back(v.get<uint64_t>());
        }
    }

    if (j.contains("reward") && j["reward"].is_array())
    {
        f.reward.clear();
        for (const auto& inner : j["reward"])
        {
            if (inner.is_array())
            {
                std::vector<std::string> temp;
                for (const auto& s : inner)
                {
                    if (!s.is_null())
                        temp.push_back(s.get<std::string>());
                }
                f.reward.push_back(std::move(temp));
            }
        }
    }
}

}  // namespace web3::type::response
