#include <iostream>
#include <ctime>
#include "../include/MalwareScanner.h"
#include "../include/RansomwareDetector.h"
#include "../include/NetworkIDS.h"
#include "../include/ThreatIntelligence.h"

void printHeader() {
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║    INTEGRATED CYBER THREAT DETECTION SUITE                ║" << std::endl;
    std::cout << "║    CS-214 Data Structures Project                         ║" << std::endl;
    std::cout << "║    BS Cyber Security Program                              ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════════╝" << std::endl;
    std::cout << "\n";
}

void printSection(const std::string& title) {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "  " << title << std::endl;
    std::cout << std::string(60, '=') << std::endl;
}

int main() {
    printHeader();
    
    // Initialize Threat Intelligence System
    ThreatIntelligence* intel = new ThreatIntelligence();
    
    // ========== MODULE 1: MALWARE SIGNATURE SCANNER ==========
    printSection("MODULE 1: MALWARE SIGNATURE SCANNER");
    
    MalwareScanner* malwareScanner = new MalwareScanner();
    
    // Add some malware signatures
    std::cout << "Loading malware signature database..." << std::endl;
    malwareScanner->addSignature("malicious_payload");
    malwareScanner->addSignature("trojan");
    malwareScanner->addSignature("virus");
    malwareScanner->addSignature("ransomware_key");
    malwareScanner->addSignature("backdoor");
    std::cout << "✓ Loaded 5 malware signatures using Trie & Aho-Corasick" << std::endl;
    
    // Scan test data
    std::cout << "\nScanning test file for malware..." << std::endl;
    std::string testData = "This file contains a trojan and malicious_payload that should be detected.";
    auto malwareMatches = malwareScanner->scanText(testData);
    malwareScanner->displayResults(malwareMatches);
    
    // Log to intelligence system
    intel->addMalwareResults(malwareMatches);
    
    // ========== MODULE 2: RANSOMWARE BEHAVIOR DETECTOR ==========
    printSection("MODULE 2: RANSOMWARE BEHAVIOR DETECTOR");
    
    RansomwareDetector* ransomwareDetector = new RansomwareDetector();
    
    std::cout << "Building file system graph structure..." << std::endl;
    ransomwareDetector->buildFileSystem();
    std::cout << "✓ File system graph created with DFS/BFS traversal" << std::endl;
    
    ransomwareDetector->simulateNormalAccess();
    ransomwareDetector->simulateRansomwareAccess();
    
    BehaviorPattern pattern = ransomwareDetector->detectRansomwareBehavior();
    ransomwareDetector->displayAnalysis(pattern);
    
    // Log to intelligence system
    intel->addRansomwareAlert(pattern.isRansomware);
    
    // ========== MODULE 3: NETWORK INTRUSION DETECTION SYSTEM ==========
    printSection("MODULE 3: NETWORK INTRUSION DETECTION SYSTEM");
    
    NetworkIDS* networkIDS = new NetworkIDS();
    
    std::cout << "Initializing Network IDS with AVL Tree and Priority Queue..." << std::endl;
    
    // Add blacklisted IPs
    networkIDS->addBlacklistIP("192.168.1.100");
    networkIDS->addBlacklistIP("10.0.0.50");
    std::cout << "✓ Blacklist loaded using Hash Table" << std::endl;
    
    // Simulate network packets
    std::cout << "\nProcessing network packets..." << std::endl;
    
    time_t baseTime = time(0);
    
    // Normal traffic
    for (int i = 0; i < 5; i++) {
        Packet* p = new Packet("172.16.0.5", "8.8.8.8", 443, "HTTPS", baseTime + i, 1024);
        networkIDS->processPacket(p);
    }
    
    // Suspicious traffic from blacklisted IP
    for (int i = 0; i < 3; i++) {
        Packet* p = new Packet("192.168.1.100", "172.16.0.10", 80, "HTTP", baseTime + 10 + i, 512);
        networkIDS->processPacket(p);
    }
    
    // Port scan simulation
    for (int i = 0; i < 15; i++) {
        Packet* p = new Packet("203.0.113.5", "172.16.0.10", 1000 + i, "TCP", baseTime + 20 + i, 64);
        networkIDS->processPacket(p);
    }
    
    // DDoS simulation
    for (int i = 0; i < 55; i++) {
        Packet* p = new Packet("198.51.100.10", "172.16.0.10", 80, "HTTP", baseTime + 40 + i, 128);
        networkIDS->processPacket(p);
    }
    
    std::cout << "✓ Processed packets stored in AVL Tree" << std::endl;
    
    networkIDS->analyzeTraffic();
    networkIDS->displayThreats();
    
    // Log to intelligence system
    intel->addNetworkThreats(networkIDS->getThreatQueue());
    
    // ========== MODULE 4: THREAT INTELLIGENCE & REPORTING ==========
    printSection("MODULE 4: THREAT INTELLIGENCE & REPORTING");
    
    std::cout << "Consolidating threat data from all modules..." << std::endl;
    std::cout << "✓ Using Hash Tables for threat database" << std::endl;
    std::cout << "✓ Using Linked Lists for event logging" << std::endl;
    
    intel->displaySummary();
    
    // Generate comprehensive report
    intel->generateReport("threat_report.txt");
    
    // ========== FINAL SUMMARY ==========
    printSection("DETECTION SUITE SUMMARY");
    
    std::cout << "\n✓ All modules executed successfully!" << std::endl;
    std::cout << "\nData Structures Demonstrated:" << std::endl;
    std::cout << "  • Trie - Malware signature storage" << std::endl;
    std::cout << "  • Aho-Corasick Automaton - Multi-pattern matching" << std::endl;
    std::cout << "  • Graph - File system representation" << std::endl;
    std::cout << "  • DFS/BFS - File system traversal" << std::endl;
    std::cout << "  • AVL Tree - Balanced packet storage" << std::endl;
    std::cout << "  • Max-Heap - Priority-based threat ranking" << std::endl;
    std::cout << "  • Hash Table - Fast threat lookups and IP tracking" << std::endl;
    std::cout << "  • Linked List - Event log management" << std::endl;
    
    std::cout << "\n📊 Complete threat report saved to: threat_report.txt" << std::endl;
    std::cout << "\n" << std::string(60, '=') << std::endl;
    
    // Cleanup
    delete malwareScanner;
    delete ransomwareDetector;
    delete networkIDS;
    delete intel;
    
    return 0;
}
