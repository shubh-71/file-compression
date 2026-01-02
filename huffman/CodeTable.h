#ifndef CODETABLE_H
#define CODETABLE_H

#include <vector>
#include <string>

class CodeTable {
private:
    std::vector<std::string> codes;   // size = 256

public:
    CodeTable();

    void set(unsigned char byte, const std::string& code);
    const std::string& get(unsigned char byte) const;

    bool hasCode(unsigned char byte) const;
};

#endif
