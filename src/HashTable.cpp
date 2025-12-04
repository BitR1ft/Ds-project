#include "../include/HashTable.h"

HashNode::HashNode(const std::string& k, const std::string& v) 
    : key(k), value(v), next(nullptr) {}

HashTable::HashTable() {
    table.resize(TABLE_SIZE, nullptr);
}

HashTable::~HashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode* current = table[i];
        while (current) {
            HashNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
}

int HashTable::hashFunction(const std::string& key) {
    unsigned long hash = 5381;
    for (char c : key) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % TABLE_SIZE;
}

void HashTable::insert(const std::string& key, const std::string& value) {
    int index = hashFunction(key);
    
    HashNode* current = table[index];
    while (current) {
        if (current->key == key) {
            current->value = value;
            return;
        }
        current = current->next;
    }
    
    HashNode* newNode = new HashNode(key, value);
    newNode->next = table[index];
    table[index] = newNode;
}

std::string HashTable::get(const std::string& key) {
    int index = hashFunction(key);
    HashNode* current = table[index];
    
    while (current) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    
    return "";
}

bool HashTable::contains(const std::string& key) {
    int index = hashFunction(key);
    HashNode* current = table[index];
    
    while (current) {
        if (current->key == key) {
            return true;
        }
        current = current->next;
    }
    
    return false;
}

void HashTable::remove(const std::string& key) {
    int index = hashFunction(key);
    HashNode* current = table[index];
    HashNode* prev = nullptr;
    
    while (current) {
        if (current->key == key) {
            if (prev) {
                prev->next = current->next;
            } else {
                table[index] = current->next;
            }
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
}

std::vector<std::string> HashTable::getAllKeys() {
    std::vector<std::string> keys;
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode* current = table[i];
        while (current) {
            keys.push_back(current->key);
            current = current->next;
        }
    }
    
    return keys;
}
