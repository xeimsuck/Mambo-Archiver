#include "uncompress.hpp"

int mambo::uncompress(const char *archive, const char *where) {
    return 0; // Return 0 if success
}
int mambo::uncompress(const std::string &archive, const std::string &where)  {
    return uncompress(archive.c_str(), where.c_str());
}