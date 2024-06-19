#ifndef MAMBO_DETAIL_HPP
#define MAMBO_DETAIL_HPP

#include <fstream>
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

    int getFileSize(std::fstream& stream);
    int getFileSize(const std::string& path);
    node* getHuffmanCodes(std::fstream& stream);
}

#endif //MAMBO_DETAIL_HPP
