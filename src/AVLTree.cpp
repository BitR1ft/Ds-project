#include "../include/AVLTree.h"

Packet::Packet(const std::string& src, const std::string& dst, int p, 
               const std::string& proto, long ts, int sz)
    : sourceIP(src), destIP(dst), port(p), protocol(proto), timestamp(ts), size(sz) {}

AVLNode::AVLNode(Packet* packet) : data(packet), left(nullptr), right(nullptr), height(1) {}

AVLTree::AVLTree() : root(nullptr) {}

AVLTree::~AVLTree() {
    clear(root);
}

int AVLTree::getHeight(AVLNode* node) {
    return node ? node->height : 0;
}

int AVLTree::getBalance(AVLNode* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

AVLNode* AVLTree::rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    
    x->right = y;
    y->left = T2;
    
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    
    return x;
}

AVLNode* AVLTree::rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    
    y->left = x;
    x->right = T2;
    
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    
    return y;
}

AVLNode* AVLTree::insert(AVLNode* node, Packet* packet) {
    if (!node) {
        return new AVLNode(packet);
    }
    
    if (packet->timestamp < node->data->timestamp) {
        node->left = insert(node->left, packet);
    } else {
        node->right = insert(node->right, packet);
    }
    
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    
    int balance = getBalance(node);
    
    // Left Left
    if (balance > 1 && packet->timestamp < node->left->data->timestamp) {
        return rotateRight(node);
    }
    
    // Right Right
    if (balance < -1 && packet->timestamp > node->right->data->timestamp) {
        return rotateLeft(node);
    }
    
    // Left Right
    if (balance > 1 && packet->timestamp > node->left->data->timestamp) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    
    // Right Left
    if (balance < -1 && packet->timestamp < node->right->data->timestamp) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    
    return node;
}

void AVLTree::insert(Packet* packet) {
    root = insert(root, packet);
}

void AVLTree::inorder(AVLNode* node, void (*callback)(Packet*)) {
    if (!node) return;
    
    inorder(node->left, callback);
    callback(node->data);
    inorder(node->right, callback);
}

void AVLTree::traverse(void (*callback)(Packet*)) {
    inorder(root, callback);
}

void AVLTree::clear(AVLNode* node) {
    if (!node) return;
    
    clear(node->left);
    clear(node->right);
    delete node->data;
    delete node;
}
