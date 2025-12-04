#include "../include/Trie.h"

TrieNode::TrieNode() : isEndOfWord(false) {}

Trie::Trie() {
    root = new TrieNode();
}

Trie::~Trie() {
    clear(root);
}

void Trie::insert(const std::string& word) {
    TrieNode* current = root;
    
    for (char ch : word) {
        if (current->children.find(ch) == current->children.end()) {
            current->children[ch] = new TrieNode();
        }
        current = current->children[ch];
    }
    
    current->isEndOfWord = true;
    current->pattern = word;
}

bool Trie::search(const std::string& word) {
    TrieNode* current = root;
    
    for (char ch : word) {
        if (current->children.find(ch) == current->children.end()) {
            return false;
        }
        current = current->children[ch];
    }
    
    return current->isEndOfWord;
}

TrieNode* Trie::getRoot() {
    return root;
}

void Trie::clear(TrieNode* node) {
    if (!node) return;
    
    for (auto& pair : node->children) {
        clear(pair.second);
    }
    
    delete node;
}
