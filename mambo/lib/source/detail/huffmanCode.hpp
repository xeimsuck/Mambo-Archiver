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

    void convertHuffmanTreeToMap(mambo::detail::huffmanNode *root, std::unordered_map<char, std::string>& map);
    void convertHuffmanTreeToMap(mambo::detail::huffmanNode *root, std::string& huffmanCode, std::unordered_map<char, std::string>& huffmanMap);
}


#endif //MAMBO_HUFFMANCODE_HPP
