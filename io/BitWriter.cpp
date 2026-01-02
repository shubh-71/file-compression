#include "BitWriter.h"

using namespace std;
BitWriter::BitWriter(ofstream &out): out(out),buffer(0),bitCount(0){}

void BitWriter::writeBit(int bit){
    buffer=(buffer << 1) | (bit&1);
        bitCount++;
        if(bitCount==8){
            out.put(buffer);
            buffer=0;
            bitCount=0;
        }
}

void BitWriter::writeBits(const string &bits){
    for(char b:bits){
        writeBit(b=='1');
    }
}
int BitWriter::flush(){
    int padding=0;
    if(bitCount>0){
        padding= 8-bitCount;
        buffer <<= padding;
        out.put(buffer);
    }
    buffer=0;
    bitCount=0;
    return padding;
}
