#include "detail.hpp"

#include <unordered_map>
#include <queue>
#include <iostream>

int mambo::detail::getFileSize(std::fstream &stream){
    const auto prev = stream.tellg();
    stream.seekg(std::ios::end);
    const auto size = stream.tellg();
    stream.seekg(prev);
    return static_cast<int>(size);
}

int mambo::detail::getFileSize(const std::string &path) {
    std::fstream stream(path, std::ios::binary);
    if(!stream.is_open()) return -1;
    int size = getFileSize(stream);
    stream.close();
    return size;
}

bool fun(mambo::detail::node* l, mambo::detail::node* r) {
    return l->frequency > r->frequency;
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

    for(auto pair : nodes) {
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

std::string mambo::detail::writeBits(const std::string &file, const std::unordered_map<char, std::vector<int>>& map) {
    std::string result;

    std::fstream stream (file, std::ios::in | std::ios::binary);
    if(!stream.is_open()) return "";

    stream.close();

    return result;
}