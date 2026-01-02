# 🗜️ MyZip — Huffman File Compression Tool (C++)

MyZip is a **binary-safe file compression and decompression utility** implemented in C++ using **Huffman Coding**.
It supports text and binary files, preserves original filenames, handles collisions safely, and provides a simple CLI interface.

This project focuses on **correctness, clean architecture, and real-world behavior**, not shortcuts.

---

## ✨ Features

* Huffman compression & decompression
* Works with **any file type** (text, images, binaries)
* Stores original filename metadata
* User can rename output during decompression
* Automatic filename collision handling
  (`file.txt → file(1).txt`)
* Memory-safe tree cleanup
* Binary-safe I/O
* Simple command-line interface

---

## 📁 Project Structure

```
project/
├── main.cpp
├── compression/
│   ├── Compressor.h
│   ├── Compressor.cpp
│   ├── Decompressor.h
│   └── Decompressor.cpp
├── huffman/
│   ├── Node.h
│   ├── HuffmanTree.h
│   └── HuffmanTree.cpp
├── io/
│   ├── BitWriter.h
│   ├── BitWriter.cpp
│   ├── BitReader.h
│   └── BitReader.cpp
└── README.md
```

---

## ⚙️ Build Instructions

### Requirements

* C++17 compatible compiler
* `g++` (Linux / macOS)

### Compile

From the **project root**:

```bash
g++ -std=c++17 -Wall -Wextra -O2  main.cpp compression/*.cpp huffman/*.cpp io/*.cpp -o myzip
```

If successful, this creates the executable:
```
myzip
```

---

## 🚀 Usage

### Compress a file

```bash
./myzip -c inputfile
```

Example:

```bash
./myzip -c notes.txt
```

Output:

```
notescompressed.bin
```

---

### Decompress a file

```bash
./myzip -d compressedfile
```

Example:

```bash
./myzip -d notescompressed.bin
```

During decompression:

* Original filename is shown
* You can keep it or rename
* Name collisions are resolved automatically

---

## 🧠 How It Works (High-Level)

1. **Compression**

   * Reads input file
   * Builds frequency table
   * Constructs Huffman Tree
   * Encodes file as a bitstream
   * Writes metadata + compressed bits

2. **Decompression**

   * Reads metadata
   * Rebuilds Huffman Tree
   * Reads bits one-by-one
   * Traverses tree to recover original bytes

Padding bits are handled implicitly by decoding only the required number of bytes.

---

## 🛡️ Safety & Robustness

* No overwriting of existing files
* Graceful handling of corrupted input
* Automatic memory cleanup via tree destructor
* Binary-safe read/write throughout

---

## 📌 Limitations

* Compresses **single files only** (no directories yet)
* No checksum or versioning (planned)
* Compression ratio depends on data entropy

---

## 🔮 Possible Extensions

* Checksum validation (CRC32)
* Format versioning
* Directory compression
* Multithreaded compression
* Encryption layer
* Cross-platform packaging

---

## 📜 License

This project is provided for **educational and learning purposes**.
You are free to modify, extend, and experiment with it.

---

## 🙌 Acknowledgements

* Huffman Coding (David A. Huffman)
* C++ Standard Library

---

## 🧩 Final Note

This project demonstrates:

* data structures
* file format design
* bit-level I/O
* real-world systems thinking


---