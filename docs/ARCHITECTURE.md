# System Architecture & UML Diagrams
## Integrated Cyber Threat Detection Suite

---

## 1. System Architecture Diagram

```
┌─────────────────────────────────────────────────────────────────┐
│                    USER INTERFACE LAYER                         │
│                   (Console Application)                         │
└────────────────────────┬────────────────────────────────────────┘
                         │
┌────────────────────────▼────────────────────────────────────────┐
│               MAIN CONTROLLER & INTEGRATION                     │
│                      (main.cpp)                                 │
│  • Orchestrates module execution                                │
│  • Coordinates data flow                                        │
│  • Manages initialization and cleanup                           │
└─────┬──────────┬──────────┬──────────┬──────────────────────────┘
      │          │           │          │
┌─────▼─────┐ ┌─▼────────┐ ┌▼────────┐ ┌▼──────────────────────┐
│  Module 1 │ │ Module 2 │ │Module 3 │ │      Module 4         │
│  Malware  │ │Ransomware│ │ Network │ │ Threat Intelligence   │
│  Scanner  │ │ Detector │ │   IDS   │ │    & Reporting        │
└─────┬─────┘ └─┬────────┘ └┬────────┘ └┬──────────────────────┘
      │         │            │           │
┌─────▼─────────▼────────────▼───────────▼─────────────────────┐
│              DATA STRUCTURE LAYER                             │
│                                                               │
│  ┌──────┐  ┌──────┐  ┌──────┐  ┌────────┐  ┌──────────┐    │
│  │ Trie │  │Graph │  │ AVL  │  │  Hash  │  │  Linked  │    │
│  │      │  │      │  │ Tree │  │  Table │  │   List   │    │
│  └──────┘  └──────┘  └──────┘  └────────┘  └──────────┘    │
│  ┌──────────────┐  ┌────────────────┐                       │
│  │ Aho-Corasick │  │  Priority Queue│                       │
│  │   Automaton  │  │   (Max-Heap)   │                       │
│  └──────────────┘  └────────────────┘                       │
└───────────────────────────────────────────────────────────────┘
```

---

## 2. Class Diagram

### Overview

```
┌─────────────────────────────────────────────────────────────┐
│                    Data Structures                          │
├─────────────────────────────────────────────────────────────┤
│  Trie              Graph          AVLTree                   │
│  AhoCorasick       HashTable      PriorityQueue             │
│  LinkedList                                                 │
└─────────────────────────────────────────────────────────────┘
                           ▲
                           │ uses
┌─────────────────────────┴────────────────────────────────────┐
│                    Security Modules                          │
├──────────────────────────────────────────────────────────────┤
│  MalwareScanner        RansomwareDetector                    │
│  NetworkIDS            ThreatIntelligence                    │
└──────────────────────────────────────────────────────────────┘
```

### Detailed Class Diagrams

#### Module 1: Malware Scanner Classes

```
┌─────────────────────────────┐
│      MalwareScanner         │
├─────────────────────────────┤
│ - scanner: AhoCorasick*     │
│ - signatureDB: Trie*        │
│ - signatures: vector<str>   │
├─────────────────────────────┤
│ + MalwareScanner()          │
│ + ~MalwareScanner()         │
│ + loadSignatures(file)      │
│ + addSignature(sig)         │
│ + scanFile(file)            │
│ + scanText(text)            │
│ + displayResults(matches)   │
└─────────────────────────────┘
         │ uses
         ├──────────────────────────┐
         │                          │
┌────────▼──────────┐     ┌─────────▼────────┐
│      Trie         │     │   AhoCorasick    │
├───────────────────┤     ├──────────────────┤
│ - root: TrieNode* │     │ - root: ACNode*  │
├───────────────────┤     ├──────────────────┤
│ + insert(word)    │     │ + addPattern()   │
│ + search(word)    │     │ + build()        │
│ + getRoot()       │     │ + search(text)   │
└───────────────────┘     └──────────────────┘
```

#### Module 2: Ransomware Detector Classes

```
┌───────────────────────────────┐
│    RansomwareDetector         │
├───────────────────────────────┤
│ - fileSystem: Graph*          │
│ - pattern: BehaviorPattern    │
├───────────────────────────────┤
│ + buildFileSystem()           │
│ + simulateNormalAccess()      │
│ + simulateRansomwareAccess()  │
│ + detectRansomwareBehavior()  │
│ + displayAnalysis(pattern)    │
└───────────────────────────────┘
         │ uses
         ▼
┌───────────────────────────────┐
│         Graph                 │
├───────────────────────────────┤
│ - nodes: map<str, GraphNode*> │
│ - adjList: map<str, vector>   │
├───────────────────────────────┤
│ + addNode(name, type)         │
│ + addEdge(from, to)           │
│ + BFS(start)                  │
│ + DFS(start)                  │
│ + getNode(name)               │
└───────────────────────────────┘

┌───────────────────────────────┐
│      BehaviorPattern          │
├───────────────────────────────┤
│ + rapidEncryption: int        │
│ + massFileAccess: int         │
│ + suspiciousTraversal: int    │
│ + isRansomware: bool          │
└───────────────────────────────┘
```

