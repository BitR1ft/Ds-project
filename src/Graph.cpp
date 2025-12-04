#include "../include/Graph.h"
#include <queue>

GraphNode::GraphNode(const std::string& n, const std::string& t) 
    : name(n), type(t), isEncrypted(false), accessCount(0) {}

Graph::Graph() {}

Graph::~Graph() {
    for (auto& pair : nodes) {
        delete pair.second;
    }
}

void Graph::addNode(const std::string& name, const std::string& type) {
    if (nodes.find(name) == nodes.end()) {
        nodes[name] = new GraphNode(name, type);
    }
}

void Graph::addEdge(const std::string& from, const std::string& to) {
    adjList[from].push_back(to);
}

std::vector<std::string> Graph::getNeighbors(const std::string& node) {
    if (adjList.find(node) != adjList.end()) {
        return adjList[node];
    }
    return std::vector<std::string>();
}

GraphNode* Graph::getNode(const std::string& name) {
    if (nodes.find(name) != nodes.end()) {
        return nodes[name];
    }
    return nullptr;
}

std::vector<std::string> Graph::getAllNodes() {
    std::vector<std::string> result;
    for (auto& pair : nodes) {
        result.push_back(pair.first);
    }
    return result;
}

std::vector<std::string> Graph::BFS(const std::string& start) {
    std::vector<std::string> result;
    std::unordered_set<std::string> visited;
    std::queue<std::string> q;
    
    q.push(start);
    visited.insert(start);
    
    while (!q.empty()) {
        std::string current = q.front();
        q.pop();
        result.push_back(current);
        
        // Increment access count
        if (nodes.find(current) != nodes.end()) {
            nodes[current]->accessCount++;
        }
        
        for (const auto& neighbor : getNeighbors(current)) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                q.push(neighbor);
            }
        }
    }
    
    return result;
}

std::vector<std::string> Graph::DFS(const std::string& start) {
    std::vector<std::string> result;
    std::unordered_set<std::string> visited;
    DFSUtil(start, visited, result);
    return result;
}

void Graph::DFSUtil(const std::string& node, std::unordered_set<std::string>& visited, 
                    std::vector<std::string>& result) {
    visited.insert(node);
    result.push_back(node);
    
    // Increment access count
    if (nodes.find(node) != nodes.end()) {
        nodes[node]->accessCount++;
    }
    
    for (const auto& neighbor : getNeighbors(node)) {
        if (visited.find(neighbor) == visited.end()) {
            DFSUtil(neighbor, visited, result);
        }
    }
}
