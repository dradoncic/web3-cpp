# SHIFT Web3 C++ Library

A comprehensive C++ library for interacting with Ethereum and Anvil (Ethereum local testing tool). This library provides a clean, object-oriented interface for blockchain operations including account management, contract interaction, RPC calls, and transaction handling.

## Features

- **Ethereum Integration**: Full support for Ethereum RPC calls and operations
- **Anvil Support**: Specialized support for Anvil local development environment
- **Account Management**: Create accounts, manage private keys, and handle wallets
- **Smart Contract Interaction**: Deploy and call smart contracts with ABI support
- **Transaction Handling**: Support for multiple transaction types (Legacy, EIP-2930, EIP-1559, EIP-4844, EIP-7702)
- **Utility Functions**: Comprehensive utilities for cryptographic operations, hex conversions, and BigNumber arithmetic
- **HTTP RPC Client**: Built-in HTTP client for JSON-RPC communication

## Architecture

The library is organized into several core components:

- **Web3 Core**: Main entry point (`Web3` class) that delegates to Ethereum or Anvil implementations
- **Ethereum (`eth`)**: Standard Ethereum operations including RPC, accounts, and contracts
- **Anvil (`anvil`)**: Anvil-specific functionality extending Ethereum capabilities
- **Types**: Request and response structures for RPC communication
- **Utils**: Cryptographic utilities, encoding/decoding, and helper functions

## Installation

### Prerequisites

- C++17 or later
- CMake 3.10+
- Dependencies:
  - `nlohmann/json` (JSON parsing)
  - `jsonrpccxx` (JSON-RPC client)
  - `libcurl` (HTTP communication)
  - `cryptopp` (Cryptographic operations)
  - `gmp` (Big number arithmetic)

### Building

```bash
mkdir build
cd build
cmake ..
make
```

## Usage

### Basic Setup

```cpp
#include <web3/web3.h>

// Connect to Ethereum node
web3::Web3 w3("localhost", 8545, web3::RPCType::Ethereum);

// Or connect to Anvil
web3::Web3 w3("localhost", 8545, web3::RPCType::Anvil);
```

### Account Management

```cpp
auto& accounts = w3.eth().accounts();

// Create a new account
auto account = accounts.create();
std::cout << "Address: " << account.address << std::endl;
std::cout << "Private Key: " << account.privateKey << std::endl;

// Import from private key
auto imported = accounts.privateKeyToAccount("0x...");

// Access wallet
auto& wallet = accounts.wallet();
wallet.add(account);
```

### Interacting with Contracts

```cpp
nlohmann::json abi = nlohmann::json::parse(abiJson);
auto contract = w3.eth().contract("0xContractAddress", abi);

// Call a view function
auto method = contract.method("balanceOf");
method.param("0xUserAddress");
auto result = method.call("0xContractAddress");

// Send a transaction
auto sendMethod = contract.method("transfer");
sendMethod.param("0xRecipientAddress");
sendMethod.param(uint64_t{100});
auto txHash = sendMethod.send("0xYourAddress", "0xContractAddress", "0", "100000");
```

### Transactions

```cpp
auto& rpc = w3.eth().rpc();

// Legacy transaction
web3::type::request::Transaction tx(
    0,           // nonce
    20000000000, // gas price (20 Gwei)
    21000,       // gas
    "0xTo",
    "0xFrom",
    1000000000000000000 // value (1 Ether in Wei)
);

// Sign and send
std::string txHash = rpc.sendRawTransaction(tx);
```

### Utility Functions

```cpp
#include <web3/utils.h>

using namespace web3::utils;

// Unit conversions
std::string wei = toWei("1.0", "ether");
std::string ether = fromWei(wei, "ether");

// Hex operations
std::string hex = intToHex(255);
uint64_t num = hexToInt("0xFF");
std::vector<uint8_t> bytes = hexToBytes("0xABCD");
std::string hexString = bytesToHex(bytes);

// Cryptography
std::vector<uint8_t> data = {0x01, 0x02, 0x03};
std::string hash = keccak256(data);

// BigNumber arithmetic
std::string sum = BN::add("123456789", "987654321", 10);
std::string product = BN::mul("1000", "2000", 10);

// Address utilities
std::string checksum = toChecksumAddress("0xabcd1234abcd1234abcd1234abcd1234abcd1234");
bool valid = isAddress(checksum);
```

### RPC Calls

```cpp
auto& rpc = w3.eth().rpc();

// Get block information
auto blockNum = rpc.blockNumber();
auto block = rpc.getBlockByNumber(std::stoul(blockNum));
auto balance = rpc.getBalance({"0xAddress"});

// Get transaction details
auto tx = rpc.getTransactionByHash("0xTxHash");
auto receipt = rpc.getTransactionReceipt("0xTxHash");

// Gas estimation
web3::type::request::Transaction estimateTx(...);
auto gasEstimate = rpc.estimateGas(estimateTx);
```