#### Module 3: Network IDS Classes

```
┌────────────────────────────────┐
│       NetworkIDS               │
├────────────────────────────────┤
│ - packetTree: AVLTree*         │
│ - threatQueue: MaxHeap*        │
│ - ipTracker: HashTable*        │
│ - blacklistedIPs: vector<str>  │
├────────────────────────────────┤
│ + loadBlacklist(file)          │
│ + addBlacklistIP(ip)           │
│ + processPacket(packet)        │
│ + analyzeTraffic()             │
│ + displayThreats()             │
└────────────────────────────────┘
         │ uses
    ┌────┼────┬──────────┐
    ▼    ▼    ▼          ▼
┌─────┐ ┌───┐ ┌────┐ ┌─────────┐
│ AVL │ │Max│ │Hash│ │ Packet  │
│Tree │ │Heap│ │Tbl │ │ Threat  │
└─────┘ └───┘ └────┘ └─────────┘

┌───────────────────────────────┐
│         Packet                │
├───────────────────────────────┤
│ + sourceIP: string            │
│ + destIP: string              │
│ + port: int                   │
│ + protocol: string            │
│ + timestamp: long             │
│ + size: int                   │
└───────────────────────────────┘

┌───────────────────────────────┐
│          Threat               │
├───────────────────────────────┤
│ + type: string                │
│ + source: string              │
│ + severity: int               │
│ + description: string         │
│ + timestamp: long             │
└───────────────────────────────┘
```

#### Module 4: Threat Intelligence Classes

```
┌────────────────────────────────────┐
│      ThreatIntelligence            │
├────────────────────────────────────┤
│ - threatDB: HashTable*             │
│ - eventLog: LinkedList*            │
│ - malwareSignatures: vector<str>   │
│ - suspiciousIPs: vector<str>       │
│ - ransomwareIndicators: vector<str>│
├────────────────────────────────────┤
│ + addThreat(type, value)           │
│ + logEvent(ts, type, desc, sev)    │
│ + isThreatKnown(indicator)         │
│ + generateReport(file)             │
│ + displaySummary()                 │
│ + addMalwareResults(matches)       │
│ + addRansomwareAlert(detected)     │
│ + addNetworkThreats(threats)       │
└────────────────────────────────────┘
         │ uses
    ┌────┴──────┐
    ▼           ▼
┌─────────┐ ┌────────────┐
│  Hash   │ │  Linked    │
│  Table  │ │   List     │
└─────────┘ └────────────┘

┌───────────────────────────────┐
│        EventLog               │
├───────────────────────────────┤
│ + timestamp: string           │
│ + eventType: string           │
│ + description: string         │
│ + severity: string            │
└───────────────────────────────┘
```

---

## 3. Sequence Diagrams

### 3.1 Main Execution Flow

```
User    Main    MalwareScanner  RansomwareDetector  NetworkIDS  ThreatIntel
 │       │            │                 │               │            │
 │──run──▶│           │                 │               │            │
 │       │──create───▶│                 │               │            │
 │       │            │──load sigs──────│               │            │
 │       │            │◀────────────────│               │            │
 │       │            │                 │               │            │
 │       │──scan─────▶│                 │               │            │
 │       │            │──matches────────▶               │            │
 │       │◀───────────│                 │               │            │
 │       │                              │               │            │
 │       │──create────────────────────▶ │               │            │
 │       │──build FS──────────────────▶ │               │            │
 │       │──simulate──────────────────▶ │               │            │
 │       │◀──pattern──────────────────  │               │            │
 │       │                              │               │            │
 │       │──create──────────────────────────────────────▶            │
 │       │──process packets─────────────────────────────▶            │
 │       │◀──threats────────────────────────────────────             │
 │       │                                              │            │
 │       │──create──────────────────────────────────────────────────▶│
 │       │──add malware results─────────────────────────────────────▶│
 │       │──add ransomware alert────────────────────────────────────▶│
 │       │──add network threats─────────────────────────────────────▶│
 │       │──generate report─────────────────────────────────────────▶│
 │       │◀──report saved───────────────────────────────────────────│
 │◀──done│                                                            │
```

