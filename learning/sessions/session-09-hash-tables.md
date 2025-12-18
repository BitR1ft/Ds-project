# Session 9: Hash Tables

**Duration:** 60-75 minutes  
**Goal:** Master fast lookups with hashing

## Hash Tables Explained
Map keys to values using hash function:
- Key → Hash Function → Index → Value

## Hash Functions
Convert key to array index:
```cpp
int hash(string key) {
    int sum = 0;
    for (char c : key) sum += c;
    return sum % tableSize;
}
```

## Collision Handling
Two methods:
1. **Chaining** - Linked list at each slot (we use this!)
2. **Open Addressing** - Find next empty slot

## Performance
- Insert: O(1) average
- Search: O(1) average
- Delete: O(1) average

## IP Blacklist
- Map IP → Threat Info
- Instant lookup: Is this IP malicious?
- ~1000× faster than linear search!

See you in Session 10!
