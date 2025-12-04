#include "../include/ThreatIntelligence.h"
#include <iostream>
#include <fstream>
#include <ctime>

ThreatIntelligence::ThreatIntelligence() {
    threatDB = new HashTable();
    eventLog = new LinkedList();
}

ThreatIntelligence::~ThreatIntelligence() {
    delete threatDB;
    delete eventLog;
}

void ThreatIntelligence::addThreat(const std::string& type, const std::string& value) {
    threatDB->insert(value, type);
    
    if (type == "malware") {
        malwareSignatures.push_back(value);
    } else if (type == "ip") {
        suspiciousIPs.push_back(value);
    } else if (type == "ransomware") {
        ransomwareIndicators.push_back(value);
    }
}

void ThreatIntelligence::logEvent(const std::string& timestamp, const std::string& type,
                                   const std::string& description, const std::string& severity) {
    EventLog* log = new EventLog(timestamp, type, description, severity);
    eventLog->append(log);
}

bool ThreatIntelligence::isThreatKnown(const std::string& indicator) {
    return threatDB->contains(indicator);
}

void ThreatIntelligence::addMalwareResults(const std::vector<std::pair<int, std::string>>& matches) {
    for (const auto& match : matches) {
        addThreat("malware", match.second);
        
        time_t now = time(0);
        char timestamp[26];
        ctime_r(&now, timestamp);
        timestamp[24] = '\0';
        
        logEvent(timestamp, "Malware Detection", 
                "Signature found: " + match.second, "HIGH");
    }
}

void ThreatIntelligence::addRansomwareAlert(bool detected) {
    if (detected) {
        time_t now = time(0);
        char timestamp[26];
        ctime_r(&now, timestamp);
        timestamp[24] = '\0';
        
        addThreat("ransomware", "behavior_pattern");
        logEvent(timestamp, "Ransomware Detection",
                "Suspicious file encryption behavior detected", "CRITICAL");
    }
}

void ThreatIntelligence::addNetworkThreats(MaxHeap* threats) {
    while (!threats->isEmpty()) {
        Threat* threat = threats->extractMax();
        
        addThreat("ip", threat->source);
        
        char timestamp[26];
        time_t ts = threat->timestamp;
        ctime_r(&ts, timestamp);
        timestamp[24] = '\0';
        
        logEvent(timestamp, threat->type, threat->description,
                threat->severity > 7 ? "CRITICAL" : "HIGH");
    }
}

void ThreatIntelligence::generateReport(const std::string& filename) {
    std::ofstream report(filename);
    
    if (!report.is_open()) {
        std::cerr << "Could not create report file: " << filename << std::endl;
        return;
    }
    
    report << "========================================" << std::endl;
    report << "  INTEGRATED CYBER THREAT DETECTION    " << std::endl;
    report << "        SECURITY REPORT                " << std::endl;
    report << "========================================" << std::endl;
    
    time_t now = time(0);
    char timestamp[26];
    ctime_r(&now, timestamp);
    report << "Generated: " << timestamp << std::endl;
    
    report << "\n--- THREAT SUMMARY ---" << std::endl;
    report << "Malware Signatures Detected: " << malwareSignatures.size() << std::endl;
    report << "Suspicious IPs Identified: " << suspiciousIPs.size() << std::endl;
    report << "Ransomware Indicators: " << ransomwareIndicators.size() << std::endl;
    report << "Total Events Logged: " << eventLog->size() << std::endl;
    
    report << "\n--- MALWARE SIGNATURES ---" << std::endl;
    if (malwareSignatures.empty()) {
        report << "None detected" << std::endl;
    } else {
        for (const auto& sig : malwareSignatures) {
            report << "  - " << sig << std::endl;
        }
    }
    
    report << "\n--- SUSPICIOUS IPs ---" << std::endl;
    if (suspiciousIPs.empty()) {
        report << "None detected" << std::endl;
    } else {
        for (const auto& ip : suspiciousIPs) {
            report << "  - " << ip << std::endl;
        }
    }
    
    report << "\n--- DETAILED EVENT LOG ---" << std::endl;
    ListNode* current = eventLog->getHead();
    while (current) {
        report << "[" << current->data->timestamp << "] "
               << "[" << current->data->severity << "] "
               << current->data->eventType << ": "
               << current->data->description << std::endl;
        current = current->next;
    }
    
    report << "\n========================================" << std::endl;
    report << "           END OF REPORT                " << std::endl;
    report << "========================================" << std::endl;
    
    report.close();
    std::cout << "\n✓ Security report generated: " << filename << std::endl;
}

void ThreatIntelligence::displaySummary() {
    std::cout << "\n========================================" << std::endl;
    std::cout << "    THREAT INTELLIGENCE SUMMARY        " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Malware Signatures: " << malwareSignatures.size() << std::endl;
    std::cout << "Suspicious IPs: " << suspiciousIPs.size() << std::endl;
    std::cout << "Ransomware Indicators: " << ransomwareIndicators.size() << std::endl;
    std::cout << "Total Events: " << eventLog->size() << std::endl;
    std::cout << "========================================" << std::endl;
    
    eventLog->display();
}
