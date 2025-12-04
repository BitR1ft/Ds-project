#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <vector>
#include <string>

struct Threat {
    std::string type;
    std::string source;
    int severity;  // 1-10, higher is more severe
    std::string description;
    long timestamp;
    
    Threat(const std::string& t, const std::string& src, int sev, 
           const std::string& desc, long ts);
};

class MaxHeap {
private:
    std::vector<Threat*> heap;
    
    int parent(int i);
    int leftChild(int i);
    int rightChild(int i);
    void heapifyUp(int i);
    void heapifyDown(int i);
    void swap(int i, int j);
    
public:
    MaxHeap();
    ~MaxHeap();
    
    void insert(Threat* threat);
    Threat* extractMax();
    Threat* peek();
    bool isEmpty();
    int size();
};

#endif // PRIORITY_QUEUE_H
