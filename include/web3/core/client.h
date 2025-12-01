#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <variant>

#include "core/error.h"
#include "core/iconnector.h"

#define VERSION 2

namespace web3::rpc
{

typedef std::variant<int, std::string> idType;

struct JsonRPCResponse
{
    idType id;
    nlohmann::json result;

    JsonRPCResponse(const idType& id, const nlohmann::json& result)
        : id(id), result(result)
    {
    }
};

class JsonRPCClient
{
   public:
    JsonRPCClient(IConnector& connector)
        : connector_(connector), version_(VERSION)
    {
    }
    virtual ~JsonRPCClient() = default;

    template <typename Result, typename Input>
    Result callMethod(const idType& id, const std::string& method,
                      const Input& params)
    {
        return sendRequest(id, method, params).result.template get<Result>();
    }

   protected:
    IConnector& connector_;

   private:
    uint64_t version_;

    nlohmann::json buildRequest(const idType& id, const std::string& method,
                                const nlohmann::json& params)
    {
        nlohmann::json j = {{"jsonrpc", version_}, {"method", method}};
        if (std::get_if<int>(&id) != nullptr)
            j["id"] = std::get<int>(id);
        else
            j["id"] = std::get<std::string>(id);
        if (!params.is_null() && !params.empty())
            j["params"] = params;

        return j;
    }

    JsonRPCResponse sendRequest(const idType& id, const std::string& method,
                                const nlohmann::json& params)
    {
        nlohmann::json j = buildRequest(id, method, params);

        try
        {
            nlohmann::json response =
                nlohmann::json::parse(connector_.send(j.dump()));

            if (hasTypedKey(response, "error", nlohmann::json::value_t::object))
                throw JsonRPCException::from_json(response["error"]);
            else if (hasTypedKey(response, "error",
                                 nlohmann::json::value_t::string))
                throw JsonRPCException(Error::UNKNOWN, response["error"]);

            if (hasKey(response, "result") && hasKey(response, "id"))
            {
                if (response["id"].type() == nlohmann::json::value_t::string)
                    return JsonRPCResponse(
                        response["id"].get<std::string>(),
                        response["result"].get<nlohmann::json>());
                else
                    return JsonRPCResponse(
                        response["id"].get<int>(),
                        response["result"].get<nlohmann::json>());
            }
            throw JsonRPCException(
                Error::INTERNAL,
                R"(Invalid server response: neither "result"  nor "error" fields found.)");
        }
        catch (nlohmann::json::parse_error& e)
        {
            throw JsonRPCException(
                Error::PARSE,
                std::string("Invalid JSON response from server: ") + e.what());
        }
    }
};

}  // namespace web3::rpc
