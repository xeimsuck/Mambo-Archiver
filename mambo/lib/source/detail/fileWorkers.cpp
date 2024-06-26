#include "fileWorkers.hpp"
#include "detail.hpp"

#include <filesystem>

int mambo::detail::getFileSize(const std::string &path) {
    return static_cast<int>(std::filesystem::file_size(path));
}
int mambo::detail::getFileSize(const std::vector<std::string>& paths) {
    int size = 0;
    for(decltype(auto) path : paths)
        size+=static_cast<int>(getFileSize(path));
    return size;
}

std::string mambo::detail::getFileName(const std::string &fullPath) {
    return fullPath.substr(fullPath.find_last_of('/')+1);
}

bool mambo::detail::checkSignature(std::fstream& stream) {
    if(!stream.is_open()) return false;

    std::string signature(SIGNATURE.size(), ' ');
    stream.read(signature.data(), SIGNATURE.size());

    return signature==SIGNATURE;
}

std::string mambo::detail::getCompressedFile(const std::string &file, std::unordered_map<char, std::vector<int>>& map) {
    std::string result;

    std::fstream stream (file, std::ios::in | std::ios::binary);
    if(!stream.is_open()) return "";

    char sym;
    int c = 0, i = 7;
    while (!stream.eof()) {
        if(c==0) {
            stream >> sym;
            if(stream.eof()) break;
        }
        if(i==7) result.push_back(static_cast<int>(0));
        decltype(auto) byte = result.back();
        while(i>=0){
            if(c==map[sym].size()) {
                c = 0;
                break;
            }
            byte = byte | map[sym][c] << i;
            --i; ++c;
        }
        if(i==-1) i = 7;
    }

    stream.close();

    return result;
}

std::string mambo::detail::writeHuffmanMap(std::unordered_map<char, std::vector<int>> &map) {
    std::string result;
    for (decltype(auto) pair : map){
        char bytes[16]{};
        for(int i = 0; i<pair.second.size(); ++i)
            bytes[i/8] = bytes[i/8] | pair.second[i] << (7-i%8);
        result += std::string{pair.first} + static_cast<char>(pair.second.size());
        for(int i = 0; i <= (pair.second.size()-1)/8; ++i) result+=bytes[i];
    }
    return result;
}
std::unordered_map<char, std::vector<int>> mambo::detail::readHuffmanMap(std::fstream& stream) {
    std::unordered_map<char, std::vector<int>> map;
    size_t size;
    stream >> size;

    for(int i = 0; i < size;++i){
        char symbol, scale;
        stream.get(symbol);
        stream.get(scale);

        std::vector<int> v;
        char byte;
        for(int j = 0; j<((scale-1)/8); ++j){
            stream.get(byte);
            for(int k = 7; k >= 0; --k) {
                v.push_back(std::abs((byte >> k)%2));
            }
            ++i;
        }
        stream.get(byte);
        for(int k = 7; k >= 7-(scale-1)%8; --k) {
            v.push_back(std::abs((byte >> k)%2));
        }
        map[symbol] = std::move(v);
    }
    return map;
}