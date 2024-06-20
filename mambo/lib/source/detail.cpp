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


mambo::detail::node* mambo::detail::getHuffmanCodes(std::fstream &stream) {
    std::unordered_map<char, int> nodes;
    std::string line;
    while(std::getline(stream, line)){
        for(auto c : line) ++nodes[c];
    }

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

void mambo::detail::deletenodetree(mambo::detail::node *root) {
    if(!root)return;
    deletenodetree(root->left);
    deletenodetree(root->right);
    delete root;
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