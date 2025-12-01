#pragma once
#include <exception>
#include <string>

#include "nlohmann/json.hpp"

namespace web3::rpc
{

static inline bool hasKey(const nlohmann::json& j, const std::string& k)
{
    return j.find(k) != j.end();
}

static inline bool hasTypedKey(const nlohmann::json& j, const std::string& k,
                               nlohmann::json::value_t t)
{
    return hasKey(j, k) && j.at(k).type() == t;
}
static inline bool validNullId(const nlohmann::json& r)
{
    return hasKey(r, "id") &&
           (r["id"].is_number() || r["id"].is_string() || r["id"].is_null());
}
static inline bool validId(const nlohmann::json& r)
{
    return hasKey(r, "id") && (r["id"].is_number() || r["id"].is_string());
}

enum Error
{
    PARSE = -32700,
    INVALIDREQUEST = -32600,
    METHODNOTFOUND = -32601,
    INVALIDPARAMS = -32602,
    INTERNAL = -32603,
    INVALIDINPUT = -32000,
    RESOURCEUNAVAILABLE = -32003,
    TRANSACTIONREJECTED = -32003,
    METHODNOTSUPPORTED = -32004,
    LIMITEXCEEDED = -32005,
    JSONRPCVERSION = -32006,
    UNKNOWN
};

class JsonRPCException : public std::exception
{
   public:
    JsonRPCException(int code, const std::string& message) noexcept
        : code(code),
          message(message),
          data(nullptr),
          err(std::to_string(code) + ": " + message)
    {
    }
    JsonRPCException(int code, const std::string& message,
                     const nlohmann::json& data) noexcept
        : code(code),
          message(message),
          data(data),
          err(std::to_string(code) + ": " + message + ", data: " + data.dump())
    {
    }

    Error Type() const
    {
        if (code >= -32700 && code <= -32603 ||
            code >= -32606 && code <= -32000)
            return static_cast<Error>(code);
        return Error::UNKNOWN;
    }

    int Code() const
    {
        return code;
    }
    const std::string& Message() const
    {
        return message;
    }
    const nlohmann::json& Data() const
    {
        return data;
    }

    const char* what() const noexcept override
    {
        return err.c_str();
    }

    static inline JsonRPCException from_json(const nlohmann::json& value)
    {
        bool has_code = hasTypedKey(value, "code",
                                    nlohmann::json::value_t::number_integer) ||
                        hasTypedKey(value, "code",
                                    nlohmann::json::value_t::number_unsigned);
        bool has_message =
            hasTypedKey(value, "message", nlohmann::json::value_t::string);
        bool has_data = hasKey(value, "data");
        if (has_code && has_message)
        {
            if (has_data)
            {
                return JsonRPCException(value["code"], value["message"],
                                        value["data"].get<nlohmann::json>());
            }
            else
            {
                return JsonRPCException(value["code"], value["message"]);
            }
        }
        return JsonRPCException(
            Error::UNKNOWN,
            R"(Invalid Ethereum nlohmann::json-RPC error response)");
    }

   private:
    int code;
    std::string message;
    nlohmann::json data;
    std::string err;
};
}  // namespace web3::rpc
