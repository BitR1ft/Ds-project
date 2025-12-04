#ifndef THREAT_INTELLIGENCE_H
#define THREAT_INTELLIGENCE_H

#include "HashTable.h"
#include "LinkedList.h"
#include "PriorityQueue.h"
#include <string>
#include <vector>

class ThreatIntelligence {
private:
    HashTable* threatDB;
    LinkedList* eventLog;
    std::vector<std::string> malwareSignatures;
    std::vector<std::string> suspiciousIPs;
    std::vector<std::string> ransomwareIndicators;
    
public:
    ThreatIntelligence();
    ~ThreatIntelligence();
    
    void addThreat(const std::string& type, const std::string& value);
    void logEvent(const std::string& timestamp, const std::string& type, 
                  const std::string& description, const std::string& severity);
    bool isThreatKnown(const std::string& indicator);
    void generateReport(const std::string& filename);
    void displaySummary();
    
    // Integration with other modules
    void addMalwareResults(const std::vector<std::pair<int, std::string>>& matches);
    void addRansomwareAlert(bool detected);
    void addNetworkThreats(MaxHeap* threats);
};

#endif // THREAT_INTELLIGENCE_H
