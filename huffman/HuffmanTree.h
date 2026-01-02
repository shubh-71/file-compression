#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include "CodeTable.h"
#include<string>
#include<vector>
#include "Node.h"

class HuffmanTree{
private:
    Node* root;
    void dfs(Node* node, std::string path,CodeTable& table);
    void deleteDfs(Node* curr);
public:
    HuffmanTree(const std::vector<int>& freq);
    ~HuffmanTree();
    void generateCodes(CodeTable &table);
    Node* getRoot();
};
#endif