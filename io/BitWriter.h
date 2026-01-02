#ifndef BITWRITER_H
#define BITWRITER_H
#include<string>
#include<fstream>

class BitWriter{
private:
    std::ofstream &out;
    unsigned char buffer;
    int bitCount;
public:
    explicit BitWriter(std::ofstream &out);
    void writeBit(int bit);
    void writeBits(const std::string &bits);
    int flush();
};
#endif