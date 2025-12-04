#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <string>
#include <vector>

struct HashNode {
    std::string key;
    std::string value;
    HashNode* next;
    
    HashNode(const std::string& k, const std::string& v);
};

class HashTable {
private:
    static const int TABLE_SIZE = 1000;
    std::vector<HashNode*> table;
    
    int hashFunction(const std::string& key);
    
public:
    HashTable();
    ~HashTable();
    
    void insert(const std::string& key, const std::string& value);
    std::string get(const std::string& key);
    bool contains(const std::string& key);
    void remove(const std::string& key);
    std::vector<std::string> getAllKeys();
};

#endif // HASH_TABLE_H
