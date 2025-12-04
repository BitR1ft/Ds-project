#include "../include/PriorityQueue.h"

Threat::Threat(const std::string& t, const std::string& src, int sev, 
               const std::string& desc, long ts)
    : type(t), source(src), severity(sev), description(desc), timestamp(ts) {}

MaxHeap::MaxHeap() {}

MaxHeap::~MaxHeap() {
    for (auto threat : heap) {
        delete threat;
    }
}

int MaxHeap::parent(int i) {
    return (i - 1) / 2;
}

int MaxHeap::leftChild(int i) {
    return 2 * i + 1;
}

int MaxHeap::rightChild(int i) {
    return 2 * i + 2;
}

void MaxHeap::swap(int i, int j) {
    Threat* temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

void MaxHeap::heapifyUp(int i) {
    while (i > 0 && heap[parent(i)]->severity < heap[i]->severity) {
        swap(i, parent(i));
        i = parent(i);
    }
}

void MaxHeap::heapifyDown(int i) {
    int maxIndex = i;
    int left = leftChild(i);
    int right = rightChild(i);
    
    if (left < heap.size() && heap[left]->severity > heap[maxIndex]->severity) {
        maxIndex = left;
    }
    
    if (right < heap.size() && heap[right]->severity > heap[maxIndex]->severity) {
        maxIndex = right;
    }
    
    if (i != maxIndex) {
        swap(i, maxIndex);
        heapifyDown(maxIndex);
    }
}

void MaxHeap::insert(Threat* threat) {
    heap.push_back(threat);
    heapifyUp(heap.size() - 1);
}

Threat* MaxHeap::extractMax() {
    if (heap.empty()) {
        return nullptr;
    }
    
    Threat* max = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    
    if (!heap.empty()) {
        heapifyDown(0);
    }
    
    return max;
}

Threat* MaxHeap::peek() {
    return heap.empty() ? nullptr : heap[0];
}

bool MaxHeap::isEmpty() {
    return heap.empty();
}

int MaxHeap::size() {
    return heap.size();
}
