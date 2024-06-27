#include "compress.hpp"

#include <iostream>
#include <fstream>
#include "detail/detail.hpp"

double mambo::compress(const char* path, unsigned n, const char** files){
    std::vector<std::string> vFiles(n);
    for(int i = 0; i < n; ++i) vFiles[i] = (*(files+i));
    return mambo::compress(path, vFiles);
}

double mambo::compress(const std::string& path, const std::vector<std::string>& files){
    std::fstream outStream(path, std::ios::out | std::ios::binary);
    if(!outStream.is_open()) return -1;

    detail::huffmanNode* root = detail::getHuffmanCodes(files);
    std::unordered_map<char, std::vector<int>> huffmanMap;
    detail::convertHuffmanTreeToMap(root, huffmanMap);
    detail::deleteHuffmanNodeTree(root);

    outStream << detail::SIGNATURE;

    auto strHuffmanMap = detail::writeHuffmanMap(huffmanMap);
    outStream << static_cast<size_t>(strHuffmanMap.size()) << strHuffmanMap;

    for (decltype(auto) file : files) {
        std::string compressed = detail::getCompressedFile(file, huffmanMap);
        std::string fileName = detail::getFileName(file);
        outStream << fileName.size() << fileName << compressed.size() << compressed;
    }

    outStream.close();

    return static_cast<double>(detail::getFileSize(files))/static_cast<double>(detail::getFileSize(path));
}