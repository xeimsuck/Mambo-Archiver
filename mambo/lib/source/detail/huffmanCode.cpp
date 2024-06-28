#include "huffmanCode.hpp"

struct mambo::detail::huffmanNode {
    char symbol = '\0';
    int frequency = 0;
    huffmanNode* left = nullptr;
    huffmanNode* right = nullptr;
};

struct mambo::detail::huffmanNodeComparator {
    bool operator()(huffmanNode*l, huffmanNode*r) { return l->frequency > r->frequency; }
};

void mambo::detail::deleteHuffmanNodeTree(mambo::detail::huffmanNode *root) {
    if(!root)return;
    deleteHuffmanNodeTree(root->left);
    deleteHuffmanNodeTree(root->right);
    delete root;
}

mambo::detail::huffmanNode* mambo::detail::getHuffmanCodes(const std::string &path) {
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
mambo::detail::huffmanNode* mambo::detail::getHuffmanCodes(const std::vector<std::string>& paths) {
    std::unordered_map<char, int> nodes;
    for(decltype(auto) path : paths){
        std::fstream stream(path, std::ios::in | std::ios::binary);
        std::string line;
        if(!stream.is_open()) return nullptr;
        while(std::getline(stream, line)){
            for(auto c : line) ++nodes[c];
            ++nodes['\n'];
        }
        stream.close();
    }
    return getHuffmanCodes(nodes);
}
mambo::detail::huffmanNode* mambo::detail::getHuffmanCodes(const std::unordered_map<char, int>& nodes) {
    if(nodes.empty()) return nullptr;

    std::priority_queue<huffmanNode*, std::vector<huffmanNode*>, huffmanNodeComparator> queue;

    for(decltype(auto) pair : nodes) {
        queue.push(new huffmanNode{pair.first, pair.second, nullptr, nullptr});
    }

    while(queue.size()>1){
        auto temp = new huffmanNode{'\0', 0, nullptr, nullptr};

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

void mambo::detail::convertHuffmanTreeToMap(mambo::detail::huffmanNode* root, std::unordered_map<char, std::string>& map){
    std::string code;
    convertHuffmanTreeToMap(root, code, map);
}
void mambo::detail::convertHuffmanTreeToMap(mambo::detail::huffmanNode *root, std::string& huffmanCode, std::unordered_map<char, std::string>& huffmanMap){
    if(!root) return;
    if(!root->left && !root->right) {
        huffmanMap[root->symbol] = huffmanCode;
        return;
    }
    huffmanCode.push_back(static_cast<char>(1));
    convertHuffmanTreeToMap(root->left, huffmanCode, huffmanMap);
    huffmanCode.pop_back();
    huffmanCode.push_back(static_cast<char>(0));
    convertHuffmanTreeToMap(root->right, huffmanCode, huffmanMap);
    huffmanCode.pop_back();
}