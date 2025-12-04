#ifndef RANSOMWARE_DETECTOR_H
#define RANSOMWARE_DETECTOR_H

#include "Graph.h"
#include <string>
#include <vector>

struct BehaviorPattern {
    int rapidEncryption;
    int massFileAccess;
    int suspiciousTraversal;
    bool isRansomware;
    
    BehaviorPattern();
};

class RansomwareDetector {
private:
    Graph* fileSystem;
    BehaviorPattern pattern;
    
    void analyzeTraversal(const std::vector<std::string>& traversal);
    
public:
    RansomwareDetector();
    ~RansomwareDetector();
    
    void buildFileSystem();
    void simulateNormalAccess();
    void simulateRansomwareAccess();
    BehaviorPattern detectRansomwareBehavior();
    void displayAnalysis(const BehaviorPattern& pattern);
};

#endif // RANSOMWARE_DETECTOR_H
