#include "CodeTable.h"

CodeTable::CodeTable() : codes(256) {}

void CodeTable::set(unsigned char byte, const std::string& code) {
    codes[byte] = code;
}

const std::string& CodeTable::get(unsigned char byte) const {
    return codes[byte];
}

bool CodeTable::hasCode(unsigned char byte) const {
    return !codes[byte].empty();
}
