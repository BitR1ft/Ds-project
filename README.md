# Integrated Cyber Threat Detection Suite

**Course:** CS-214 – Data Structures  
**Program:** BS Cyber Security

## Overview

A comprehensive security framework combining multiple threat detection mechanisms using advanced Data Structures. This project demonstrates the practical application of data structures in cybersecurity.

## Features

### 1. Malware Signature Scanner
- **Data Structures:** Trie, Aho-Corasick Automaton
- **Functionality:** Multi-pattern malware signature detection in files

### 2. Ransomware Behavior Detector
- **Data Structures:** Graphs, DFS/BFS
- **Functionality:** File system traversal analysis and ransomware pattern detection

### 3. Network Intrusion Detection System (IDS)
- **Data Structures:** AVL Tree, Priority Queue (Max-Heap)
- **Functionality:** Packet analysis and intrusion detection

### 4. Threat Intelligence & Reporting Engine
- **Data Structures:** Hash Tables, Linked Lists
- **Functionality:** Centralized threat database and comprehensive reporting

## System Architecture

The system integrates four independent modules into a cohesive security suite:

```
┌─────────────────────────────────────────────┐
│    Main Controller & Integration Layer     │
└──────────────┬──────────────────────────────┘
               │
    ┌──────────┴──────────┐
    │                     │
┌───▼────┐  ┌────▼─────┐  ┌────▼─────┐  ┌────▼─────┐
│Malware │  │Ransomware│  │ Network  │  │ Threat   │
│Scanner │  │ Detector │  │   IDS    │  │ Intel.   │
└────────┘  └──────────┘  └──────────┘  └──────────┘
```

## Building the Project

### Prerequisites
- C++ compiler (g++ 7.0 or later)
- Make (optional)

### Compilation

Using Makefile:
```bash
make
```

Manual compilation:
```bash
g++ -std=c++17 -I./include src/*.cpp -o threat_detection_suite
```

## Running the Suite

```bash
./threat_detection_suite
```

The program will:
1. Load malware signatures
2. Scan test files
3. Analyze file system behavior
4. Process network packets
5. Generate a comprehensive threat report

## Project Structure

```
Ds-project/
├── src/               # Source files (.cpp)
├── include/           # Header files (.h)
├── tests/             # Test cases
├── data/              # Sample data files
├── docs/              # Documentation and reports
├── Makefile           # Build configuration
└── README.md          # This file
```

## Data Structures Implemented

1. **Trie** - Efficient prefix-based signature storage
2. **Aho-Corasick Automaton** - Multi-pattern matching
3. **Graph** - File system representation
4. **DFS/BFS** - Graph traversal algorithms
5. **AVL Tree** - Balanced packet storage
6. **Max-Heap** - Priority-based threat ranking
7. **Hash Table** - Fast threat lookups
8. **Linked List** - Event log management

## Testing

Run test cases:
```bash
./threat_detection_suite --test
```

## Documentation

Complete project documentation is available in the `docs/` directory:
- Technical Documentation
- UML Diagrams
- Project Report
- User Manual

## License

Educational project for CS-214 Data Structures course.

## Authors

Group Members:
1. [Member 1 - Malware Scanner Module]
2. [Member 2 - Ransomware Detector Module]
3. [Member 3 - Network IDS Module]
4. [Member 4 - Threat Intelligence Module]
