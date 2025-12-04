#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <string>
#include <algorithm>

struct Packet {
    std::string sourceIP;
    std::string destIP;
    int port;
    std::string protocol;
    long timestamp;
    int size;
    
    Packet(const std::string& src, const std::string& dst, int p, 
           const std::string& proto, long ts, int sz);
};

class AVLNode {
public:
    Packet* data;
    AVLNode* left;
    AVLNode* right;
    int height;
    
    AVLNode(Packet* packet);
};

class AVLTree {
private:
    AVLNode* root;
    
    int getHeight(AVLNode* node);
    int getBalance(AVLNode* node);
    AVLNode* rotateRight(AVLNode* y);
    AVLNode* rotateLeft(AVLNode* x);
    AVLNode* insert(AVLNode* node, Packet* packet);
    void inorder(AVLNode* node, void (*callback)(Packet*));
    void clear(AVLNode* node);
    
public:
    AVLTree();
    ~AVLTree();
    
    void insert(Packet* packet);
    void traverse(void (*callback)(Packet*));
};

#endif // AVL_TREE_H
