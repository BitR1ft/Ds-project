#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class GraphNode {
public:
    std::string name;
    std::string type;  // "file" or "directory"
    bool isEncrypted;
    int accessCount;
    
    GraphNode(const std::string& n, const std::string& t);
};

class Graph {
private:
    std::unordered_map<std::string, GraphNode*> nodes;
    std::unordered_map<std::string, std::vector<std::string>> adjList;
    
public:
    Graph();
    ~Graph();
    
    void addNode(const std::string& name, const std::string& type);
    void addEdge(const std::string& from, const std::string& to);
    std::vector<std::string> getNeighbors(const std::string& node);
    GraphNode* getNode(const std::string& name);
    std::vector<std::string> getAllNodes();
    
    // Traversal algorithms
    std::vector<std::string> BFS(const std::string& start);
    std::vector<std::string> DFS(const std::string& start);
    void DFSUtil(const std::string& node, std::unordered_set<std::string>& visited, std::vector<std::string>& result);
};

#endif // GRAPH_H
