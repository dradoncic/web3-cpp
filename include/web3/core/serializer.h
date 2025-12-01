#pragma once

#include <nlohmann/json.hpp>
#include <optional>

namespace nlohmann
{

template <typename T>
struct nlohmann::adl_serializer<std::optional<T>>
{
    static void to_json(nlohmann::json& j, const std::optional<T>& opt)
    {
        if (!opt.has_value())
            j = nullptr;
        else
            j = opt.value();
    }

    static void from_json(const nlohmann::json& j, std::optional<T>& opt)
    {
        if (j.is_null())
            opt = std::nullopt;
        else
            opt = j.get<T>();
    }
};

}  // namespace nlohmann
