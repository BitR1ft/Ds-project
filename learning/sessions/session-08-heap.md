# Session 8: Priority Queue and Max-Heap

**Duration:** 60-75 minutes  
**Goal:** Learn heaps for threat prioritization

## Priority Queues
Abstract data type where each element has priority:
- Insert with priority
- Extract highest priority

## Max-Heap Implementation
Complete binary tree where parent ≥ children
```
       100
      /   \
    80    60
   / \   /
  40 30 20
```

## Operations
- Insert: O(log n) - bubble up
- Extract Max: O(log n) - bubble down
- Peek Max: O(1) - just root!

## Network Threat Prioritization
- Each packet has threat score
- Always process highest threat first
- O(1) to get most critical threat
- O(log n) to add new threats

Perfect for real-time security monitoring!

See you in Session 9!
