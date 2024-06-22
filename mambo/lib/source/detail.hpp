#ifndef MAMBO_DETAIL_HPP
#define MAMBO_DETAIL_HPP

#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>

namespace mambo::detail {
    // Struct which stay first in .mam
    struct header {
        long size;
        long characterTable;
        // Table..
    };
    struct node {
        char symbol;
        int frequency;
        node* left = nullptr;
        node* right = nullptr;
    };
    struct nodecomparator {
        bool operator()(node*l, node*r) { return l->frequency>r->frequency; }
    };

    void deleteNodeTree(node* root);

    int getFileSize(const std::string& path);
    int getFileSize(const std::vector<std::string>& paths);

    node* getHuffmanCodes(const std::string& path);
    node* getHuffmanCodes(const std::vector<std::string>& paths);
    node* getHuffmanCodes(const std::unordered_map<char, int>& nodes);

    void getBits(node* root, std::unordered_map<char, std::vector<int>>& map);
    void getBits(node* root, std::vector<int>&v, std::unordered_map<char, std::vector<int>>& map);

    std::string writeBits(const std::string& file, std::unordered_map<char, std::vector<int>>& map);
}

#endif //MAMBO_DETAIL_HPP
