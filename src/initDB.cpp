#include <PSQLWrapper.hpp>

void initDB(const std::string& name, std::shared_ptr<pqxx::connection> db) {
    if (!db || !db->is_open()) {
        spdlog::get("PSQL")->log(spdlog::level::critical, "Init db error: db is not opened/not created(shared_ptr)");
        std::raise(SIGUSR1);
    }
    try {
        pqxx::work w(*db);
        w.exec("CREATE TABLE IF NOT EXISTS users ("
               "id BIGINT PRIMARY KEY NOT NULL,"
               "tgFirstName VARCHAR,"
               "tgLastName VARCHAR,"
               "username VARCHAR NOT NULL,"
               "name VARCHAR,"
               "city VARCHAR,"
               "age SMALLINT DEFAULT 0,"
               "bio TEXT,"
               "language SMALLINT NOT NULL DEFAULT 2,"
               "gender SMALLINT NOT NULL,"
               "media JSONB,"
               "preferredAges JSONB,"
               "preferredCountries JSONB,"
               "preferredCities JSONB,"
               "preferredLanguages JSONB,"
               "hasProfile BOOLEAN NOT NULL DEFAULT FALSE"
               ");"
               );
        w.commit();
    } catch (std::exception& sqlerr) {
        spdlog::get("PSQL")->log(spdlog::level::critical, "Failed to create table");
        std::raise(SIGUSR1);
    }
}
