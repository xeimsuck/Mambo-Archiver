#include "uncompress.hpp"

#include <fstream>
#include "detail/detail.hpp"
#include <iostream>

int mambo::uncompress(const char *archive, const char *where) {
    return mambo::uncompress(static_cast<std::string>(archive), static_cast<std::string>(where));
}
int mambo::uncompress(const std::string &archive, const std::string &where)  {
    std::fstream in(archive, std::ios::in | std::ios::binary);
    if(!in.is_open()) return 1;

    if(!detail::checkSignature(in)){
        in.close();
        return 1;
    }

    auto huffmanMap = detail::readHuffmanMap(in);
    if(huffmanMap.empty()){
        in.close();
        return 1;
    }

    std::size_t filesCount = 0;
    in.read(reinterpret_cast<char*>(&filesCount), sizeof(filesCount));
    for(int i = 0; i < filesCount; ++i){
        std::fstream out(where+detail::readFileName(in), std::ios::out);
        if(!out.is_open()) return 1;
        out << detail::readCompressedFile(in, huffmanMap);
        out.close();
    }

    in.close();

    return 0; // Success
}