# Session 7: AVL Tree (Self-Balancing BST)

**Duration:** 75-90 minutes  
**Goal:** Understand self-balancing trees for packet storage

## Binary Search Trees
- Left < Parent < Right
- O(log n) operations IF balanced
- Can degrade to O(n) if unbalanced

## AVL Trees
Named after inventors: Adelson-Velsky and Landis
- Self-balancing BST
- Height difference ≤ 1 between subtrees
- Guarantees O(log n) always!

## Rotations
Four types:
1. Left Rotation
2. Right Rotation
3. Left-Right Rotation
4. Right-Left Rotation

## Network IDS Usage
- Store packets sorted by timestamp
- Fast insertion: O(log n)
- Fast search: O(log n)
- Always balanced - no degradation!

**289× faster than unsorted array for large datasets!**

See you in Session 8!
