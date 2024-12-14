#include <PSQLWrapper.hpp>

#include <variant>

#include <pqxx/pqxx>
#include <spdlog/spdlog.h>

namespace db { extern std::shared_ptr<pqxx::connection> database; }

User getUser(std::variant<std::int64_t, User> identificator) {
    User result;
    std::int64_t id = (std::holds_alternative<std::int64_t>(identificator) ? std::get<std::int64_t>(identificator) : std::get<User>(identificator).id);
    pqxx::work w(*db::database);
    try {
        pqxx::result dbresult = w.exec("SELECT * FROM users WHERE id = " + std::to_string(id));
        for (auto i : dbresult) {
            result.tgFirstName = i["tgFirstName"].as<std::string>();
            result.tgLastName = i["tgLastName"].as<std::string>();
            result.age = i["age"].as<std::uint16_t>();
            result.name = i["name"].as<std::string>();
            result.bio = i["bio"].as<std::string>();
            result.gender = static_cast<UserGender>(i["gender"].as<int>());
            result.language = static_cast<UserLanguage>(i["language"].as<int>());
            result.city = i["city"].as<std::string>();
            result.media = parsers::parse<std::string, false, std::string>(i["media"].as<std::string>());
            result.preferredLanguages = parsers::parse<UserLanguage, true, UserLanguage>(i["preferredLanguage"].as<std::string>());
            result.preferredAges = parsers::parse<std::uint16_t, false, std::uint16_t>(i["preferredAges"].as<std::string>());
            result.preferredCities = parsers::parse<std::string, false, std::string>(i["preferredCities"].as<std::string>());
            result.preferredGenders = parsers::parse<UserGender, false, UserGender>(i["preferredGender"].as<std::string>());
            result.hasProfile = i["hasProfile"].as<bool>();
        }
    } catch (std::exception& dberr) {
        spdlog::get("PSQL")->log(spdlog::level::err, "Failed to get user: pqxx created an exception: {}", dberr.what());
        return result;
    }

    return result;
}
