#include "core/client.h"

#include <curl/curl.h>

#include <stdexcept>
#include <string>

#include "jsonrpccxx/common.hpp"

namespace web3::rpc
{

HTTPClient::HTTPClient(const std::string& host, int port)
    : host_{host}, port_{port}
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

HTTPClient::~HTTPClient()
{
    curl_global_cleanup();
}

std::string HTTPClient::Send(const std::string& request)
{
    CURL* curl = curl_easy_init();
    if (!curl)
        throw std::runtime_error("Failed to init CURL.");

    std::string response;
    std::string url =
        "http://" + host_ + ":" + std::to_string(port_) + "/jsonrpc";

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    curl_easy_setopt(curl, CURLOPT_POST, 1L);

    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, request.size());

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);

    long code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &code);

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK)
        throw jsonrpccxx::JsonRpcException(
            -32003,
            std::string("Connection Error: ") + curl_easy_strerror(res));

    if (code != 200)
        throw jsonrpccxx::JsonRpcException(
            -32003,
            std::string("Client Connection Error - Received Non-200 Status"));

    return response;
}

size_t HTTPClient::WriteCallback(void* contents, size_t size, size_t nmemb,
                                 void* userp)
{
    size_t total = size * nmemb;
    std::string* out = reinterpret_cast<std::string*>(userp);
    out->append(static_cast<char*>(contents), total);
    return total;
}

}  // namespace web3::rpc
