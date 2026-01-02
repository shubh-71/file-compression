#include <iostream>
#include <string>

#include "compression/Compressor.h"
#include "compression/Decompressor.h"

using namespace std;

/*
 * CLI usage:
 *   myzip -c <file>   -> compress
 *   myzip -d <file>   -> decompress
 *
 * Exit codes:
 *   0 -> success
 *   1 -> user / input error
 *   2 -> file or processing error
 */
int main(int argc, char* argv[]) {

    /* ---------- Argument validation ---------- */
    if (argc != 3) {
        cerr << "Usage:\n"
             << "  myzip -c <file>   Compress file\n"
             << "  myzip -d <file>   Decompress file\n";
        return 1;
    }

    string option = argv[1];
    string file   = argv[2];

    /* ---------- Compression ---------- */
    if (option == "-c") {
        Compressor compressor;
        int result = compressor.compress(file);

        if (result == 1) {
            return 0;   // success
        }
        else if (result == 0) {
            // empty file is not an error, but nothing was done
            cerr << "Nothing to compress.\n";
            return 0;
        }
        else {
            // result == -1
            return 2;
        }
    }

    /* ---------- Decompression ---------- */
    else if (option == "-d") {
        Decompressor decompressor;
        int result = decompressor.decompress(file);

        if (result == 1) {
            return 0;   // success
        }
        else if (result == 0) {
            cerr << "Nothing to decompress.\n";
            return 0;
        }
        else {
            return 2;
        }
    }

    /* ---------- Invalid option ---------- */
    else {
        cerr << "Invalid option: " << option << "\n"
             << "Use -c to compress or -d to decompress.\n";
        return 1;
    }
}
