#ifndef MAMBO_UNCOMPRESS_HPP
#define MAMBO_UNCOMPRESS_HPP

#include <string>

namespace mambo {
    int uncompress(const char* archive, const char* where){
        return 0; // Return 0 if success
    }
    int uncompress(const std::string& archive, const std::string& where) {
        return uncompress(archive.c_str(), where.c_str());
    }
}

#endif //MAMBO_UNCOMPRESS_HPP
