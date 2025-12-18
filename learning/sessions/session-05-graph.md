# Session 5: Graph Data Structure

**Duration:** 60-75 minutes  
**Prerequisites:** Sessions 1-4 completed  
**Goal:** Master graph structures for representing relationships and networks

---

## What We'll Learn Today

By the end of this session, you will:
- ✅ Understand what graphs are and their components
- ✅ Learn different graph representations
- ✅ Build a file system graph
- ✅ Understand directed vs. undirected graphs
- ✅ See how graphs model real-world problems
- ✅ Prepare for ransomware behavior detection

---

## Part 1: Understanding Graphs (15 minutes)

### What is a Graph?

**Graph** = Collection of nodes (vertices) connected by edges

**Components:**
- **Vertices (V):** The nodes/points
- **Edges (E):** The connections between nodes

```
Simple Graph:
    A --- B
    |     |
    C --- D

Vertices: {A, B, C, D}
Edges: {(A,B), (A,C), (B,D), (C,D)}
```

### Real-World Examples

**Social Networks:**
```
   Alice --- Bob
     |         |
   Carol --- David

Vertices = People
Edges = Friendships
```

**Road Networks:**
```
  NYC ---- Boston
   |         |
Philly --- DC

Vertices = Cities
Edges = Roads
```

**File Systems:**
```
     root
    /    \
  docs   code
   |      |
 notes  main.cpp

Vertices = Files/Folders
Edges = Contains relationship
```

### Types of Graphs

**1. Directed vs. Undirected:**

Undirected (friendship):
```
A --- B  (A knows B, B knows A)
```

Directed (following):
```
A --→ B  (A follows B, but B doesn't follow A)
```

**2. Weighted vs. Unweighted:**

Unweighted:
```
A --- B  (just connected)
```

Weighted:
```
A --5-- B  (5 km distance, 5 min drive time, etc.)
```

**3. Cyclic vs. Acyclic:**

Cyclic (has loops):
```
A → B → C → A  (can return to start)
```

Acyclic (no loops):
```
A → B → C  (tree-like)
```

---

## Part 2: Graph Representations (15 minutes)

### Adjacency Matrix

2D array where matrix[i][j] = 1 if edge exists

```
Graph:     Adjacency Matrix:
  0--1        0  1  2  3
  |  |      0 [0, 1, 1, 0]
  2--3      1 [1, 0, 0, 1]
            2 [1, 0, 0, 1]
            3 [0, 1, 1, 0]
```

**Pros:**
- Fast edge lookup: O(1)
- Simple to implement

**Cons:**
- Space: O(V²) always
- Sparse graphs waste space

### Adjacency List

Array of lists, one per vertex

```
Graph:     Adjacency List:
  0--1      0: [1, 2]
  |  |      1: [0, 3]
  2--3      2: [0, 3]
            3: [1, 2]
```

**Pros:**
- Space: O(V + E)
- Efficient for sparse graphs
- Fast to iterate neighbors

**Cons:**
- Edge lookup: O(degree)
- Slightly more complex

### Our Project Uses Adjacency List!

**Why?**
- File systems are sparse (not every file connects to every file)
- Need to efficiently traverse directories
- Space efficient for large file systems

---

## Part 3: Graph Implementation in C++ (20 minutes)

### Basic Structure

```cpp
class Graph {
private:
    int numVertices;
    // Adjacency list: vertex → list of neighbors
    unordered_map<string, vector<string>> adjList;
    
public:
    Graph(int vertices);
    
    void addVertex(const string& vertex);
    void addEdge(const string& from, const string& to);
    void removeEdge(const string& from, const string& to);
    
    vector<string> getNeighbors(const string& vertex);
    bool hasEdge(const string& from, const string& to);
    
    void display();
};
```

### Adding Vertices

```cpp
void Graph::addVertex(const string& vertex) {
    if (adjList.find(vertex) == adjList.end()) {
        adjList[vertex] = vector<string>();
        numVertices++;
    }
}
```

### Adding Edges

```cpp
// For directed graph
void Graph::addEdge(const string& from, const string& to) {
    // Add vertices if they don't exist
    addVertex(from);
    addVertex(to);
    
    // Add edge from → to
    adjList[from].push_back(to);
}

// For undirected graph
void Graph::addUndirectedEdge(const string& v1, const string& v2) {
    addEdge(v1, v2);  // v1 → v2
    addEdge(v2, v1);  // v2 → v1
}
```

### Getting Neighbors

```cpp
vector<string> Graph::getNeighbors(const string& vertex) {
    if (adjList.find(vertex) != adjList.end()) {
        return adjList[vertex];
    }
    return vector<string>();  // Empty if vertex doesn't exist
}
```

---

## Part 4: File System as a Graph (15 minutes)

### The Problem: Ransomware Detection

**Ransomware behavior:**
- Encrypts many files quickly
- Accesses files in unusual patterns
- Modifies files across directories

**To detect:** Model file system as graph, track access patterns

### File System Graph

