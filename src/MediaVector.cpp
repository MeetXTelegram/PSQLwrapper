#include <PSQLWrapper.hpp>

#include <nlohmann/json.hpp>

std::vector<std::string> parsers::parseJSONMediaVector(const std::string& jsonMV) {
    nlohmann::json j = nlohmann::json::parse(jsonMV);
    std::vector<std::string> mv;
    for (auto element : j) {
        mv.emplace_back(element.get<std::string>());
    }
    return mv;
}

std::string parsers::castMediaVector(std::vector<std::string>& mv) {
    nlohmann::json j;
    for (auto& element : mv) {
        j.push_back(element);
    }
    return j.dump();
}
