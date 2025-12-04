#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <unordered_map>
#include <vector>

class TrieNode {
public:
    std::unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
    std::string pattern;  // Store the complete pattern at leaf nodes
    
    TrieNode();
};

class Trie {
private:
    TrieNode* root;
    
public:
    Trie();
    ~Trie();
    
    void insert(const std::string& word);
    bool search(const std::string& word);
    TrieNode* getRoot();
    void clear(TrieNode* node);
};

#endif // TRIE_H
