#ifndef MAMBO_HUFFMANCODE_HPP
#define MAMBO_HUFFMANCODE_HPP

#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <queue>

namespace mambo::detail {
    struct huffmanNode;
    struct huffmanNodeComparator;

    void deleteHuffmanNodeTree(huffmanNode * root);

    huffmanNode* getHuffmanCodes(const std::string &path);
    huffmanNode* getHuffmanCodes(const std::vector<std::string>& paths);
    huffmanNode* getHuffmanCodes(const std::unordered_map<char, int>& nodes);

    void convertHuffmanTreeToMap(mambo::detail::huffmanNode *root, std::unordered_map<char, std::vector<int>>& map);
    void convertHuffmanTreeToMap(mambo::detail::huffmanNode *root, std::vector<int>&v, std::unordered_map<char, std::vector<int>>& map);
}


#endif //MAMBO_HUFFMANCODE_HPP
