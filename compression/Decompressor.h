#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H
#include<string>
#include "../io/BitReader.h"

class Decompressor{
private:
    std::string resolveCollision(const std::string& fileName);
    std::string getFileName(const std::string& fileName);
public:
    int decompress(const std::string &inputFile);
};
#endif