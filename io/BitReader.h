#ifndef BITREADER_H
#define BITREADER_H

#include<fstream>
class BitReader{
private:
    std::ifstream &in;
    unsigned char buffer;
    int bitPos;
public:
    explicit BitReader(std::ifstream &in);
    int readBit();
};
#endif