#include "BitReader.h"

BitReader::BitReader(std::ifstream &in):in(in),
                    buffer(0),bitPos(8){}

int BitReader::readBit(){
    if(bitPos==8){
        char raw;
        if(!in.get(raw)) return -1;
        buffer=static_cast<unsigned char>(raw);
        bitPos=0;
    }
    int bit=( buffer>> (7-bitPos)) & 1;
    bitPos++;
    return bit;
}