/**
 * Simple Trie Implementation
 * Demonstrates basic Trie operations for Session 3
 * 
 * Compile: g++ -std=c++17 simple-trie.cpp -o trie_demo
 * Run: ./trie_demo
 */

#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

// Node in the Trie
class TrieNode {
public:
    unordered_map<char, TrieNode*> children;  // Map char → child node
    bool isEndOfWord;                          // Marks complete word
    string word;                               // Store the word itself
    
    TrieNode() {
        isEndOfWord = false;
        word = "";
    }
};

// Trie data structure
class Trie {
private:
    TrieNode* root;
    
public:
    Trie() {
        root = new TrieNode();
    }
    
    // Insert a word into the Trie
    void insert(const string& word) {
        TrieNode* current = root;
        
        cout << "Inserting '" << word << "': ";
        
        // For each character in the word
        for (char ch : word) {
            cout << ch;
            
            // If path doesn't exist, create it
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new TrieNode();
                cout << "(new) ";
            } else {
                cout << "(exists) ";
            }
            
            // Move to next node
            current = current->children[ch];
        }
        
        // Mark end of word
        current->isEndOfWord = true;
        current->word = word;
        cout << " ✓" << endl;
    }
    
    // Search for a word in the Trie
    bool search(const string& word) {
        TrieNode* current = root;
        
        // Try to follow the path
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                return false;  // Path doesn't exist
            }
            current = current->children[ch];
        }
        
        // Check if it's marked as end of word
        return current->isEndOfWord;
    }
    
    // Check if any word starts with given prefix
    bool startsWith(const string& prefix) {
        TrieNode* current = root;
        
        // Try to follow the path
        for (char ch : prefix) {
            if (current->children.find(ch) == current->children.end()) {
                return false;  // Prefix doesn't exist
            }
            current = current->children[ch];
        }
        
        return true;  // Prefix exists
    }
    
    // Get Trie statistics
    void getStats(TrieNode* node, int& nodeCount, int& wordCount) {
        if (node == nullptr) return;
        
        nodeCount++;
        if (node->isEndOfWord) wordCount++;
        
        for (auto& pair : node->children) {
            getStats(pair.second, nodeCount, wordCount);
        }
    }
    
    void printStats() {
        int nodeCount = 0, wordCount = 0;
        getStats(root, nodeCount, wordCount);
        cout << "\nTrie Statistics:" << endl;
        cout << "  Total nodes: " << nodeCount << endl;
        cout << "  Total words: " << wordCount << endl;
    }
};

int main() {
    cout << "=== Simple Trie Demo ===" << endl << endl;
    
    // Create Trie
    Trie trie;
    
    // Insert words
    cout << "1. Inserting words:" << endl;
    trie.insert("cat");
    trie.insert("car");
    trie.insert("card");
    trie.insert("dog");
    trie.insert("dodge");
    
    // Print statistics
    trie.printStats();
    
    // Search for words
    cout << "\n2. Searching for words:" << endl;
    string searchWords[] = {"cat", "car", "card", "ca", "do", "dodge", "elephant"};
    
    for (const string& word : searchWords) {
        bool found = trie.search(word);
        cout << "  '" << word << "': " << (found ? "✓ Found" : "✗ Not found") << endl;
    }
    
    // Check prefixes
    cout << "\n3. Checking prefixes:" << endl;
    string prefixes[] = {"ca", "do", "car", "ele"};
    
    for (const string& prefix : prefixes) {
        bool hasPrefix = trie.startsWith(prefix);
        cout << "  Words starting with '" << prefix << "': " 
             << (hasPrefix ? "✓ Yes" : "✗ No") << endl;
    }
    
    // Demonstrate efficiency
    cout << "\n4. Efficiency demonstration:" << endl;
    cout << "  Notice how 'cat', 'car', and 'card' share the 'ca' prefix!" << endl;
    cout << "  They reuse the same nodes for 'c' and 'a'." << endl;
    cout << "  This is why Tries are space-efficient for many words." << endl;
    
    cout << "\n=== Demo Complete ===" << endl;
    
    return 0;
}