```
                root
               /    \
           Users    System
           /        /     \
        Alice    Logs   Config
        /   \     |       |
    Docs   Pics  app.log sys.cfg
     |      |
  doc1  photo1
```

**Graph representation:**
- Nodes = Files and directories
- Edges = Contains/access relationships
- Directed = Parent → Child

### Building the Graph

```cpp
class RansomwareDetector {
private:
    Graph* fileSystemGraph;
    
public:
    void buildFileSystem() {
        // Root directory
        fileSystemGraph->addVertex("root");
        
        // Level 1
        fileSystemGraph->addVertex("Users");
        fileSystemGraph->addVertex("System");
        fileSystemGraph->addEdge("root", "Users");
        fileSystemGraph->addEdge("root", "System");
        
        // Level 2
        fileSystemGraph->addVertex("Alice");
        fileSystemGraph->addEdge("Users", "Alice");
        
        // Add files
        fileSystemGraph->addVertex("doc1.txt");
        fileSystemGraph->addEdge("Docs", "doc1.txt");
        
        // ... more structure
    }
};
```

### Access Tracking

```cpp
struct FileAccess {
    string fileName;
    time_t accessTime;
    string operation;  // read/write/delete
};

void trackAccess(const string& file, const string& operation) {
    FileAccess access;
    access.fileName = file;
    access.accessTime = time(0);
    access.operation = operation;
    
    accessHistory.push_back(access);
}
```

---

## Part 5: Graph Applications in Cybersecurity (10 minutes)

### 1. Ransomware Detection

**Pattern Analysis:**
- Normal: Few scattered file accesses
- Ransomware: Many files accessed rapidly

**Graph helps:**
- Track which files are connected
- Detect breadth-first access patterns
- Identify suspicious traversal

### 2. Network Topology

**Model:**
- Nodes = Computers/servers
- Edges = Network connections

**Use:**
- Find attack paths
- Identify critical nodes
- Isolate compromised systems

### 3. Malware Propagation

**Model:**
- Nodes = Systems
- Edges = Communication links

**Use:**
- Track infection spread
- Predict next targets
- Plan containment

### 4. Access Control

**Model:**
- Nodes = Users and resources
- Edges = Permission relationships

**Use:**
- Verify authorization
- Detect privilege escalation
- Audit access paths

---

## Part 6: Performance Analysis (5 minutes)

### Time Complexity

| Operation | Adjacency Matrix | Adjacency List |
|-----------|------------------|----------------|
| Add vertex | O(V²) (resize) | O(1) |
| Add edge | O(1) | O(1) |
| Remove edge | O(1) | O(E) |
| Has edge? | O(1) | O(degree) |
| Get neighbors | O(V) | O(degree) |
| Space | O(V²) | O(V + E) |

### Space Analysis

**Example: 1000 files**

Adjacency Matrix:
- 1000 × 1000 = 1,000,000 entries
- Even if only 2000 connections!

Adjacency List:
- 1000 vertex entries + 2000 edge entries
- 3,000 entries total
- **333× more efficient!**

### Our Project

- Thousands of files
- Sparse connections (tree-like)
- **Adjacency list is perfect!**

---

## Part 7: Hands-On Practice (10 minutes)

### Exercise 1: Draw a Graph

Create a graph for this file system:
```
root
├── home
│   ├── user
│   │   ├── file1.txt
│   │   └── file2.txt
└── etc
    └── config.ini
```

**Solution:**
```
         root
        /    \
     home    etc
      |       |
     user   config.ini
     /  \
file1  file2
```

### Exercise 2: Adjacency List

For this graph:
```
  A → B
  ↓   ↓
  C → D
```

Write the adjacency list.

**Solution:**
```
A: [B, C]
B: [D]
C: [D]
D: []
```

### Exercise 3: Detect Pattern

Which access pattern is suspicious?

**Pattern A:**
```
doc1.txt (9:00)
doc2.txt (9:15)
doc3.txt (10:30)
```

**Pattern B:**
```
file1 (14:00)
file2 (14:00)
file3 (14:00)
file4 (14:01)
file5 (14:01)
... 100 more files in 2 minutes
```

**Answer:** Pattern B - rapid access to many files (ransomware-like!)

---

## Summary and Key Takeaways

✅ **Graphs:** Vertices + Edges model relationships

✅ **Representations:**
- Adjacency Matrix: O(V²) space, O(1) edge lookup
- Adjacency List: O(V+E) space, efficient for sparse

✅ **File System:**
- Modeled as directed graph
- Enables behavior analysis
- Detects ransomware patterns

✅ **Next:** Graph traversal algorithms (BFS/DFS) to analyze patterns!

---

## Next Session Preview

**Session 6: Graph Traversal (BFS/DFS)**

We'll learn to navigate graphs and detect ransomware!

**You'll learn:**
- Breadth-First Search (BFS)
- Depth-First Search (DFS)
- When to use each
- Detecting suspicious access patterns
- Complete ransomware detector

**See you in Session 6!** 🚀
