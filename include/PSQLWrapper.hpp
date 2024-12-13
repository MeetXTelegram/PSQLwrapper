#pragma once

#include <csignal>
#include <variant>

#include <nlohmann/json.hpp>
#include <pqxx/pqxx>

#include <User.hpp>

enum AddUserResult {
    OK, /* The user succefully added */
    ALREADY_EXISTS, /* The user already exists */
    BANNED, /* The user has been banned */
    DB_ERROR, /* An error occurred on the database side */
};

AddUserResult addUser(User& user);
void removeUser(std::variant<std::int64_t, User> identificator);
User getUser(std::variant<std::uint64_t, User> identificator);
void updateUser(User& user);

namespace parsers {
    template <typename ValueType, bool useCast, typename CastType> std::vector<ValueType> parse(const std::string& json) {
        std::vector<ValueType> result;
        if (json.empty())
            return result;

        auto j = nlohmann::json::parse(json);
        for (auto& element : j)
            if (useCast)
                result.emplace_back(static_cast<CastType>(element.get<ValueType>()));
            else
                result.emplace_back(element.get<ValueType>());

        return result;
    }

    template <typename ValueType, bool useCast, typename CastType> std::string cast(std::vector<ValueType>& v) {
        nlohmann::json j;
        for (auto& element : v) {
            if (useCast)
                j.emplace_back(static_cast<CastType>(element));
            else
                j.emplace_back(element);
        }
        return j.dump();
    }
}
