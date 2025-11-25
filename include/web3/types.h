#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace web3
{

struct Transaction
{
    std::string blockHash;
    std::string blockNumber;
    std::string chainId;
    std::string from;
    std::string gas;
    std::string gasPrice;
    std::string maxFeePerGas;
    std::string maxPriorityFeePerGas;
    std::string hash;
    std::string input;
    std::string nonce;
    std::string to;
    std::string transactionIndex;
    std::string value;
    std::string type;
    std::string v;
    std::string r;
    std::string s;
};

inline void to_json(nlohmann::json& json, const Transaction& transaction)
{
    json = nlohmann::json{
        {"blockHash", transaction.blockHash},
        {"blockNumber", transaction.blockNumber},
        {"chainId", transaction.chainId},
        {"from", transaction.from},
        {"gas", transaction.gas},
        {"gasPrice", transaction.gasPrice},
        {"maxFeePerGas", transaction.maxFeePerGas},
        {"maxPriorityFeePerGas", transaction.maxPriorityFeePerGas},
        {"hash", transaction.hash},
        {"input", transaction.input},
        {"nonce", transaction.nonce},
        {"to", transaction.to},
        {"transactionIndex", transaction.transactionIndex},
        {"value", transaction.value},
        {"type", transaction.type},
        {"v", transaction.v},
        {"r", transaction.r},
        {"s", transaction.s}};
}

inline void from_json(const nlohmann::json& json, Transaction& transaction)
{
    json.at("blockHash").get_to(transaction.blockHash);
    json.at("blockNumber").get_to(transaction.blockNumber);
    json.at("chainId").get_to(transaction.blockNumber);
    json.at("from").get_to(transaction.from);
    json.at("gas").get_to(transaction.gas);
    json.at("gasPrice").get_to(transaction.gasPrice);
    json.at("maxFeePerGas").get_to(transaction.maxFeePerGas);
    json.at("maxPriorityFeePerGas").get_to(transaction.maxPriorityFeePerGas);
    json.at("hash").get_to(transaction.hash);
    json.at("input").get_to(transaction.input);
    json.at("nonce").get_to(transaction.nonce);
    json.at("to").get_to(transaction.to);
    json.at("transactionIndex").get_to(transaction.transactionIndex);
    json.at("value").get_to(transaction.value);
    json.at("type").get_to(transaction.type);
    json.at("v").get_to(transaction.v);
    json.at("r").get_to(transaction.r);
    json.at("s").get_to(transaction.s);
}

struct Withdrawal
{
    std::string index;
    std::string validatorIndex;
    std::string address;
    std::string amount;
};

inline void to_json(nlohmann::json& j, const Withdrawal& w)
{
    j = nlohmann::json{{"index", w.index},
                       {"validatorIndex", w.validatorIndex},
                       {"address", w.address},
                       {"amount", w.amount}};
}

inline void from_json(const nlohmann::json& j, Withdrawal& w)
{
    j.at("index").get_to(w.index);
    j.at("validatorIndex").get_to(w.validatorIndex);
    j.at("address").get_to(w.address);
    j.at("amount").get_to(w.amount);
}

struct Block
{
    std::string baseFeePerGas;
    std::string difficulty;
    std::string extraData;
    std::string gasLimit;
    std::string gasUsed;
    std::string hash;
    std::string logsBloom;
    std::string miner;
    std::string mixHash;
    std::string nonce;
    std::string number;
    std::string parentHash;
    std::string receiptsRoot;
    std::string sha3Uncles;
    std::string size;
    std::string stateRoot;
    std::string timestamp;
    std::vector<Transaction> transactions;
    std::string transactionsRoot;
    std::vector<std::string> uncles;
    std::vector<Withdrawal> withdrawals;
    std::string withdrawalsRoot;
};

inline void to_json(nlohmann::json& j, const Block& b)
{
    j = nlohmann::json{{"number", b.number},
                       {"hash", b.hash},
                       {"parentHash", b.parentHash},
                       {"nonce", b.nonce},
                       {"sha3Uncles", b.sha3Uncles},
                       {"logsBloom", b.logsBloom},
                       {"transactionsRoot", b.transactionsRoot},
                       {"stateRoot", b.stateRoot},
                       {"receiptsRoot", b.receiptsRoot},
                       {"miner", b.miner},
                       {"mixHash", b.mixHash},
                       {"difficulty", b.difficulty},
                       {"extraData", b.extraData},
                       {"size", b.size},
                       {"gasLimit", b.gasLimit},
                       {"gasUsed", b.gasUsed},
                       {"timestamp", b.timestamp},
                       {"transactions", b.transactions},
                       {"uncles", b.uncles},
                       {"baseFeePerGas", b.baseFeePerGas},
                       {"withdrawals", b.withdrawals},
                       {"withdrawalsRoot", b.withdrawalsRoot}};
}

inline void from_json(const nlohmann::json& j, Block& b)
{
    j.at("number").get_to(b.number);
    j.at("hash").get_to(b.hash);
    j.at("parentHash").get_to(b.parentHash);
    j.at("nonce").get_to(b.nonce);
    j.at("sha3Uncles").get_to(b.sha3Uncles);
    j.at("logsBloom").get_to(b.logsBloom);
    j.at("transactionsRoot").get_to(b.transactionsRoot);
    j.at("stateRoot").get_to(b.stateRoot);
    j.at("receiptsRoot").get_to(b.receiptsRoot);
    j.at("miner").get_to(b.miner);
    j.at("mixHash").get_to(b.mixHash);
    j.at("difficulty").get_to(b.difficulty);
    j.at("extraData").get_to(b.extraData);
    j.at("size").get_to(b.size);
    j.at("gasLimit").get_to(b.gasLimit);
    j.at("gasUsed").get_to(b.gasUsed);
    j.at("timestamp").get_to(b.timestamp);
    j.at("transactions").get_to(b.transactions);
    j.at("uncles").get_to(b.uncles);
    j.at("baseFeePerGas").get_to(b.baseFeePerGas);
    j.at("withdrawals").get_to(b.withdrawals);
    j.at("withdrawalsRoot").get_to(b.withdrawalsRoot);
}

struct Log
{
    std::string logIndex;
    bool removed = false;

    std::string address;
    std::vector<std::string> topics;
    std::string data;

    std::string blockNumber;
    std::string blockTimestamp;
    std::string blockHash;
    std::string transactionHash;
    std::string transactionIndex;
};

inline void to_json(nlohmann::json& json, const Log& log)
{
    json = nlohmann::json{{"logIndex", log.logIndex},
                          {"removed", log.removed},
                          {"blockNumber", log.blockNumber},
                          {"blockTimestamp", log.blockTimestamp},
                          {"blockHash", log.blockHash},
                          {"transactionHash", log.transactionHash},
                          {"transactionIndex", log.transactionIndex},
                          {"address", log.address},
                          {"data", log.data},
                          {"topics", log.topics}};
}

inline void from_json(const nlohmann::json& json, Log& log)
{
    json.at("logIndex").get_to(log.logIndex);
    json.at("address").get_to(log.address);
    json.at("topics").get_to(log.topics);
    json.at("data").get_to(log.data);
    json.at("blockNumber").get_to(log.blockNumber);
    json.at("blockTimestamp").get_to(log.blockTimestamp);
    json.at("blockHash").get_to(log.blockHash);
    json.at("transactionHash").get_to(log.transactionHash);
    json.at("transactionIndex").get_to(log.transactionIndex);

    if (json.contains("removed"))
        json.at("removed").get_to(log.removed);
}

struct Receipt
{
    std::string blockHash;
    std::string blockNumber;
    std::string contractAddress;
    std::string cumulativeGasUsed;
    std::string effectiveGasPrice;
    std::string from;
    std::string gasUsed;
    std::vector<Log> logs;
    std::string logsBloom;
    std::string status;
    std::string to;
    std::string transactionHash;
    std::string transactionIndex;
    std::string type;
};

inline void to_json(nlohmann::json& j, const Receipt& r)
{
    j = nlohmann::json{{"blockHash", r.blockHash},
                       {"blockNumber", r.blockNumber},
                       {"contractAddress", r.contractAddress},
                       {"cumulativeGasUsed", r.cumulativeGasUsed},
                       {"effectiveGasPrice", r.effectiveGasPrice},
                       {"from", r.from},
                       {"gasUsed", r.gasUsed},
                       {"logs", r.logs},
                       {"logsBloom", r.logsBloom},
                       {"status", r.status},
                       {"to", r.to},
                       {"transactionHash", r.transactionHash},
                       {"transactionIndex", r.transactionIndex},
                       {"type", r.type}};
}

inline void from_json(const nlohmann::json& j, Receipt& r)
{
    j.at("blockHash").get_to(r.blockHash);
    j.at("blockNumber").get_to(r.blockNumber);
    j.at("contractAddress").get_to(r.contractAddress);
    j.at("cumulativeGasUsed").get_to(r.cumulativeGasUsed);
    j.at("effectiveGasPrice").get_to(r.effectiveGasPrice);
    j.at("from").get_to(r.from);
    j.at("gasUsed").get_to(r.gasUsed);
    j.at("logs").get_to(r.logs);
    j.at("logsBloom").get_to(r.logsBloom);
    j.at("status").get_to(r.status);
    j.at("to").get_to(r.to);
    j.at("transactionHash").get_to(r.transactionHash);
    j.at("transactionIndex").get_to(r.transactionIndex);
    j.at("type").get_to(r.type);
}

struct FeeHistory
{
    std::string oldestBlock;
    std::vector<std::vector<std::string>> reward;
    std::vector<double> gasUsedRatio;
    std::vector<std::string> baseFeePerGas;
};

inline void to_json(nlohmann::json& j, const FeeHistory& f)
{
    j = {{"oldestBlock", f.oldestBlock},
         {"reward", f.reward},
         {"baseFeePerGas", f.baseFeePerGas},
         {"gasUsedRatio", f.gasUsedRatio}};
}

inline void from_json(const nlohmann::json& j, FeeHistory& f)
{
    j.at("oldestBlock").get_to(f.oldestBlock);
    j.at("reward").get_to(f.reward);
    j.at("baseFeePerGas").get_to(f.baseFeePerGas);
    j.at("gasUsedRatio").get_to(f.gasUsedRatio);
}

}  // namespace web3
