cmake_minimum_required(VERSION 3.5)

project(PSQLWrapper LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)


find_package(spdlog REQUIRED)
find_package(PostgreSQL REQUIRED)
find_package(libpqxx REQUIRED)

add_subdirectory(json)

include_directories(json/include)
include_directories(include)
include_directories(Types)
include_directories(external/include)

add_library(PSQLWrapper STATIC
    include/PSQLWrapper.hpp
    src/addUser.cpp
    src/removeUser.cpp
    src/updateUser.cpp
    src/getUser.cpp
    external/include/Definitions.hpp
    external/src/createLogger.cpp
    external/src/SIGUSR1Handler.cpp
    external/src/TerminateHandler.cpp
)

install(TARGETS PSQLWrapper
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

target_link_libraries(PSQLWrapper PRIVATE ${PostgreSQL_LIBRARY} libpqxx::pqxx spdlog::spdlog nlohmann_json::nlohmann_json Definitions)
