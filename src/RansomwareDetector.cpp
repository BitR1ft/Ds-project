#include "../include/RansomwareDetector.h"
#include <iostream>
#include <ctime>

BehaviorPattern::BehaviorPattern() 
    : rapidEncryption(0), massFileAccess(0), suspiciousTraversal(0), isRansomware(false) {}

RansomwareDetector::RansomwareDetector() {
    fileSystem = new Graph();
}

RansomwareDetector::~RansomwareDetector() {
    delete fileSystem;
}

void RansomwareDetector::buildFileSystem() {
    // Simulate a file system structure
    fileSystem->addNode("root", "directory");
    fileSystem->addNode("documents", "directory");
    fileSystem->addNode("pictures", "directory");
    fileSystem->addNode("music", "directory");
    fileSystem->addNode("videos", "directory");
    
    fileSystem->addNode("report.docx", "file");
    fileSystem->addNode("thesis.pdf", "file");
    fileSystem->addNode("budget.xlsx", "file");
    fileSystem->addNode("photo1.jpg", "file");
    fileSystem->addNode("photo2.png", "file");
    fileSystem->addNode("song.mp3", "file");
    fileSystem->addNode("movie.mp4", "file");
    
    // Build directory structure
    fileSystem->addEdge("root", "documents");
    fileSystem->addEdge("root", "pictures");
    fileSystem->addEdge("root", "music");
    fileSystem->addEdge("root", "videos");
    
    fileSystem->addEdge("documents", "report.docx");
    fileSystem->addEdge("documents", "thesis.pdf");
    fileSystem->addEdge("documents", "budget.xlsx");
    
    fileSystem->addEdge("pictures", "photo1.jpg");
    fileSystem->addEdge("pictures", "photo2.png");
    
    fileSystem->addEdge("music", "song.mp3");
    fileSystem->addEdge("videos", "movie.mp4");
}

void RansomwareDetector::simulateNormalAccess() {
    std::cout << "\n=== Simulating Normal File Access ===" << std::endl;
    
    // Normal user accessing a few files
    GraphNode* file1 = fileSystem->getNode("report.docx");
    GraphNode* file2 = fileSystem->getNode("photo1.jpg");
    
    if (file1) file1->accessCount = 1;
    if (file2) file2->accessCount = 1;
    
    std::cout << "Normal access pattern: 2 files accessed" << std::endl;
}

void RansomwareDetector::simulateRansomwareAccess() {
    std::cout << "\n=== Simulating Ransomware Activity ===" << std::endl;
    
    // Ransomware: rapid traversal and encryption
    std::vector<std::string> traversal = fileSystem->BFS("root");
    
    std::cout << "Suspicious traversal detected:" << std::endl;
    for (const auto& node : traversal) {
        GraphNode* gNode = fileSystem->getNode(node);
        if (gNode && gNode->type == "file") {
            gNode->isEncrypted = true;
            gNode->accessCount += 5;  // Rapid access
            std::cout << "  - " << node << " [ENCRYPTED]" << std::endl;
        }
    }
}

void RansomwareDetector::analyzeTraversal(const std::vector<std::string>& traversal) {
    int encryptedFiles = 0;
    int totalAccess = 0;
    
    for (const auto& nodeName : traversal) {
        GraphNode* node = fileSystem->getNode(nodeName);
        if (node && node->type == "file") {
            if (node->isEncrypted) encryptedFiles++;
            totalAccess += node->accessCount;
        }
    }
    
    pattern.rapidEncryption = encryptedFiles;
    pattern.massFileAccess = totalAccess;
    pattern.suspiciousTraversal = traversal.size();
}

BehaviorPattern RansomwareDetector::detectRansomwareBehavior() {
    std::vector<std::string> traversal = fileSystem->BFS("root");
    analyzeTraversal(traversal);
    
    // Detection logic
    if (pattern.rapidEncryption > 3 || pattern.massFileAccess > 15) {
        pattern.isRansomware = true;
    }
    
    return pattern;
}

void RansomwareDetector::displayAnalysis(const BehaviorPattern& pattern) {
    std::cout << "\n=== Ransomware Behavior Analysis ===" << std::endl;
    std::cout << "Rapid Encryption Count: " << pattern.rapidEncryption << std::endl;
    std::cout << "Mass File Access Count: " << pattern.massFileAccess << std::endl;
    std::cout << "Traversal Depth: " << pattern.suspiciousTraversal << std::endl;
    
    if (pattern.isRansomware) {
        std::cout << "⚠ ALERT: Ransomware behavior detected!" << std::endl;
    } else {
        std::cout << "✓ No ransomware behavior detected." << std::endl;
    }
}
