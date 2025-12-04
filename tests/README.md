# Test Suite for Integrated Cyber Threat Detection Suite

This directory contains test cases for validating the correctness of all modules and data structures.

## Test Files

- `test_trie.cpp` - Unit tests for Trie data structure
- `test_aho_corasick.cpp` - Unit tests for Aho-Corasick automaton
- `test_graph.cpp` - Unit tests for Graph data structure
- `test_avl_tree.cpp` - Unit tests for AVL Tree
- `test_priority_queue.cpp` - Unit tests for Max-Heap
- `test_hash_table.cpp` - Unit tests for Hash Table
- `test_linked_list.cpp` - Unit tests for Linked List

## Running Tests

Each test file can be compiled and run independently:

```bash
# Compile a test
g++ -std=c++17 -I../include test_trie.cpp ../src/Trie.cpp -o test_trie

# Run the test
./test_trie
```

## Test Coverage

### Data Structures Tests
- Insert operations
- Search operations
- Delete operations
- Edge cases (empty, single element, large datasets)
- Memory management

### Module Tests
- Malware detection accuracy
- Ransomware behavior patterns
- Network intrusion detection
- Report generation

## Expected Results

All tests should pass with 100% success rate.
