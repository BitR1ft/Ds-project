# Session 3: Trie Data Structure

**Duration:** 60-75 minutes  
**Prerequisites:** Sessions 1-2 completed  
**Goal:** Understand and implement the Trie data structure for efficient pattern storage

---

## What We'll Learn Today

By the end of this session, you will:
- ✅ Understand what a Trie is and why it's useful
- ✅ See how Tries store strings efficiently
- ✅ Learn to insert and search in a Trie
- ✅ Understand the code in our Malware Scanner
- ✅ Analyze time and space complexity
- ✅ Build a simple Trie yourself

---

## Part 1: The Problem - Pattern Matching (10 minutes)

### Scenario: Virus Signature Detection

Imagine you're building an antivirus. You have:
- **10,000 known virus signatures** (patterns)
- **Large files to scan** (gigabytes of data)

**Goal:** Find if any virus signature appears in a file.

### Naive Approach (What NOT to do)

```cpp
// Store patterns in an array
string patterns[10000] = {"virus", "trojan", "malware", ...};

// Check if text contains any pattern
bool hasVirus(string text, string patterns[], int numPatterns) {
    for (int i = 0; i < numPatterns; i++) {
        if (text.find(patterns[i]) != string::npos) {
            return true;  // Found a virus!
        }
    }
    return false;
}
```

**Problems:**
1. Search each pattern separately: O(m × n × p)
   - m = number of patterns
   - n = length of text
   - p = length of pattern
2. For 10,000 patterns in 1GB file: EXTREMELY SLOW!
3. No shared prefix optimization

### Why We Need Something Better

Consider these virus signatures:
```
virus
viral
virtuoso
virtue
```

Notice they all start with "vir"!

**Naive approach:** Stores "vir" FOUR times
**Smart approach (Trie):** Stores "vir" ONCE, branches after

This is what a Trie does!

---

## Part 2: Understanding Tries (15 minutes)

### What is a Trie?

**Trie** (pronounced "try") = A tree structure for storing strings efficiently

**Key properties:**
1. Each node represents a character
2. Path from root to node = a string prefix
3. Shared prefixes share paths
4. Leaf nodes mark complete words

### Visual Example

Store words: "cat", "car", "card", "dog", "dodge"

```
         (root)
         /    \
        c      d
        |      |
        a      o
       / \     |
      t   r    g
          |    |
          d    (e)  ← "dog" ends here
          |
         (◆)   ← "card" ends here
```

**Legend:**
- Each letter is a node
- (◆) marks end of a valid word
- Paths share common prefixes

**Words represented:**
- "cat" = root → c → a → t
- "car" = root → c → a → r
- "card" = root → c → a → r → d
- "dog" = root → d → o → g
- "dodge" = root → d → o → d → g → e

### Benefits Over Array

| Operation | Array | Trie |
|-----------|-------|------|
| Insert word | O(1) | O(k) where k = word length |
| Search word | O(n × k) | O(k) |
| Find all words with prefix | O(n × k) | O(k + results) |
| Space for shared prefixes | O(total chars) | O(unique chars) |

**Key Insight:** Trie is MUCH faster for prefix-based operations!

### Real-World Applications

**Where Tries are used:**
1. **Autocomplete** - Type "pro", suggest "program", "project"
2. **Spell checkers** - Fast dictionary lookups
3. **IP routing** - Network routers use tries
4. **Phone contacts** - T9 predictive text
5. **Antivirus** - Our malware signature matching!

---

## Part 3: Trie Structure in C++ (15 minutes)

### The TrieNode Class

```cpp
class TrieNode {
public:
    // Map of character → child node
    unordered_map<char, TrieNode*> children;
    
    // Is this the end of a valid word?
    bool isEndOfWord;
    
    // Store the complete pattern (for virus signatures)
    string pattern;
    
    // Constructor
    TrieNode() {
        isEndOfWord = false;
        pattern = "";
    }
};
```

**Understanding each part:**

1. **`children`** - Maps character to next node
   ```cpp
   // If current node is 'c', children might be:
   // 'a' → TrieNode for "ca..."
   // 'o' → TrieNode for "co..."
   ```

