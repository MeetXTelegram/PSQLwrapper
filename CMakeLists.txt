cmake_minimum_required(VERSION 3.5)

project(PSQLWrapper LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)


find_package(spdlog REQUIRED)
find_package(PostgreSQL REQUIRED)

add_subdirectory(json)

include_directories(json/include)
include_directories(include)
include_directories(Types)

add_library(PSQLWrapper SHARED 
    include/PSQLWrapper.hpp
    src/initDB.cpp
    src/UserLanguage.cpp
    src/UserCountry.cpp
    src/MediaVector.cpp
    src/PreferredAges.cpp)

install(TARGETS PSQLWrapper
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

target_link_libraries(PSQLWrapper PRIVATE ${PostgreSQL_LIBRARY} libpqxx.so spdlog::spdlog nlohmann_json::nlohmann_json)