### 3.2 Malware Scanning Sequence

```
MalwareScanner  AhoCorasick  Trie    File
     │               │        │       │
     │──addSignature─▶        │       │
     │               │──insert─▶      │
     │               │◀───────│       │
     │               │        │       │
     │──scanFile─────▶        │       │
     │               │──read──────────▶
     │               │◀───content─────│
     │               │        │       │
     │──search───────▶        │       │
     │               │──traverse──────│
     │               │──match─────────│
     │◀──matches─────│        │       │
     │               │        │       │
```

### 3.3 Ransomware Detection Sequence

```
RansomwareDetector  Graph  FileSystem
       │              │         │
       │──buildFS─────▶         │
       │              │──addNode─▶
       │              │──addEdge─▶
       │              │         │
       │──simulate────▶         │
       │              │──BFS────▶
       │              │◀────────│
       │              │         │
       │──analyze─────▶         │
       │              │         │
       │◀──pattern────│         │
       │              │         │
```

### 3.4 Network Intrusion Detection Sequence

```
NetworkIDS  AVLTree  MaxHeap  HashTable
    │          │        │         │
    │──processPacket───▶│         │
    │          │──insert │         │
    │          │        │         │
    │──checkIP──────────────────▶ │
    │          │        │◀────────│
    │          │        │         │
    │──addThreat────────▶         │
    │          │        │         │
    │──displayThreats───▶         │
    │          │◀──extractMax──   │
    │◀─────────│        │         │
```

---

## 4. Data Flow Diagram

```
┌─────────────┐
│   Input     │
│   Files     │
└──────┬──────┘
       │
       ▼
┌─────────────────┐     ┌──────────────────┐
│ Malware Scanner │────▶│  Pattern Matches │
└─────────────────┘     └────────┬─────────┘
                                 │
       ┌─────────────────────────┤
       │                         │
       ▼                         ▼
┌─────────────────┐     ┌──────────────────┐
│ File System     │────▶│ Behavior Pattern │
│ Simulation      │     └────────┬─────────┘
└─────────────────┘              │
                                 │
       ┌─────────────────────────┤
       │                         │
       ▼                         ▼
┌─────────────────┐     ┌──────────────────┐
│ Network Packets │────▶│  Threat Events   │
└─────────────────┘     └────────┬─────────┘
                                 │
                                 │
                                 ▼
                        ┌──────────────────┐
                        │     Threat       │
                        │  Intelligence    │
                        │    Database      │
                        └────────┬─────────┘
                                 │
                                 ▼
                        ┌──────────────────┐
                        │ Security Report  │
                        └──────────────────┘
```

---

## 5. Component Interaction Diagram

```
┌──────────────────────────────────────────────────────────┐
│                  Integration Layer                       │
│                                                          │
│  ┌────────────┐  ┌────────────┐  ┌────────────┐       │
│  │  Module 1  │  │  Module 2  │  │  Module 3  │       │
│  │   Sends    │  │   Sends    │  │   Sends    │       │
│  │  Matches   │  │  Patterns  │  │  Threats   │       │
│  └─────┬──────┘  └─────┬──────┘  └─────┬──────┘       │
│        │               │               │               │
│        └───────────────┼───────────────┘               │
│                        ▼                               │
│               ┌─────────────────┐                      │
│               │    Module 4     │                      │
│               │  Aggregates &   │                      │
│               │    Reports      │                      │
│               └─────────────────┘                      │
└──────────────────────────────────────────────────────────┘
```

---

## 6. Deployment Diagram

```
┌─────────────────────────────────────────────┐
│           Physical Machine                  │
│                                             │
│  ┌───────────────────────────────────────┐ │
│  │      Operating System (Linux/Mac)     │ │
│  │                                       │ │
│  │  ┌─────────────────────────────────┐ │ │
│  │  │    Runtime Environment          │ │ │
│  │  │    (C++ Standard Library)       │ │ │
│  │  │                                 │ │ │
│  │  │  ┌───────────────────────────┐ │ │ │
│  │  │  │  Threat Detection Suite   │ │ │ │
│  │  │  │  (Executable Binary)      │ │ │ │
│  │  │  └───────────────────────────┘ │ │ │
│  │  └─────────────────────────────────┘ │ │
│  └───────────────────────────────────────┘ │
│                                             │
│  ┌───────────────────────────────────────┐ │
│  │      File System                      │ │
│  │                                       │ │
│  │  • data/malware_signatures.txt        │ │
│  │  • data/blacklisted_ips.txt           │ │
│  │  • threat_report.txt                  │ │
│  └───────────────────────────────────────┘ │
└─────────────────────────────────────────────┘
```

