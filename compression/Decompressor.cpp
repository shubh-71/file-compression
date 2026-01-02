#include "Decompressor.h"

#include <fstream>
#include <vector>
#include <string>
#include <iostream>

#include "../huffman/HuffmanTree.h"
#include "../huffman/Node.h"
#include "../io/BitReader.h"

using namespace std;

/*
 * Prevent overwriting existing files by appending (1), (2), ...
 * Example: report.txt -> report(1).txt
 */
string Decompressor::resolveCollision(const string& filename) {
    ifstream test(filename, ios::binary);
    if (!test) return filename;

    size_t dot = filename.find_last_of('.');
    string base = (dot == string::npos) ? filename : filename.substr(0, dot);
    string ext  = (dot == string::npos) ? ""       : filename.substr(dot);

    
    int counter = 1;
    string newName;
    do {
        newName = base + "(" + to_string(counter) + ")" + ext;
        counter++;
    } while (ifstream(newName, ios::binary));

    return newName;
}

/*
 * Decide final output filename.
 * Currently: always keep original name and resolve collisions.
 * Hook exists for future user-renaming support.
 */
string Decompressor::getFileName(const string& originalName) {
    return resolveCollision(originalName);
}

string getBaseFileName(const string& inputFile) {
    size_t slash = inputFile.find_last_of("/\\");
    return (slash == string::npos)
            ? inputFile
            : inputFile.substr(slash + 1);
}

/*
 * Decompress a Huffman-compressed file
 *
 * Return values:
 *   1  -> success
 *   0  -> empty archive / nothing to decode
 *  -1  -> error or corrupted input
 */
int Decompressor::decompress(const string& inp) {

    /* ---------- 1. Open compressed file ---------- */
    ifstream in(inp, ios::binary);
    if (!in) {
        cerr << "Invalid file\n";
        return -1;
    }

    /* ---------- 1. Validate filename ---------- */

    string baseInput = getBaseFileName(inp);
    size_t dot = baseInput.find_last_of('.');
    if (dot == string::npos || baseInput.substr(dot) != ".huf") {
        cerr << "Invalid file format (expected .huf)\n";
        return -1;
    }



    /* ---------- 2. Read stored filename ---------- */
    unsigned char nameLen;
    in.read(reinterpret_cast<char*>(&nameLen), 1);

    string originalName(nameLen, '\0');
    in.read(&originalName[0], nameLen);

    /* ---------- 3. Read padding metadata ---------- */
    unsigned char paddingBits;
    in.read(reinterpret_cast<char*>(&paddingBits), 1);
    // Padding bits are ignored during decoding;
    // decoding stops using total byte count.

    /* ---------- 4. Read frequency table ---------- */
    vector<int> freq(256);
    for (int i = 0; i < 256; ++i) {
        in.read(reinterpret_cast<char*>(&freq[i]), sizeof(int));
    }

    /* ---------- 5. Compute total bytes to decode ---------- */
    int totalBytes = 0;
    for (int f : freq) {
        totalBytes += f;
    }

    /* ---------- 6. Rebuild Huffman tree ---------- */
    HuffmanTree tree(freq);
    Node* root = tree.getRoot();
    if (!root) {
        return 0;   // nothing to decode
    }

    /* ---------- 7. Open output file ---------- */
    string outputFile = getFileName(originalName);
    ofstream out(outputFile, ios::binary);
    if (!out) {
        cerr << "Failed to create output file\n";
        return -1;
    }

    /* ---------- 8. Handle single-symbol edge case ---------- */
    if (!root->left && !root->right) {
        unsigned char b = root->byte;
        for (int i = 0; i < totalBytes; ++i) {
            out.write(reinterpret_cast<char*>(&b), 1);
        }
        return 1;
    }

    /* ---------- 9. Decode bitstream ---------- */
    BitReader br(in);
    Node* currNode = root;
    int written = 0;

    while (written < totalBytes) {
        int bit = br.readBit();
        if (bit == -1) {
            cerr << "File is corrupted\n";
            return -1;
        }

        currNode = (bit == 0) ? currNode->left : currNode->right;

        if (!currNode->left && !currNode->right) {
            unsigned char b = currNode->byte;
            out.write(reinterpret_cast<char*>(&b), 1);
            currNode = root;
            written++;
        }
    }
    cout<<"Decompressed to : "<<outputFile<<endl;
    return 1;
}

/*
string Decompressor::getFileName(const string& fileName){
    // cout<<"\n Original file Name : "<<fileName<<endl;
    // cout<<"Do You wish to change that(y/n)"<<endl;
    // cout << "Press 'y' to change name, 'n' to keep original: ";
    // char choice;
    // cin>>choice;
    // if(choice=='n' || choice=='N') return resolveCollision(fileName);
    // else{
    //     size_t pos = fileName.find_last_of('.');
    //     string ext = (pos == string::npos) ? "" : fileName.substr(pos);
    //     cout<<"Enter file name without any spaces : ";
    //     string newFile;
    //     cin>>newFile;
    //     return resolveCollision(newFile+ext);
    // }

    return resolveCollision(fileName);
}
*/
