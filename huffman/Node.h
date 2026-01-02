#ifndef NODE_H
#define NODE_H

struct Node{
    unsigned char byte;
    int freq;
    Node *left,*right;
    Node(){
        left=right=nullptr;
        freq=0;
    }
    Node(unsigned char val,int freq){
        this->byte=val;
        this->freq=freq;
        this->left=nullptr;
        this->right=nullptr;
    }
};
#endif