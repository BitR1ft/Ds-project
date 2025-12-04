# User Manual
## Integrated Cyber Threat Detection Suite

### Version 1.0

---

## Table of Contents
1. [Introduction](#introduction)
2. [System Requirements](#system-requirements)
3. [Installation](#installation)
4. [Getting Started](#getting-started)
5. [Using the System](#using-the-system)
6. [Understanding the Output](#understanding-the-output)
7. [Advanced Usage](#advanced-usage)
8. [Troubleshooting](#troubleshooting)
9. [FAQ](#faq)

---

## 1. Introduction

Welcome to the **Integrated Cyber Threat Detection Suite** - a comprehensive security framework designed to detect and analyze various types of cyber threats.

### What is this system?

The Threat Detection Suite is an educational and practical tool that demonstrates how advanced data structures can be applied to real-world cybersecurity problems. It analyzes files, system behavior, and network traffic to identify potential security threats.

### Who is this for?

- **Students** learning about data structures and cybersecurity
- **Educators** teaching algorithmic applications
- **Security enthusiasts** interested in threat detection mechanisms
- **Developers** studying system architecture and integration

---

## 2. System Requirements

### Minimum Requirements

**Operating System:**
- Linux (Ubuntu 18.04+, Debian 9+, CentOS 7+)
- macOS (10.14+)
- Windows (with WSL2 or MinGW)

**Software:**
- C++ Compiler: g++ 7.0 or later
- Make utility
- Standard C++ libraries

**Hardware:**
- CPU: Any modern processor
- RAM: 512 MB minimum
- Storage: 50 MB free space

### Recommended

- CPU: Multi-core processor
- RAM: 2 GB or more
- Storage: 100 MB free space

---

## 3. Installation

### Step 1: Clone the Repository

```bash
git clone https://github.com/BitR1ft/Ds-project.git
cd Ds-project
```

### Step 2: Verify Prerequisites

Check if you have the required compiler:

```bash
g++ --version
```

You should see output showing g++ version 7.0 or higher.

### Step 3: Build the Project

```bash
make
```

Expected output:
```
mkdir -p obj
g++ -std=c++17 -Wall -Wextra -I./include -c src/...
...
Build successful! Run with: ./threat_detection_suite
```

### Step 4: Verify Installation

```bash
./threat_detection_suite
```

If you see the welcome banner, installation was successful!

---

## 4. Getting Started

### Quick Start Guide

1. **Run the program:**
   ```bash
   ./threat_detection_suite
   ```

2. **View the output:**
   The system will automatically:
   - Load malware signatures
   - Scan test files
   - Analyze file system behavior
   - Process network packets
   - Generate a threat report

3. **Check the report:**
   ```bash
   cat threat_report.txt
   ```

That's it! The system runs all modules automatically and generates a comprehensive report.

---

## 5. Using the System

### Running a Complete Analysis

The simplest way to use the system:

```bash
./threat_detection_suite
```

This executes all four modules in sequence:

1. **Malware Signature Scanner**
2. **Ransomware Behavior Detector**
3. **Network Intrusion Detection System**
4. **Threat Intelligence & Reporting**

### Understanding the Workflow

```
Start
  ↓
Load Malware Signatures
  ↓
Scan Files for Malware
  ↓
Analyze File System Behavior
  ↓
Process Network Packets
  ↓
Generate Threat Report
  ↓
End
```

### Customizing Detection

#### Adding Malware Signatures

Edit `data/malware_signatures.txt`:

```bash
nano data/malware_signatures.txt
```

Add one signature per line:
```
malicious_code
trojan_backdoor
ransomware_pattern
```

#### Adding Blacklisted IPs

Edit `data/blacklisted_ips.txt`:

```bash
nano data/blacklisted_ips.txt
```

Add one IP per line:
```
192.168.1.100
10.0.0.50
203.0.113.5
```

#### Creating Test Files

Create your own test file:

```bash
echo "This file contains a trojan and malicious code" > data/samples/my_test.txt
```

---

## 6. Understanding the Output

### Console Output Structure

The program displays output in four sections:

#### Section 1: Malware Scanner
```
=== Malware Scan Results ===
⚠ Found 2 malware signature(s):
  - Position 21: "trojan"
  - Position 32: "malicious_payload"
```

**Interpretation:**
- Number of matches found
- Position in file where signature was detected
- Name of the signature

#### Section 2: Ransomware Detector
```
=== Ransomware Behavior Analysis ===
Rapid Encryption Count: 7
Mass File Access Count: 51
Traversal Depth: 12
⚠ ALERT: Ransomware behavior detected!
```

**Interpretation:**
- **Rapid Encryption Count:** Number of files encrypted quickly
- **Mass File Access Count:** Total file access operations
- **Traversal Depth:** Number of directories/files examined
- **Alert Status:** Whether ransomware behavior was detected

#### Section 3: Network IDS
```
=== Network Intrusion Detection Results ===
⚠ Detected 58 network threat(s):
  [Severity: 10] DDoS Attack from 198.51.100.10
  [Severity: 9] Blacklisted IP from 192.168.1.100
  [Severity: 7] Port Scan from 203.0.113.5
```

**Interpretation:**
- **Severity Levels:**
  - 10: Critical (DDoS attacks)
  - 9: High (Blacklisted IPs)
  - 7: Medium (Port scans)
- **Threat Type:** Classification of the attack
- **Source:** IP address of attacker

#### Section 4: Threat Intelligence Summary
```
========================================
    THREAT INTELLIGENCE SUMMARY        
========================================
Malware Signatures: 2
Suspicious IPs: 3
Ransomware Indicators: 1
Total Events: 6
========================================
```

**Interpretation:**
- Summary of all detected threats across all modules
- Total event count

### Threat Report File

The `threat_report.txt` file contains:

1. **Header:** Report metadata and generation time
2. **Threat Summary:** Quick overview of all threats
3. **Malware Signatures:** List of detected malware
4. **Suspicious IPs:** Network-based threats
5. **Event Log:** Chronological list of all events

Example:
```
========================================
  INTEGRATED CYBER THREAT DETECTION    
        SECURITY REPORT                
========================================
Generated: Thu Dec  4 08:56:34 2025

--- THREAT SUMMARY ---
Malware Signatures Detected: 2
Suspicious IPs Identified: 3
Ransomware Indicators: 1
Total Events Logged: 6

--- DETAILED EVENT LOG ---
[timestamp] [severity] Event description
...
```

---

## 7. Advanced Usage

### Rebuilding the Project

After making code changes:

```bash
make clean    # Remove old build files
make         # Rebuild from scratch
```

### Running with Custom Data

You can modify the main program to scan your own files:

1. Edit `src/main.cpp`
2. Modify the test data or file paths
3. Rebuild: `make clean && make`
4. Run: `./threat_detection_suite`

### Extending the System

#### Adding New Malware Signatures Programmatically

Edit the main.cpp to add more signatures:

```cpp
malwareScanner->addSignature("new_malware_pattern");
malwareScanner->addSignature("suspicious_code");
```

#### Simulating Different Network Traffic

Modify the packet generation in main.cpp:

```cpp
// Add custom packets
Packet* p = new Packet("source_ip", "dest_ip", port, "protocol", timestamp, size);
networkIDS->processPacket(p);
```

---

## 8. Troubleshooting

### Common Issues

#### Issue: "Command 'g++' not found"

**Solution:** Install g++ compiler

**Ubuntu/Debian:**
```bash
sudo apt-get update
sudo apt-get install g++ build-essential
```

**macOS:**
```bash
xcode-select --install
```

#### Issue: "make: command not found"

**Solution:** Install make utility

**Ubuntu/Debian:**
```bash
sudo apt-get install make
```

**macOS:**
Make is included with Xcode Command Line Tools

#### Issue: "Permission denied" when running

**Solution:** Make the executable file executable

```bash
chmod +x threat_detection_suite
./threat_detection_suite
```

#### Issue: Compilation warnings

**Solution:** Warnings about signed/unsigned comparison are normal and don't affect functionality. The program will still run correctly.

#### Issue: "Segmentation fault"

**Possible causes:**
1. Corrupted data files
2. Invalid file paths
3. Memory issues

**Solution:**
```bash
make clean
make
./threat_detection_suite
```

If problem persists, check data file formats.

### Getting Help

If you encounter issues:

1. Check the error message carefully
2. Verify all data files are present in `data/` directory
3. Ensure you're running from the project root directory
4. Try rebuilding: `make clean && make`
5. Check system requirements

---

## 9. FAQ

### General Questions

**Q: What does this program actually do?**

A: It's an educational security tool that demonstrates how data structures can be used to detect cyber threats. It scans for malware, analyzes file system behavior, and monitors network traffic patterns.

**Q: Can I use this in a production environment?**

A: This is primarily an educational tool. While the concepts are sound, it would need additional hardening and features for production use.

**Q: How accurate is the threat detection?**

A: The detection is based on predefined signatures and behavior patterns. It will accurately detect threats it's programmed to recognize, but won't detect unknown threats (zero-days).

### Technical Questions

**Q: Which data structures are used?**

A: The system uses:
- Trie
- Aho-Corasick Automaton
- Graph (Adjacency List)
- AVL Tree
- Max-Heap (Priority Queue)
- Hash Table
- Linked List

**Q: What's the time complexity of malware scanning?**

A: O(n + z) where n is the text length and z is the number of matches, thanks to the Aho-Corasick algorithm.

**Q: How is ransomware detected?**

A: By analyzing file system traversal patterns using graph algorithms (BFS/DFS) and looking for rapid, systematic file encryption behavior.

**Q: Can I add my own detection rules?**

A: Yes! You can:
1. Add malware signatures to `data/malware_signatures.txt`
2. Add blacklisted IPs to `data/blacklisted_ips.txt`
3. Modify threshold values in the source code

### Usage Questions

**Q: Do I need to run as root/administrator?**

A: No, the program runs with normal user privileges.

**Q: How long does a scan take?**

A: With the default test data, the entire scan completes in under 1 second.

**Q: Where is the output saved?**

A: The detailed report is saved to `threat_report.txt` in the project directory.

**Q: Can I scan my actual files?**

A: Yes, you can modify the code to scan any files you have read access to.

---

## 10. Tips and Best Practices

### For Students

1. **Read the code:** Understanding the implementation is key to learning
2. **Experiment:** Modify parameters and observe the behavior
3. **Add features:** Try implementing your own detection mechanisms
4. **Document changes:** Keep notes on what you modify

### For Educators

1. **Demonstrate concepts:** Use this to show real-world data structure applications
2. **Assignment ideas:**
   - Add new detection mechanisms
   - Implement additional data structures
   - Optimize specific algorithms
   - Add visualization features

### For Security Enthusiasts

1. **Study the patterns:** Learn how different attacks manifest
2. **Test with real data:** Collect and analyze your own samples
3. **Compare with production tools:** See how this compares to commercial systems
4. **Extend functionality:** Add more sophisticated detection methods

---

## 11. Additional Resources

### Documentation Files

- `docs/TECHNICAL_DOCUMENTATION.md` - Detailed technical documentation
- `docs/PROJECT_REPORT.md` - Comprehensive project report
- `README.md` - Quick start guide

### Data Files

- `data/malware_signatures.txt` - Malware pattern database
- `data/blacklisted_ips.txt` - Known malicious IPs
- `data/samples/` - Test data files

### Source Code

- `src/` - Implementation files
- `include/` - Header files
- `Makefile` - Build configuration

---

## 12. Glossary

**AVL Tree:** Self-balancing binary search tree  
**BFS:** Breadth-First Search algorithm  
**DDoS:** Distributed Denial of Service attack  
**DFS:** Depth-First Search algorithm  
**Hash Table:** Data structure for fast key-value lookups  
**IDS:** Intrusion Detection System  
**Malware:** Malicious software  
**Max-Heap:** Binary heap where parent > children  
**Ransomware:** Malware that encrypts files for ransom  
**Trie:** Prefix tree data structure  

---

## Support

For issues, questions, or contributions:
- Check the documentation in `docs/`
- Review the code comments
- Experiment with the test cases

---

**Thank you for using the Integrated Cyber Threat Detection Suite!**

**Version:** 1.0  
**Last Updated:** December 2024  
**License:** Educational Use

---

**END OF USER MANUAL**
