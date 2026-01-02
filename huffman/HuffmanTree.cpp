#include "HuffmanTree.h"
#include<queue>

using namespace std;

struct Compare{
    bool operator()(Node *a,Node *b){
        return a->freq>b->freq;
    }
};
void HuffmanTree::deleteDfs(Node* curr){
    if(!curr) return;
    queue<Node*> q;
    q.push(curr);
    while(!q.empty()){
        Node* node=q.front();
        q.pop();
        if(node->left)q.push(node->left);
        if(node->right)q.push(node->right);
        delete(node);
    }
}
HuffmanTree::~HuffmanTree(){
    deleteDfs(root);
    root=nullptr;
}
HuffmanTree::HuffmanTree(const vector<int> &freq){
    priority_queue<Node*, vector<Node*>,Compare> pq;
    for(int i=0;i<256;++i){
        if(freq[i]>0){
            Node* n=new Node(static_cast<unsigned char>(i),freq[i]);
            pq.push(n);
        }
    }
    while(pq.size()>1){
        Node* n=new Node;
        n->left=pq.top();
        pq.pop();
        n->right=pq.top();
        pq.pop();
        n->freq=n->left->freq+n->right->freq;
        pq.push(n);
    }
    root= pq.empty()?nullptr:pq.top();
}

    void HuffmanTree::dfs(Node* node,string path,CodeTable &table){
    if(!node) return;
    if(!node->left && !node->right){
        if(path.empty()) path="0";
        table.set(node->byte,path);
        return;
    }
    dfs(node->left,path+"0",table);
    dfs(node->right,path+"1",table);
    }

    
    Node* HuffmanTree::getRoot(){
        return root;
    }


    void HuffmanTree::generateCodes(CodeTable &table){
        dfs(root,"",table);
    }
