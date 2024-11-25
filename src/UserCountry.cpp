#include <PSQLWrapper.hpp>

int parsers::castUserCountry(UserCountry& uc) {
    return static_cast<int>(uc);
}

UserCountry parsers::parseUserCountry(int ucI) {
    return static_cast<UserCountry>(ucI);
}

