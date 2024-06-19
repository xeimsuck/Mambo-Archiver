#include "detail.hpp"

int mambo::detail::getFileSize(std::fstream &stream){
    const auto prev = stream.tellg();
    stream.seekg(std::ios::end);
    const auto size = stream.tellg();
    stream.seekg(prev);
    return static_cast<int>(size);
}

int mambo::detail::getFileSize(const std::string &path) {
    std::fstream stream(path, std::ios::binary);
    if(!stream.is_open()) return -1;
    int size = getFileSize(stream);
    stream.close();
    return size;
}