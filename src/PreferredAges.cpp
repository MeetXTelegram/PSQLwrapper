#include <PSQLWrapper.hpp>

#include <nlohmann/json.hpp>

std::vector<std::uint16_t> parsers::parseJSONPreferredAges(const std::string& jsonPA) {
    nlohmann::json j = nlohmann::json::parse(jsonPA);
    std::vector<std::uint16_t> pa;
    for (auto element : j) {
        pa.emplace_back(element.get<std::uint16_t>());
    }
    return pa;
}

std::string parsers::castPreferredAges(std::vector<std::uint16_t>& pa) {
    nlohmann::json j;

    for (auto& element : pa) {
        j.push_back(element);
    }
    return j.dump();
}
