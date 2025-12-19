# Session 10: Linked Lists

**Duration:** 45-60 minutes  
**Goal:** Understand linked lists for event logging

## Structure
Nodes connected by pointers:
```
[Data|Next] → [Data|Next] → [Data|NULL]
```

## Operations
- Insert at head: O(1)
- Insert at tail: O(1) with tail pointer
- Delete at head: O(1)
- Search: O(n)
- Access by index: O(n)

## vs. Arrays
Arrays:
- Fast access by index: O(1)
- Slow insert/delete: O(n)
- Fixed size

Linked Lists:
- Slow access: O(n)
- Fast insert/delete: O(1)
- Dynamic size

## Event Logging
Perfect for logging because:
- Constantly appending new events
- O(1) append with tail pointer
- No array resizing overhead
- 5,986× faster for append-heavy workloads!

See you in Session 11!