2. **`isEndOfWord`** - Marks valid endings
   ```cpp
   // For "car" and "card":
   // Node after 'r': isEndOfWord = true (end of "car")
   // Node after 'd': isEndOfWord = true (end of "card")
   ```

3. **`pattern`** - Stores the complete word (useful for reporting)
   ```cpp
   // When we find a virus, we want to know which one!
   ```

### The Trie Class

```cpp
class Trie {
private:
    TrieNode* root;  // Starting point of the trie
    
public:
    Trie() {
        root = new TrieNode();  // Create empty root
    }
    
    void insert(const string& word);
    bool search(const string& word);
    TrieNode* getRoot();
    void clear(TrieNode* node);
    ~Trie();  // Destructor to free memory
};
```

---

## Part 4: Implementing Trie Operations (20 minutes)

### Operation 1: Insert

**Goal:** Add a word to the Trie

**Algorithm:**
1. Start at root
2. For each character in word:
   - If character path exists, follow it
   - If not, create new node
3. Mark last node as end of word

**Code:**
```cpp
void Trie::insert(const string& word) {
    TrieNode* current = root;  // Start at root
    
    // Traverse/create path for each character
    for (char ch : word) {
        // If path doesn't exist, create it
        if (current->children.find(ch) == current->children.end()) {
            current->children[ch] = new TrieNode();
        }
        
        // Move to next node
        current = current->children[ch];
    }
    
    // Mark end of word
    current->isEndOfWord = true;
    current->pattern = word;  // Store complete word
}
```

**Example: Inserting "car"**

```
Step 0: Start at root
        (root*)

Step 1: Process 'c'
        (root)
         |
         c*

Step 2: Process 'a'
        (root)
         |
         c
         |
         a*

Step 3: Process 'r'
        (root)
         |
         c
         |
         a
         |
         r*  ← mark as end, store "car"
```

**Now insert "card":**
```
Process 'c': Path exists, follow it
Process 'a': Path exists, follow it  
Process 'r': Path exists, follow it
Process 'd': No path, CREATE new node
        (root)
         |
         c
         |
         a
         |
         r (end: "car")
         |
         d* (end: "card")
```

**Time Complexity:** O(k) where k = length of word
**Space Complexity:** O(k) for new nodes (shared prefixes reuse nodes!)

### Operation 2: Search

**Goal:** Check if a word exists in the Trie

**Algorithm:**
1. Start at root
2. For each character:
   - If path exists, follow it
   - If path doesn't exist, word not in trie
3. At end, check if it's marked as valid word

**Code:**
```cpp
bool Trie::search(const string& word) {
    TrieNode* current = root;  // Start at root
    
    // Try to follow path for each character
    for (char ch : word) {
        // If path doesn't exist, word not found
        if (current->children.find(ch) == current->children.end()) {
            return false;
        }
        
        // Move to next node
        current = current->children[ch];
    }
    
    // Check if this is actually end of a word
    // (not just a prefix)
    return current->isEndOfWord;
}
```

**Example: Searching "car" and "ca"**

Trie contains: "car", "card"

```
Search "car":
  (root) → c → a → r (isEndOfWord = true)
  ✓ Found!

Search "ca":
  (root) → c → a (isEndOfWord = false)
  ✗ Not found! (it's only a prefix)
```

**Time Complexity:** O(k) where k = length of word
**Space Complexity:** O(1) - just traversal, no new storage

### Operation 3: Prefix Search

**Bonus operation:** Find all words starting with a prefix

**Algorithm:**
1. Navigate to prefix node
2. DFS to collect all words from that node

```cpp
vector<string> findWordsWithPrefix(const string& prefix) {
    vector<string> results;
    TrieNode* current = root;
    
    // Navigate to prefix
    for (char ch : prefix) {
        if (current->children.find(ch) == current->children.end()) {
            return results;  // Prefix doesn't exist
        }
        current = current->children[ch];
    }
    
    // DFS to collect all words from here
    collectWords(current, results);
    return results;
}
```

This is how autocomplete works!

---

## Part 5: Trie in Our Malware Scanner (15 minutes)

### How It's Used

Our project uses Trie as the foundation for the Aho-Corasick algorithm (Session 4).

**File:** `include/Trie.h` and `src/Trie.cpp`