---

## 7. State Diagram: Threat Detection Lifecycle

```
        ┌────────┐
        │ Start  │
        └────┬───┘
             │
             ▼
      ┌──────────────┐
      │ Initializing │
      └──────┬───────┘
             │
             ▼
      ┌──────────────┐
      │   Loading    │
      │ Signatures   │
      └──────┬───────┘
             │
             ▼
      ┌──────────────┐
      │   Scanning   │
      └──────┬───────┘
             │
        ┌────┴────┐
        │         │
        ▼         ▼
   ┌────────┐ ┌────────┐
   │Threats │ │  Clean │
   │ Found  │ │        │
   └────┬───┘ └───┬────┘
        │         │
        └────┬────┘
             │
             ▼
      ┌──────────────┐
      │  Analyzing   │
      └──────┬───────┘
             │
             ▼
      ┌──────────────┐
      │  Reporting   │
      └──────┬───────┘
             │
             ▼
        ┌────────┐
        │  End   │
        └────────┘
```

---

## 8. Activity Diagram: Complete Workflow

```
START
  │
  ▼
[Initialize System]
  │
  ▼
[Load Malware Signatures]
  │
  ▼
[Build Aho-Corasick Automaton]
  │
  ▼
[Scan Files for Malware]
  │
  ├──[Match Found?]──Yes──▶[Log Match]
  │                          │
  └──[No]─────────────────────┘
  │
  ▼
[Build File System Graph]
  │
  ▼
[Simulate File Access]
  │
  ▼
[Analyze Traversal Pattern]
  │
  ├──[Ransomware Detected?]──Yes──▶[Log Alert]
  │                                  │
  └──[No]────────────────────────────┘
  │
  ▼
[Process Network Packets]
  │
  ▼
[Store in AVL Tree]
  │
  ▼
[Check for Intrusions]
  │
  ├──[Threats Found?]──Yes──▶[Add to Priority Queue]
  │                           │
  └──[No]──────────────────────┘
  │
  ▼
[Aggregate All Threats]
  │
  ▼
[Generate Report]
  │
  ▼
[Save to File]
  │
  ▼
END
```

---

## 9. Package Diagram

```
┌──────────────────────────────────────────────────┐
│              Ds-project                          │
├──────────────────────────────────────────────────┤
│                                                  │
│  ┌────────────────┐    ┌─────────────────────┐  │
│  │  DataStructures│    │   SecurityModules   │  │
│  ├────────────────┤    ├─────────────────────┤  │
│  │ • Trie         │◀───│ • MalwareScanner    │  │
│  │ • AhoCorasick  │    │ • RansomwareDetector│  │
│  │ • Graph        │    │ • NetworkIDS        │  │
│  │ • AVLTree      │    │ • ThreatIntelligence│  │
│  │ • MaxHeap      │    │                     │  │
│  │ • HashTable    │    │                     │  │
│  │ • LinkedList   │    │                     │  │
│  └────────────────┘    └─────────────────────┘  │
│         ▲                        ▲               │
│         │                        │               │
│         └────────┬───────────────┘               │
│                  │                               │
│           ┌──────▼──────┐                        │
│           │    Main     │                        │
│           │ Controller  │                        │
│           └─────────────┘                        │
│                                                  │
└──────────────────────────────────────────────────┘
```

---

## 10. Use Case Diagram

```
                    System Boundary
    ┌───────────────────────────────────────────┐
    │  Integrated Cyber Threat Detection Suite │
    │                                           │
    │  ┌────────────────────────────────┐      │
    │  │  Scan for Malware              │      │
Student ──▶  │                            │      │
Educator──▶  ├────────────────────────────┤      │
    │  │  Detect Ransomware Behavior    │      │
    │  │                                │      │
    │  ├────────────────────────────────┤      │
Security ──▶ │  Analyze Network Traffic   │      │
Analyst │  │                                │      │
    │  ├────────────────────────────────┤      │
    │  │  Generate Threat Report        │      │
    │  │                                │      │
    │  └────────────────────────────────┘      │
    │                                           │
    └───────────────────────────────────────────┘
```

---

## Conclusion

This documentation provides comprehensive visual representations of the system architecture, class structures, and workflows. These diagrams serve as:

- **Learning aids** for understanding system design
- **Reference material** for implementation details
- **Communication tools** for explaining the architecture
- **Documentation** for future maintenance and extension

All diagrams use standard UML notation and best practices for software architecture documentation.

---

**END OF ARCHITECTURE DOCUMENTATION**
