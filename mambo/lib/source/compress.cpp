#include "compress.hpp"

#include <iostream>
#include <fstream>
#include "detail.hpp"

double mambo::compress(const char* path, unsigned n, const char** files){
    std::vector<std::string> vFiles(n);
    for(int i = 0; i < n; ++i) vFiles[i] = (*(files+i));
    return mambo::compress(path, vFiles);
}

double mambo::compress(const std::string& path, const std::vector<std::string>& files){
    std::fstream outStream(path, std::ios::out | std::ios::binary);
    if(!outStream.is_open()) return -1;

    detail::node* root = detail::getHuffmanCodes(files);

    std::unordered_map<char, std::vector<int>> huffmanMap;
    detail::getBits(root, huffmanMap);

    std::string result;
    for (decltype(auto) file : files) {
        result+=detail::getFileName(file)+"\n\t\n\t"+detail::writeBits(file, huffmanMap);
    }
    outStream << result;

    detail::deleteNodeTree(root);

    return static_cast<double>(detail::getFileSize(files))/static_cast<double>(result.size());
}