### Malware Signature Storage

```cpp
// In MalwareScanner class
Trie* signatureTrie;  // Stores all virus patterns

// Adding signatures
void addSignature(const string& signature) {
    signatureTrie->insert(signature);
    // Also builds Aho-Corasick automaton (next session!)
}
```

**Why Trie for malware signatures?**
1. Many signatures share prefixes
2. Fast insertion of new signatures
3. Foundation for multi-pattern matching
4. Memory efficient

### Example from main.cpp

```cpp
// Create malware scanner
MalwareScanner* malwareScanner = new MalwareScanner();

// Add virus signatures
malwareScanner->addSignature("malicious_payload");
malwareScanner->addSignature("trojan");
malwareScanner->addSignature("virus");
malwareScanner->addSignature("ransomware_key");
malwareScanner->addSignature("backdoor");

// Scan text
string testData = "This file contains a trojan and malicious_payload";
auto results = malwareScanner->scanText(testData);
```

**Trie structure for these signatures:**
```
                    (root)
                   /  |  \
                  b   m   r   t   v
                  |   |   |   |   |
                  a   a   a   r   i
                  c   l   n   o   r
                  k   i   s   j   u
                  d   c   o   a   s
                  o   i   m   n
                  o   o   w
                  r   u   a
                  ◆   s   r
                      _   e
                      p   _
                      a   k
                      y   e
                      l   y
                      o   ◆
                      a
                      d
                      ◆
```

### Performance Impact

**Without Trie (array of strings):**
- Each signature stored separately
- No prefix sharing
- Slower multi-pattern matching

**With Trie:**
- Shared prefixes stored once
- Memory savings: ~30-40% for real signature databases
- Foundation for O(n+z) scanning (with Aho-Corasick)

---

## Part 6: Complexity Analysis (5 minutes)

### Time Complexity

| Operation | Complexity | Explanation |
|-----------|------------|-------------|
| Insert | O(k) | k = length of word, touch each character once |
| Search | O(k) | k = length of word, check each character once |
| Delete | O(k) | k = length of word, traverse and mark |
| Prefix Search | O(k + m) | k = prefix length, m = number of results |

**Key Insight:** Time depends on word length, NOT on number of words stored!

### Space Complexity

**Worst Case:** O(ALPHABET_SIZE × N × M)
- ALPHABET_SIZE = possible characters (26 for lowercase, 256 for ASCII)
- N = number of words
- M = average word length

**Best Case (with shared prefixes):** Much less!
- Many words share paths
- Only store unique character sequences

**Example:**
Store 1000 words with average 30% prefix sharing:
- Array: 1000 × 10 chars = 10,000 chars
- Trie: ~7,000 chars (30% savings)

**Our project:**
- 10,000 signatures
- ~40% prefix sharing
- Significant memory savings!

---

## Part 7: Hands-On Practice (10 minutes)

### Exercise 1: Build a Simple Trie

Create a trie with these words:
```
"the"
"their"
"there"
"these"
```

**Draw the structure:**
```
Your turn! Draw it here:

         (root)
```

**Solution:**
```
         (root)
           |
           t
           |
           h
           |
           e (end: "the")
          /  \
         i    r
         |    |
         r    e (end: "there")
         |
        (end: "their")
        
Note: "these" would branch at 'e' after "the"
```

### Exercise 2: Trace Operations

Given this Trie:
```
        (root)
         / \
        c   d
        |   |
        a   o
       /|   |
      t r   g (end: "dog")
          |
          d (end: "card")
```

**Operations:**
1. Insert "cat" - What happens?
2. Search "dog" - What path?
3. Search "do" - What's the result?
4. Insert "car" - What nodes are created?

**Answers:**
1. Follow c→a, create new node t, mark end
2. Follow d→o→g, find end marker, return true
3. Follow d→o, no end marker, return false
4. Follow c→a→r (all exist), just mark as end

### Exercise 3: Complexity Analysis

```cpp
void insertWords(Trie& trie, string words[], int n) {
    for (int i = 0; i < n; i++) {
        trie.insert(words[i]);
    }
}
```

**What's the time complexity?**
- n words
- Average length k

**Answer:** O(n × k)
- Insert each of n words: O(n)
- Each insert is O(k): O(k)
- Total: O(n × k)

