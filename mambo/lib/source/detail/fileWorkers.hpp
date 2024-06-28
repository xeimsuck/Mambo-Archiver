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


    std::string writeHuffmanMap(std::unordered_map<char, std::string>& map);
    std::unordered_map<char, std::string> readHuffmanMap(std::fstream& stream);

    std::string readFileName(std::fstream& stream);

    std::string writeCompressedFile(const std::string& file, std::unordered_map<char, std::string>& map);
    std::string readCompressedFile(std::fstream& stream, std::unordered_map<char, std::string>& huffmanMap);
}

#endif //MAMBO_FILEWORKERS_HPP
