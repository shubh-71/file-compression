#include "Compressor.h"

#include <fstream>
#include <vector>
#include <string>
#include <iostream>

#include "../huffman/HuffmanTree.h"
#include "../huffman/CodeTable.h"
#include "../io/BitWriter.h"

using namespace std;

/*
 * Prevent overwriting existing files by appending (1), (2), ...
 * Example: file.huf -> file(1).huf
 */
string Compressor::resolveCollision(const string& fileName) {
    ifstream test(fileName, ios::binary);
    if (!test) return fileName;

    size_t dot = fileName.find_last_of('.');
    string base = (dot == string::npos) ? fileName : fileName.substr(0, dot);
    string ext  = (dot == string::npos) ? ""       : fileName.substr(dot);

    int counter = 1;
    string newName;
    do {
        newName = base + "(" + to_string(counter) + ")" + ext;
        counter++;
    } while (ifstream(newName, ios::binary));

    return newName;
}

/*
 * Generate archive filename from payload filename
 * Example: report.txt -> report-compressed.huf
 */
string Compressor::getOutputFileName(const string& baseName) {
    size_t dot = baseName.find_last_of('.');
    string stem = (dot == string::npos)
                    ? baseName
                    : baseName.substr(0, dot);

    return resolveCollision(stem + "-compressed.huf");
}

/*
 * Extract base filename from full path
 * Example: /home/user/docs/report.txt -> report.txt
 */
string Compressor::getBaseFileName(const string& inputFile) {
    size_t slash = inputFile.find_last_of("/\\");
    return (slash == string::npos)
            ? inputFile
            : inputFile.substr(slash + 1);
}

/*
 * Compress a file using Huffman coding
 * Return values:
 *   1  -> success
 *   0  -> empty input file
 *  -1  -> error
 */
int Compressor::compress(const string& inputFile) {

    /* ---------- 1. Open input file ---------- */
    ifstream in(inputFile, ios::binary);
    if (!in) {
        cerr << "Cannot open input file\n";
        return -1;
    }

    /* ---------- 2. Frequency analysis ---------- */
    vector<int> freq(256, 0);
    char byte;
    while (in.get(byte)) {
        freq[static_cast<unsigned char>(byte)]++;
    }

    /* ---------- 3. Check for empty file ---------- */
    bool empty = true;
    for (int f : freq) {
        if (f > 0) {
            empty = false;
            break;
        }
    }

    if (empty) {
        cerr << "Input file is empty. Nothing to compress.\n";
        return 0;
    }

    in.close();

    /* ---------- 4. Build Huffman tree ---------- */
    HuffmanTree tree(freq);
    CodeTable table;
    tree.generateCodes(table);

    /* ---------- 5. Determine filenames ---------- */
    string baseName   = getBaseFileName(inputFile);      // payload name
    string outputFile = getOutputFileName(baseName);     // archive name

    /* ---------- 6. Open output file ---------- */
    ofstream out(outputFile, ios::binary);
    if (!out) {
        cerr << "Cannot create output file\n";
        return -1;
    }

    /* ---------- 7. Write filename metadata ---------- */
    unsigned char nameLen = static_cast<unsigned char>(baseName.size());
    out.put(nameLen);
    out.write(baseName.c_str(), nameLen);

    /* ---------- 8. Padding placeholder ---------- */
    streampos paddingPos = out.tellp();
    out.put(0);  // placeholder, patched later

    /* ---------- 9. Write frequency table ---------- */
    for (int i = 0; i < 256; i++) {
        out.write(reinterpret_cast<char*>(&freq[i]), sizeof(int));
    }

    /* ---------- 10. Encode file ---------- */
    in.clear();
    in.open(inputFile, ios::binary);

    BitWriter bw(out);
    while (in.get(byte)) {
        bw.writeBits(table.get(static_cast<unsigned char>(byte)));
    }

    int paddingBits = bw.flush();

    /* ---------- 11. Patch padding metadata ---------- */
    out.seekp(paddingPos);
    out.put(static_cast<unsigned char>(paddingBits));

    in.close();
    out.close();

    cout << "Compressed to : " << outputFile << endl;
    return 1;
}