### Exercise 4: Practical Application

Design a Trie-based autocomplete system:

```cpp
class AutoComplete {
private:
    Trie trie;
    
public:
    void addWord(string word) {
        // Your code here
    }
    
    vector<string> getSuggestions(string prefix) {
        // Your code here
    }
};
```

**Hint:** Use prefix search operation!

**Solution approach:**
1. `addWord`: Just insert into trie
2. `getSuggestions`: 
   - Navigate to prefix node
   - DFS from there to collect all words
   - Return the list

---

## Part 8: Comparing with Alternatives (5 minutes)

### Trie vs. Hash Table

| Aspect | Trie | Hash Table |
|--------|------|------------|
| Exact search | O(k) | O(1) average |
| Prefix search | O(k + results) | O(n) - check all |
| Ordered traversal | Yes (alphabetical) | No |
| Space | Shared prefixes | Full words |
| Memory | Can be large | More compact |

**When to use Trie:**
- ✅ Prefix operations needed
- ✅ Autocomplete, spell check
- ✅ Pattern matching
- ✅ Dictionary operations

**When to use Hash Table:**
- ✅ Only exact lookups needed
- ✅ No prefix operations
- ✅ Memory constrained
- ✅ Random key distribution

### Trie vs. Array of Strings

| Aspect | Trie | Array |
|--------|------|-------|
| Insert | O(k) | O(1) append |
| Search | O(k) | O(n × k) |
| Prefix search | O(k) | O(n × k) |
| Space | Optimized | Simple |
| Memory efficiency | Better for shared prefixes | Worse |

**Trie wins when:**
- Many searches needed
- Prefix operations common
- Words share prefixes
- Size is large

---

## Summary and Key Takeaways

### What We Learned

✅ **Trie structure:**
- Tree where each node = character
- Paths = string prefixes
- Shared prefixes = shared paths

✅ **Operations:**
- Insert: O(k) - create path for word
- Search: O(k) - follow path, check end marker
- Prefix search: O(k + results) - find all with prefix

✅ **In our project:**
- Stores malware signatures efficiently
- Foundation for Aho-Corasick (next session)
- 30-40% memory savings
- Enables fast multi-pattern matching

✅ **When to use Tries:**
- Prefix-based operations
- Autocomplete, spell check
- Dictionary implementations
- Pattern matching systems

### Big Picture

**Trie is step 1 of our Malware Scanner:**
```
Step 1: Store patterns in Trie ← This session
        ↓
Step 2: Build Aho-Corasick automaton ← Next session
        ↓
Step 3: Scan files for all patterns simultaneously
        ↓
Result: 6,944× faster than naive approach!
```

---

## Next Session Preview

**Session 4: Aho-Corasick Algorithm**

We'll extend our Trie to enable multi-pattern matching!

**You'll learn:**
- How to find multiple patterns in one scan
- Failure links and state transitions
- Building the Aho-Corasick automaton
- Why it's O(n + z) instead of O(m × n)
- Complete malware scanner implementation

**Preparation:**
- Make sure you understand Tries thoroughly
- Review BFS (breadth-first search)
- Think about how to find multiple patterns efficiently

---

## Additional Resources

### Visualizations:
- VisuAlgo Trie: https://visualgo.net/en/trie
- Trie Data Structure (YouTube)

### Practice:
- LeetCode: Implement Trie (Problem 208)
- HackerRank: Contacts (Trie problem)

### Reading:
- "Introduction to Algorithms" - Chapter on Tries
- GeeksforGeeks Trie tutorial

---

## Session 3 Checklist

Before moving to Session 4, make sure you can:

- [ ] Explain what a Trie is and why it's useful
- [ ] Draw a Trie for a given set of words
- [ ] Trace insert and search operations
- [ ] Understand the code in Trie.h and Trie.cpp
- [ ] Explain time complexity of Trie operations
- [ ] Know when to use Trie vs. other structures
- [ ] Understand how it's used in malware scanning
- [ ] Build a simple Trie yourself

**Ready for Aho-Corasick? Let's go to Session 4!** 🚀

---

*"A Trie is like a map of word paths - follow the route to find your destination!"*