### Anvil-Specific Operations

```cpp
auto& anvil = w3.anvil();

// Set account balance
web3::type::request::Balance balance{
    "0xAddress",
    "1000000000000000000" // 1 Ether in Wei
};
anvil.rpc().setBalance(balance);

// Drop a transaction
anvil.rpc().dropTransaction("0xTxHash");

// Access Anvil accounts and contracts
auto& accounts = anvil.accounts();
auto contract = anvil.contract("0xAddress", abi);
```

## API Reference

### Web3 Class

Main entry point for the library.

```cpp
Web3(const std::string& host, int port, RPCType type);
eth::Eth& eth();
anvil::Anvil& anvil();
RPCType type() const;
```

### Accounts & Wallet

Manage Ethereum accounts and private keys.

```cpp
class Accounts {
    Account create();
    Account privateKeyToAccount(const std::string& privateKey);
    std::string signTransaction(const Transaction& tx, const std::string& privateKey);
    Wallet& wallet();
};

class Wallet {
    void add(const Account& account);
    void remove(const std::string& address);
    void clear();
    Account get(const std::string& address);
    const std::map<std::string, Account> getAll() const;
};
```

### Contract Class

Deploy and interact with smart contracts.

```cpp
class Contract {
    ContractMethod method(const std::string& name);
    static std::string deploy(const nlohmann::json& abi, const std::string& bytecode, 
                              const std::string& from, RPC& rpc);
    std::string address() const;
};

class ContractMethod {
    ContractMethod& param(const std::string& value);
    ContractMethod& param(uint64_t value);
    ContractMethod& param(bool value);
    std::string call(const std::string& to, const std::string& from = "");
    std::string send(const std::string& from, const std::string& to, 
                     const std::string& value = "0", const std::string& gas = "");
};
```

### RPC Class

Interact with Ethereum nodes via JSON-RPC.

```cpp
class RPC {
    std::string blockNumber();
    std::string chainId();
    std::string gasPrice();
    type::response::Block getBlockByNumber(uint64_t number);
    type::response::Block getBlockByHash(const std::string& hash);
    type::response::Transaction getTransactionByHash(const std::string& hash);
    type::response::Receipt getTransactionReceipt(const std::string& hash);
    std::string getBalance(const type::request::Address& s);
    std::string getTransactionCount(const type::request::Address& s);
    std::string estimateGas(const type::request::Transaction& t);
    std::string sendRawTransaction(const type::request::Transaction& t);
};
```

## Transaction Types Supported

- **Legacy (Type 0)**: Traditional Ethereum transactions
- **EIP-2930 (Type 1)**: Transactions with access lists
- **EIP-1559 (Type 2)**: Dynamic fee transactions with priority fees
- **EIP-4844 (Type 3)**: Blob-carrying transactions
- **EIP-7702 (Type 4)**: Transactions with authorization lists

## Examples

### Example 1: Query Block Information

```cpp
web3::Web3 w3("localhost", 8545, web3::RPCType::Ethereum);
auto& rpc = w3.eth().rpc();

std::string latestBlockNum = rpc.blockNumber();
auto block = rpc.getBlockByNumber(std::stoul(latestBlockNum));

std::cout << "Block Hash: " << block.hash << std::endl;
std::cout << "Block Number: " << block.number << std::endl;
std::cout << "Miner: " << block.miner << std::endl;
```

### Example 2: Create and Manage Accounts

```cpp
web3::Web3 w3("localhost", 8545, web3::RPCType::Anvil);
auto& accounts = w3.anvil().accounts();

auto newAccount = accounts.create();
auto& wallet = accounts.wallet();
wallet.add(newAccount);

// Set balance in Anvil
web3::type::request::Balance balance{newAccount.address, toWei("10", "ether")};
w3.anvil().rpc().setBalance(balance);
```

### Example 3: Deploy and Call Contract

```cpp
nlohmann::json abi = nlohmann::json::parse(contractAbi);
std::string bytecode = "0x...";

// Deploy
std::string contractAddress = web3::eth::Contract::deploy(abi, bytecode, "0xFrom", rpc);

// Interact
auto contract = w3.eth().contract(contractAddress, abi);
auto method = contract.method("someFunction");
method.param("paramValue");
auto result = method.call(contractAddress);
```

## Error Handling

The library throws standard C++ exceptions for errors:

```cpp
try {
    auto block = rpc.getBlockByNumber(123456);
} catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
}
```

## License

[Add your license information here]

## Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues for bugs and feature requests.
