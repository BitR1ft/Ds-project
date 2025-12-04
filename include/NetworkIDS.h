#ifndef NETWORK_IDS_H
#define NETWORK_IDS_H

#include "AVLTree.h"
#include "PriorityQueue.h"
#include "HashTable.h"
#include <string>
#include <vector>

class NetworkIDS {
private:
    AVLTree* packetTree;
    MaxHeap* threatQueue;
    HashTable* ipTracker;
    std::vector<std::string> blacklistedIPs;
    
    bool isBlacklisted(const std::string& ip);
    bool isPortScan(const std::string& ip);
    bool isDDoS(const std::string& ip);
    
public:
    NetworkIDS();
    ~NetworkIDS();
    
    void loadBlacklist(const std::string& filename);
    void addBlacklistIP(const std::string& ip);
    void processPacket(Packet* packet);
    void analyzeTraffic();
    void displayThreats();
    MaxHeap* getThreatQueue();
};

#endif // NETWORK_IDS_H
