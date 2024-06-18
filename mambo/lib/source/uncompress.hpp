#ifndef MAMBO_UNCOMPRESS_HPP
#define MAMBO_UNCOMPRESS_HPP

#include <string>

namespace mambo {
    int uncompress(const char* archive, const char* where);
    int uncompress(const std::string& archive, const std::string& where);
}

#endif //MAMBO_UNCOMPRESS_HPP
