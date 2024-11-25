#include <PSQLWrapper.hpp>

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

std::vector<std::string> parsers::parseJSONMediaVector(const std::string& jsonMV) {
    rapidjson::Document d;
    std::vector<std::string> mv;
    d.Parse(jsonMV.c_str());
    for (auto element = d.Begin(); element != d.End(); ++element) {
        mv.emplace_back(element->GetString());
    }
    return mv;
}

std::string parsers::castMediaVector(std::vector<std::string>& mv) {
    rapidjson::Document d;
    rapidjson::Document::AllocatorType& allocator = d.GetAllocator();
    d.SetArray();
    for (auto& element : mv) {
        d.PushBack(element, allocator);
    }

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    d.Accept(writer);
    return buffer.GetString();
}
