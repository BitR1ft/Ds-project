#include "../include/LinkedList.h"
#include <iostream>

EventLog::EventLog(const std::string& ts, const std::string& type, 
                   const std::string& desc, const std::string& sev)
    : timestamp(ts), eventType(type), description(desc), severity(sev) {}

ListNode::ListNode(EventLog* log) : data(log), next(nullptr) {}

LinkedList::LinkedList() : head(nullptr), tail(nullptr), count(0) {}

LinkedList::~LinkedList() {
    ListNode* current = head;
    while (current) {
        ListNode* temp = current;
        current = current->next;
        delete temp->data;
        delete temp;
    }
}

void LinkedList::append(EventLog* log) {
    ListNode* newNode = new ListNode(log);
    
    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    
    count++;
}

void LinkedList::display() {
    ListNode* current = head;
    
    std::cout << "\n=== Event Log ===" << std::endl;
    while (current) {
        std::cout << "[" << current->data->timestamp << "] "
                  << "[" << current->data->severity << "] "
                  << current->data->eventType << ": "
                  << current->data->description << std::endl;
        current = current->next;
    }
}

int LinkedList::size() {
    return count;
}

ListNode* LinkedList::getHead() {
    return head;
}
