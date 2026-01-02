#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include <string>

class Compressor {
private:
    std::string resolveCollision(const std::string& fileName);
    std::string getBaseFileName(const std::string &inputFile);
    std::string getOutputFileName(const std::string& baseName);
public:
    int compress(const std::string& inputFile);
};

#endif
