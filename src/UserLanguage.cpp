#include <PSQLWrapper.hpp>

int parsers::castUserLanguage(UserLanguage& ul) {
    return static_cast<int>(ul);
}

UserLanguage parsers::parseUserLanguage(int ulI) {
    return static_cast<UserLanguage>(ulI);
}
