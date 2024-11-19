#pragma once

#include <csignal>
#include <variant>

#include <pqxx/pqxx>
#include <spdlog/spdlog.h>

#include <User.hpp>

void initDB(const std::string& name, pqxx::connection& db);
void addUser(User& user);
void removeUser(std::variant<std::int64_t, User&> identificator, pqxx::connection& db);
User getUser(std::variant<std::uint64_t, User&> identificator, pqxx::connection& db);
void updateUser(User& user, pqxx::connection& db);

namespace parsers {
    UserLanguage parseUserLanguage(int Integer);
    UserCountry parseUserCountry(int Integer);

    int castUserLanguage(UserLanguage& ul);
    int castUserCountry(UserCountry& uc);

    std::vector<std::string> parseJSONMediaVector(const std::string& jsonMV);
    std::string castMediaVector(std::vector<std::string>& mv);

    std::vector<std::uint16_t> parseJSONPreferredAges(const std::string& jsonPA);
    std::string castPreferredAges(std::vector<std::uint16_t>& pa);

    std::vector<UserLanguage> parseJSONPreferredLanguages(const std::string& jsonPL);
    std::string castPreferredLanguages(std::vector<UserLanguage>& pl);

    std::vector<UserCountry> parseJSONPreferredCountries(const std::string& jsonPC);
    std::string castPreferredCountries(std::vector<UserCountry>& pc);
}
