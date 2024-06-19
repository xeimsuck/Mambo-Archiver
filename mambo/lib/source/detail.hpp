#ifndef MAMBO_DETAIL_HPP
#define MAMBO_DETAIL_HPP

#include <fstream>
#include <string>

namespace mambo::detail {
    int getFileSize(std::fstream& stream);
    int getFileSize(const std::string& path);
}

#endif //MAMBO_DETAIL_HPP
