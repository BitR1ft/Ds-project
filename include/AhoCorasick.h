#ifndef AHO_CORASICK_H
#define AHO_CORASICK_H

#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

class ACNode {
public:
    std::unordered_map<char, ACNode*> children;
    ACNode* failure;
    std::vector<std::string> output;  // Patterns that end at this node
    
    ACNode();
};

class AhoCorasick {
private:
    ACNode* root;
    
    void buildFailureLinks();
    
public:
    AhoCorasick();
    ~AhoCorasick();
    
    void addPattern(const std::string& pattern);
    void build();
    std::vector<std::pair<int, std::string>> search(const std::string& text);
    void clear(ACNode* node);
};

#endif // AHO_CORASICK_H
