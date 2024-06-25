#include "detail.hpp"

#include <unordered_map>
#include <filesystem>
#include <queue>
#include <iostream>

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

mambo::detail::node* mambo::detail::getHuffmanCodes(const std::string &path) {
    std::unordered_map<char, int> nodes;
    std::fstream stream(path, std::ios::in | std::ios::binary);
    std::string line;
    if(!stream.is_open()) return nullptr;
    while(std::getline(stream, line)){
        for(auto c : line) ++nodes[c];
    }
    stream.close();
    return getHuffmanCodes(nodes);
}

mambo::detail::node* mambo::detail::getHuffmanCodes(const std::vector<std::string>& paths) {
    std::unordered_map<char, int> nodes;
    for(decltype(auto) path : paths){
        std::fstream stream(path, std::ios::in | std::ios::binary);
        std::string line;
        if(!stream.is_open()) return nullptr;
        while(std::getline(stream, line)){
            for(auto c : line) ++nodes[c];
        }
        stream.close();
    }
    return getHuffmanCodes(nodes);
}

mambo::detail::node* mambo::detail::getHuffmanCodes(const std::unordered_map<char, int>& nodes) {
    if(nodes.empty()) return nullptr;

    std::priority_queue<node*, std::vector<node*>, nodecomparator> queue;

    for(decltype(auto) pair : nodes) {
        queue.push(new node{pair.first, pair.second, nullptr, nullptr});
    }

    while(queue.size()>1){
        node* temp = new node{'\0', 0, nullptr, nullptr};

        temp->left = queue.top();
        temp->frequency+=temp->left->frequency;
        queue.pop();

        if(!queue.empty()){
            temp->right = queue.top();
            temp->frequency+=temp->right->frequency;
            queue.pop();
        }

        queue.push(temp);
    }

    return queue.top();
}

void mambo::detail::deleteNodeTree(mambo::detail::node *root) {
    if(!root)return;
    deleteNodeTree(root->left);
    deleteNodeTree(root->right);
    delete root;
}

void mambo::detail::getBits(mambo::detail::node* root, std::unordered_map<char, std::vector<int>>& map){
    std::vector<int> tmp;
    getBits(root, tmp, map);
}

void mambo::detail::getBits(mambo::detail::node* root, std::vector<int>&v, std::unordered_map<char, std::vector<int>>& map){
    if(!root) return;
    if(!root->left && !root->right) {
        map[root->symbol] = v;
        return;
    }
    v.push_back(1);
    getBits(root->left, v, map);
    v.pop_back();
    v.push_back(0);
    getBits(root->right, v, map);
    v.pop_back();
}

std::string mambo::detail::writeBits(const std::string &file, std::unordered_map<char, std::vector<int>>& map) {
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

bool mambo::detail::checkSignature(const std::string &path) {
    std::fstream stream(path, std::ios::in | std::ios::binary);
    if(!stream.is_open()) return false;
    std::string signature(SIGNATURE.size(), ' ');
    stream.read(signature.data(), SIGNATURE.size());
    stream.close();
    return signature==SIGNATURE;
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

std::string mambo::detail::findHuffmanMap(const std::string &path) {
    if(!checkSignature(path)) return "";

    std::fstream stream(path, std::ios::in | std::ios::binary);
    if(!stream.is_open()) return "";

    size_t size;
    char signature[SIGNATURE.size()+1];
    stream >> signature >> size;

    std::string result(size, '9');
    stream.read(result.data(), size);
    return result;
}

std::unordered_map<char, std::vector<int>> mambo::detail::readHuffmanMap(const std::string& bytes) {
    std::unordered_map<char, std::vector<int>> map;

    for(int i = 0; i < bytes.size();++i){
        char symbol = bytes[i++];
        char size = bytes[i++];

        std::vector<int> v;
        for(int j = 0; j<((size-1)/8); ++j){
            for(int k = 7; k >= 0; --k) {
                v.push_back(std::abs((bytes[i] >> k)%2));
            }
            ++i;
        }
        for(int k = 7; k >= 7-(size-1)%8; --k) {
            v.push_back(std::abs((bytes[i] >> k)%2));
        }
        map[symbol] = std::move(v);
    }
    return map;
}