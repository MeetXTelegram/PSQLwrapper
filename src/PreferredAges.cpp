#include <PSQLWrapper.hpp>

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

std::vector<std::uint16_t> parsers::parseJSONPreferredAges(const std::string& jsonPA) {
    rapidjson::Document d;
    std::vector<std::uint16_t> pa;
    d.Parse(jsonPA.c_str());
    for (auto element = d.Begin(); element != d.End(); ++element) {
        pa.emplace_back(static_cast<std::uint16_t>(element->GetInt()));
    }
    return pa;
}

std::string parsers::castPreferredAges(std::vector<std::uint16_t>& pa) {
    rapidjson::Document d;
    rapidjson::Document::AllocatorType& allocator = d.GetAllocator();
    d.SetArray();
    for (auto& element : pa) {
        d.PushBack(element, allocator);
    }

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    d.Accept(writer);
    return buffer.GetString();
}
