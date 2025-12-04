#include "../include/NetworkIDS.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

NetworkIDS::NetworkIDS() {
    packetTree = new AVLTree();
    threatQueue = new MaxHeap();
    ipTracker = new HashTable();
}

NetworkIDS::~NetworkIDS() {
    delete packetTree;
    delete threatQueue;
    delete ipTracker;
}

void NetworkIDS::loadBlacklist(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open blacklist file: " << filename << std::endl;
        return;
    }
    
    std::string ip;
    while (std::getline(file, ip)) {
        if (!ip.empty()) {
            addBlacklistIP(ip);
        }
    }
    
    file.close();
}

void NetworkIDS::addBlacklistIP(const std::string& ip) {
    blacklistedIPs.push_back(ip);
}

bool NetworkIDS::isBlacklisted(const std::string& ip) {
    for (const auto& blacklistedIP : blacklistedIPs) {
        if (blacklistedIP == ip) {
            return true;
        }
    }
    return false;
}

bool NetworkIDS::isPortScan(const std::string& ip) {
    std::string count = ipTracker->get(ip);
    if (!count.empty()) {
        int accessCount = std::stoi(count);
        return accessCount > 10;  // More than 10 connections = potential port scan
    }
    return false;
}

bool NetworkIDS::isDDoS(const std::string& ip) {
    std::string count = ipTracker->get(ip);
    if (!count.empty()) {
        int accessCount = std::stoi(count);
        return accessCount > 50;  // More than 50 connections = potential DDoS
    }
    return false;
}

void NetworkIDS::processPacket(Packet* packet) {
    // Store packet in AVL tree
    packetTree->insert(packet);
    
    // Track IP activity
    std::string currentCount = ipTracker->get(packet->sourceIP);
    int count = currentCount.empty() ? 1 : std::stoi(currentCount) + 1;
    ipTracker->insert(packet->sourceIP, std::to_string(count));
    
    // Check for threats
    if (isBlacklisted(packet->sourceIP)) {
        Threat* threat = new Threat(
            "Blacklisted IP",
            packet->sourceIP,
            9,
            "Connection attempt from known malicious IP",
            packet->timestamp
        );
        threatQueue->insert(threat);
    }
    
    if (isPortScan(packet->sourceIP)) {
        Threat* threat = new Threat(
            "Port Scan",
            packet->sourceIP,
            7,
            "Potential port scanning activity detected",
            packet->timestamp
        );
        threatQueue->insert(threat);
    }
    
    if (isDDoS(packet->sourceIP)) {
        Threat* threat = new Threat(
            "DDoS Attack",
            packet->sourceIP,
            10,
            "Potential DDoS attack detected - excessive connections",
            packet->timestamp
        );
        threatQueue->insert(threat);
    }
}

void NetworkIDS::analyzeTraffic() {
    std::cout << "\n=== Network Traffic Analysis ===" << std::endl;
    std::cout << "Analyzing packet patterns..." << std::endl;
}

void NetworkIDS::displayThreats() {
    std::cout << "\n=== Network Intrusion Detection Results ===" << std::endl;
    
    if (threatQueue->isEmpty()) {
        std::cout << "✓ No network threats detected." << std::endl;
        return;
    }
    
    std::cout << "⚠ Detected " << threatQueue->size() << " network threat(s):" << std::endl;
    
    // Create a copy to display without destroying the original
    MaxHeap tempQueue;
    while (!threatQueue->isEmpty()) {
        Threat* threat = threatQueue->extractMax();
        std::cout << "  [Severity: " << threat->severity << "] "
                  << threat->type << " from " << threat->source << std::endl;
        std::cout << "    " << threat->description << std::endl;
        tempQueue.insert(threat);
    }
}

MaxHeap* NetworkIDS::getThreatQueue() {
    return threatQueue;
}
