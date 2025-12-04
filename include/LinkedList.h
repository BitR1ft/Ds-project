#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <string>

struct EventLog {
    std::string timestamp;
    std::string eventType;
    std::string description;
    std::string severity;
    
    EventLog(const std::string& ts, const std::string& type, 
             const std::string& desc, const std::string& sev);
};

class ListNode {
public:
    EventLog* data;
    ListNode* next;
    
    ListNode(EventLog* log);
};

class LinkedList {
private:
    ListNode* head;
    ListNode* tail;
    int count;
    
public:
    LinkedList();
    ~LinkedList();
    
    void append(EventLog* log);
    void display();
    int size();
    ListNode* getHead();
};

#endif // LINKED_LIST_H
