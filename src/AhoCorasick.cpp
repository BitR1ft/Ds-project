#include "../include/AhoCorasick.h"
#include <iostream>

ACNode::ACNode() : failure(nullptr) {}

AhoCorasick::AhoCorasick() {
    root = new ACNode();
    root->failure = root;
}

AhoCorasick::~AhoCorasick() {
    clear(root);
}

void AhoCorasick::addPattern(const std::string& pattern) {
    ACNode* current = root;
    
    for (char ch : pattern) {
        if (current->children.find(ch) == current->children.end()) {
            current->children[ch] = new ACNode();
        }
        current = current->children[ch];
    }
    
    current->output.push_back(pattern);
}

void AhoCorasick::buildFailureLinks() {
    std::queue<ACNode*> q;
    
    // Initialize first level
    for (auto& pair : root->children) {
        pair.second->failure = root;
        q.push(pair.second);
    }
    
    // BFS to build failure links
    while (!q.empty()) {
        ACNode* current = q.front();
        q.pop();
        
        for (auto& pair : current->children) {
            char ch = pair.first;
            ACNode* child = pair.second;
            q.push(child);
            
            ACNode* f = current->failure;
            while (f != root && f->children.find(ch) == f->children.end()) {
                f = f->failure;
            }
            
            if (f->children.find(ch) != f->children.end() && f->children[ch] != child) {
                child->failure = f->children[ch];
            } else {
                child->failure = root;
            }
            
            // Merge outputs
            for (const auto& pattern : child->failure->output) {
                child->output.push_back(pattern);
            }
        }
    }
}

void AhoCorasick::build() {
    buildFailureLinks();
}

std::vector<std::pair<int, std::string>> AhoCorasick::search(const std::string& text) {
    std::vector<std::pair<int, std::string>> matches;
    ACNode* current = root;
    
    for (int i = 0; i < text.length(); i++) {
        char ch = text[i];
        
        while (current != root && current->children.find(ch) == current->children.end()) {
            current = current->failure;
        }
        
        if (current->children.find(ch) != current->children.end()) {
            current = current->children[ch];
        }
        
        for (const auto& pattern : current->output) {
            matches.push_back({i - pattern.length() + 1, pattern});
        }
    }
    
    return matches;
}

void AhoCorasick::clear(ACNode* node) {
    if (!node) return;
    
    for (auto& pair : node->children) {
        clear(pair.second);
    }
    
    delete node;
}
