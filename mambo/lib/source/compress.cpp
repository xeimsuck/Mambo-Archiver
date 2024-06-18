#include "compress.hpp"

int mambo::compress(const char* path, unsigned n, const char** files){
    return 0; // Return compress ration
}

int mambo::compress(const std::string& path, const std::vector<std::string>& files){
    std::vector<const char*> filesPointers(files.size());
    for(int i = 0; i < filesPointers.size(); ++i)
        filesPointers[i] = files[i].c_str();
    return compress(path.c_str(), filesPointers.size(), filesPointers.data());
}