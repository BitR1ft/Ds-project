# Session 3: Trie Exercises

Practice problems for mastering Trie data structures.

---

## Exercise 1: Basic Trie Operations (Beginner)

**Problem:** Implement a function to count how many words in a Trie start with a given prefix.

**Example:**
```
Trie contains: "apple", "app", "application", "banana"
countWordsWithPrefix("app") → 3  ("apple", "app", "application")
countWordsWithPrefix("ban") → 1  ("banana")
countWordsWithPrefix("cat") → 0  (no words)
```

**Solution:**
```cpp
int countWordsWithPrefix(TrieNode* root, const string& prefix) {
    TrieNode* current = root;
    
    // Navigate to prefix node
    for (char ch : prefix) {
        if (current->children.find(ch) == current->children.end()) {
            return 0;  // Prefix doesn't exist
        }
        current = current->children[ch];
    }
    
    // Count all words from this node
    return countWords(current);
}

int countWords(TrieNode* node) {
    if (!node) return 0;
    
    int count = node->isEndOfWord ? 1 : 0;
    
    for (auto& pair : node->children) {
        count += countWords(pair.second);
    }
    
    return count;
}
```

---

## Exercise 2: Autocomplete System (Intermediate)

**Problem:** Implement an autocomplete feature that returns the top 3 most common words with a given prefix.

**Hint:** Store frequency count in each end node, sort results.

**Solution Approach:**
1. Modify TrieNode to include `int frequency`
2. Track how many times each word is inserted
3. When searching with prefix:
   - Navigate to prefix node
   - DFS to collect all words with frequencies
   - Sort by frequency (descending)
   - Return top 3

---

## Exercise 3: Dictionary Spell Checker (Intermediate)

**Problem:** Given a Trie with valid English words, implement a spell checker that suggests corrections for misspelled words.

**Features needed:**
- Detect if word is in dictionary
- Suggest words that differ by 1 character
- Suggest words that are missing 1 character
- Suggest words that have 1 extra character

**Challenge:** Make it efficient!

---

## Exercise 4: Memory Optimization (Advanced)

**Problem:** The current Trie uses `unordered_map` for children, which has overhead. Redesign it to use:
1. Array-based children for lowercase letters only
2. Calculate space savings
3. Benchmark performance difference

**Hint:** 
```cpp
TrieNode* children[26];  // For 'a' to 'z'
int index = ch - 'a';    // Convert char to index
```

---

## Exercise 5: Longest Common Prefix (Advanced)

**Problem:** Given all words in a Trie, find the longest prefix that is common to all words.

**Example:**
```
Words: "flower", "flow", "flight"
Longest common prefix: "fl"

Words: "dog", "cat", "car"
Longest common prefix: "" (empty)
```

**Solution:**
```cpp
string longestCommonPrefix(TrieNode* root) {
    string prefix = "";
    TrieNode* current = root;
    
    // While there's exactly one child and not end of word
    while (current->children.size() == 1 && !current->isEndOfWord) {
        auto it = current->children.begin();
        prefix += it->first;
        current = it->second;
    }
    
    return prefix;
}
```

---

## Exercise 6: Delete Operation (Challenge)

**Problem:** Implement a delete operation that removes a word from the Trie and cleans up unnecessary nodes.

**Requirements:**
- Remove the word
- Delete nodes that become unused
- Don't delete nodes used by other words

**Example:**
```
Trie: "cat", "car", "card"
Delete "card" → Remove node 'd' only
Delete "car" → Remove node 'r' only  
Delete "cat" → Remove nodes 't', 'a', 'c' (if no other words)
```

**Hint:** Use recursion, return true if node should be deleted.

---

## Exercise 7: Virus Signature Matching (Real-World)

**Problem:** You have 1000 virus signatures in a Trie. Implement a scanner that:
1. Loads signatures from a file
2. Scans a text file for any signature
3. Reports all matches with positions
4. Calculates scan time

**Bonus:** Compare with naive O(m×n) approach and measure speedup.

---

## Solutions Summary

**Time Complexities:**
- Insert: O(k) where k = word length
- Search: O(k)
- Prefix count: O(k + m) where m = matching words
- Delete: O(k)
- Autocomplete: O(k + n log n) where n = results

**Space Complexity:**
- Worst case: O(ALPHABET_SIZE × total_characters)
- Best case (shared prefixes): Much better!

**Key Insights:**
- Tries excel at prefix operations
- Memory efficiency depends on prefix sharing
- Great for autocomplete, spell check, pattern matching
- Foundation for more advanced algorithms (Aho-Corasick)

---

## Challenge Project

**Build a T9 (Predictive Text) System:**

T9 is the old phone keyboard where:
- 2 = ABC
- 3 = DEF
- 4 = GHI
- etc.

When user types "4663", show possible words: "good", "home", "hood", etc.

**Requirements:**
1. Load dictionary into Trie
2. Map digits to letters
3. Find all possible words for digit sequence
4. Rank by frequency

This is how old phones did predictive text!

---

**Keep practicing! Tries are fundamental to many real-world applications.**
