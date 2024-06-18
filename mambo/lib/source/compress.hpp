#ifndef MAMBO_COMPRESS_HPP
#define MAMBO_COMPRESS_HPP

#include <vector>
#include <string>

namespace mambo {
    int compress(const char* path, unsigned n, const char** files);
    int compress(const std::string& path, const std::vector<std::string>& files);
}

#endif //MAMBO_COMPRESS_HPP
