#ifndef MAMBO_FILEWORKERS_HPP
#define MAMBO_FILEWORKERS_HPP

#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>

namespace mambo::detail {
    int getFileSize(const std::string& path);
    int getFileSize(const std::vector<std::string>& paths);

    std::string getFileName(const std::string& fullPath);

    bool checkSignature(std::fstream& stream);

    std::string getCompressedFile(const std::string& file, std::unordered_map<char, std::vector<int>>& map);

    std::string writeHuffmanMap(std::unordered_map<char, std::vector<int>>& map);
    std::unordered_map<char, std::vector<int>> readHuffmanMap(std::fstream& stream);
}

#endif //MAMBO_FILEWORKERS_HPP
