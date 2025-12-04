# Contributing to Integrated Cyber Threat Detection Suite

Thank you for your interest in contributing to this project! This document provides guidelines for extending and improving the system.

## Table of Contents
1. [Getting Started](#getting-started)
2. [Project Structure](#project-structure)
3. [Adding New Features](#adding-new-features)
4. [Code Style Guidelines](#code-style-guidelines)
5. [Testing](#testing)
6. [Documentation](#documentation)

---

## Getting Started

### Prerequisites
- C++ compiler (g++ 7.0+)
- Make utility
- Git for version control
- Text editor or IDE

### Setting Up Development Environment

```bash
# Clone the repository
git clone https://github.com/BitR1ft/Ds-project.git
cd Ds-project

# Build the project
make

# Run tests
./threat_detection_suite
```

---

## Project Structure

```
Ds-project/
├── src/                    # Implementation files
│   ├── main.cpp           # Main entry point
│   ├── Trie.cpp           # Trie implementation
│   ├── AhoCorasick.cpp    # Aho-Corasick implementation
│   ├── Graph.cpp          # Graph implementation
│   ├── AVLTree.cpp        # AVL Tree implementation
│   ├── PriorityQueue.cpp  # Max-Heap implementation
│   ├── HashTable.cpp      # Hash Table implementation
│   ├── LinkedList.cpp     # Linked List implementation
│   ├── MalwareScanner.cpp # Module 1
│   ├── RansomwareDetector.cpp # Module 2
│   ├── NetworkIDS.cpp     # Module 3
│   └── ThreatIntelligence.cpp # Module 4
│
├── include/               # Header files
│   └── *.h               # Corresponding headers
│
├── data/                  # Sample data
│   ├── malware_signatures.txt
│   ├── blacklisted_ips.txt
│   └── samples/
│
├── docs/                  # Documentation
│   ├── TECHNICAL_DOCUMENTATION.md
│   ├── PROJECT_REPORT.md
│   ├── USER_MANUAL.md
│   ├── ARCHITECTURE.md
│   ├── PERFORMANCE_ANALYSIS.md
│   └── PRESENTATION.md
│
├── tests/                 # Test files
├── Makefile              # Build configuration
└── README.md             # Project overview
```

---

## Adding New Features

### 1. Adding a New Data Structure

**Step 1:** Create header file in `include/`

```cpp
// include/NewDataStructure.h
#ifndef NEW_DATA_STRUCTURE_H
#define NEW_DATA_STRUCTURE_H

class NewDataStructure {
private:
    // Private members
    
public:
    NewDataStructure();
    ~NewDataStructure();
    
    // Public interface
};

#endif
```

**Step 2:** Implement in `src/`

```cpp
// src/NewDataStructure.cpp
#include "../include/NewDataStructure.h"

NewDataStructure::NewDataStructure() {
    // Constructor
}

NewDataStructure::~NewDataStructure() {
    // Destructor - clean up resources
}
```

**Step 3:** Add to Makefile if needed

```makefile
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
```

### 2. Adding a New Security Module

**Example: Adding a SQL Injection Detector**

**Step 1:** Create header

```cpp
// include/SQLInjectionDetector.h
#ifndef SQL_INJECTION_DETECTOR_H
#define SQL_INJECTION_DETECTOR_H

#include "Trie.h"
#include <string>
#include <vector>

class SQLInjectionDetector {
private:
    Trie* patterns;
    
public:
    SQLInjectionDetector();
    ~SQLInjectionDetector();
    
    void loadPatterns();
    bool detectInjection(const std::string& query);
    void displayResults();
};

#endif
```

**Step 2:** Implement detection logic

```cpp
// src/SQLInjectionDetector.cpp
#include "../include/SQLInjectionDetector.h"

SQLInjectionDetector::SQLInjectionDetector() {
    patterns = new Trie();
    loadPatterns();
}

void SQLInjectionDetector::loadPatterns() {
    patterns->insert("' OR '1'='1");
    patterns->insert("'; DROP TABLE");
    // Add more patterns
}

bool SQLInjectionDetector::detectInjection(const std::string& query) {
    // Implementation
    return false;
}
```

**Step 3:** Integrate into main

```cpp
// In main.cpp
#include "include/SQLInjectionDetector.h"

int main() {
    // ... existing code ...
    
    SQLInjectionDetector* sqlDetector = new SQLInjectionDetector();
    // Use the detector
    
    delete sqlDetector;
    return 0;
}
```

### 3. Adding New Detection Patterns

**Malware Signatures:**

Edit `data/malware_signatures.txt`:
```
new_malware_pattern
suspicious_code_123
trojan_variant_x
```

**Blacklisted IPs:**

Edit `data/blacklisted_ips.txt`:
```
192.168.1.150
10.0.0.99
```

---

## Code Style Guidelines

### General Principles
- Use clear, descriptive variable names
- Keep functions focused and concise
- Comment complex algorithms
- Follow existing code patterns

### Naming Conventions

```cpp
// Classes: PascalCase
class MalwareScanner { };

// Functions: camelCase
void processPacket() { }

// Variables: camelCase
int packetCount = 0;

// Constants: UPPER_SNAKE_CASE
const int MAX_SIZE = 1000;

// Private members: prefix with underscore (optional)
class MyClass {
private:
    int _privateVar;
public:
    int publicVar;
};
```

### Code Formatting

```cpp
// Use consistent indentation (4 spaces)
void exampleFunction() {
    if (condition) {
        // Code here
    }
}

// Braces on same line for functions
void myFunction() {
    // Implementation
}

// Space after keywords
if (x > 0) { }
for (int i = 0; i < n; i++) { }
while (condition) { }

// No space for function calls
myFunction(arg1, arg2);
```

### Memory Management

```cpp
// Always pair new with delete
MyClass* obj = new MyClass();
// ... use obj ...
delete obj;

// Use destructors for cleanup
class MyClass {
public:
    ~MyClass() {
        // Clean up resources
    }
};

// Check pointers before use
if (ptr != nullptr) {
    ptr->doSomething();
}
```

### Comments

```cpp
/**
 * Brief description of function
 * 
 * @param param1 Description of parameter
 * @return Description of return value
 */
int myFunction(int param1) {
    // Implementation comment
    return result;
}

// Single-line comments for brief explanations
int x = 5;  // Counter for items
```

---

## Testing

### Writing Tests

Create test files in `tests/` directory:

```cpp
// tests/test_new_feature.cpp
#include <iostream>
#include <cassert>
#include "../include/NewFeature.h"

void testBasicOperation() {
    NewFeature nf;
    assert(nf.operation() == expectedValue);
    std::cout << "✓ Basic operation test passed" << std::endl;
}

void testEdgeCase() {
    NewFeature nf;
    assert(nf.handleEdgeCase() == expectedValue);
    std::cout << "✓ Edge case test passed" << std::endl;
}

int main() {
    testBasicOperation();
    testEdgeCase();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
```

### Running Tests

```bash
# Compile test
g++ -std=c++17 -I./include tests/test_new_feature.cpp src/NewFeature.cpp -o test_new_feature

# Run test
./test_new_feature
```

---

## Documentation

### Code Documentation

Use clear comments for:
- Class purposes
- Function behavior
- Complex algorithms
- Non-obvious decisions

Example:
```cpp
/**
 * Aho-Corasick Automaton for multi-pattern string matching.
 * 
 * This implementation uses a trie with failure links to enable
 * efficient simultaneous matching of multiple patterns in O(n + z)
 * time, where n is the text length and z is the number of matches.
 */
class AhoCorasick {
    // Implementation
};
```

### Updating Documentation

When adding features:

1. **Update README.md** with new capabilities
2. **Update TECHNICAL_DOCUMENTATION.md** with implementation details
3. **Update USER_MANUAL.md** with usage instructions
4. **Add to ARCHITECTURE.md** if changing system design

---

## Pull Request Process

1. **Fork the repository**
2. **Create a feature branch**
   ```bash
   git checkout -b feature/new-feature
   ```
3. **Make your changes**
4. **Test thoroughly**
5. **Update documentation**
6. **Commit with clear messages**
   ```bash
   git commit -m "Add SQL injection detector module"
   ```
7. **Push to your fork**
   ```bash
   git push origin feature/new-feature
   ```
8. **Submit pull request**

---

## Ideas for Contributions

### Data Structures
- Suffix Array for advanced pattern matching
- B-Tree for disk-based storage
- Bloom Filter for quick negative lookups
- Skip List as alternative to AVL Tree

### Security Modules
- SQL Injection Detector
- XSS (Cross-Site Scripting) Detector
- Buffer Overflow Analyzer
- Phishing URL Detector
- Cryptojacking Monitor

### Features
- Real-time file system monitoring
- Network packet capture integration
- Machine learning based detection
- Visualization dashboard
- REST API interface
- Database persistence
- Multi-threading support
- Configuration file support

### Performance
- Memory pooling
- SIMD optimizations
- Cache-friendly data layouts
- Parallel processing
- Lazy evaluation

### Documentation
- Video tutorials
- Interactive examples
- Performance comparisons
- Case studies
- Blog posts

---

## Getting Help

If you need help:
1. Check existing documentation in `docs/`
2. Review the code comments
3. Look at similar implementations
4. Open an issue with your question

---

## Code of Conduct

- Be respectful and professional
- Write clean, maintainable code
- Test your changes thoroughly
- Document new features
- Follow existing patterns
- Ask questions when unsure

---

## License

This project is for educational purposes. Contributions should maintain this focus.

---

## Recognition

Contributors will be acknowledged in:
- README.md
- Project documentation
- Release notes

---

Thank you for contributing to this educational project!

**Questions?** Open an issue or check the documentation.
