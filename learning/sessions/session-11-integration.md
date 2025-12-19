# Session 11: System Integration & Architecture

**Duration:** 60-75 minutes  
**Goal:** Understand how all modules work together

## Architecture
```
Main Controller
    ↓
┌───┴───┬────────┬─────────┐
│       │        │         │
Malware Ransomware Network Threat
Scanner Detector   IDS   Intelligence
```

## Data Flow
1. Malware Scanner: Trie + Aho-Corasick → Detections
2. Ransomware Detector: Graph + BFS/DFS → Behavior Analysis
3. Network IDS: AVL + Heap → Packet Analysis
4. Threat Intelligence: Hash + LinkedList → Reporting

All results flow to central reporting engine!

## Integration Principles
- Modular design
- Clear interfaces
- Independent modules
- Centralized reporting
- Error handling throughout

See you in Session 12!
