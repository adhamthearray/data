#pragma once

#include "Vector.h"
#include <stdexcept>
using namespace std;
// Priority Queue Template Class
template <typename T>
class PriorityQueue {
private:
    Vector<T> heap;  // Internal container to store elements

    // Compare two elements (default is max-heap behavior)
    bool compare(const T& a, const T& b) const {
        
        return a > b;
    }

public:
    // Default Constructor
    PriorityQueue();

    // Check if the queue is empty
    bool empty() const;

    // Get the size of the queue
    int size() const;

    // Add an element to the priority queue
    void push(const T& value);

    // Remove the top element (highest priority)
    void pop();

    // Get the top element (highest priority)
    const T& top() const;
};


// Default Constructor
template <typename T>
PriorityQueue<T>::PriorityQueue() : heap() {}

// Check if the queue is empty
template <typename T>
bool PriorityQueue<T>::empty() const {
    return heap.empty();
}

// Get the size of the queue
template <typename T>
int PriorityQueue<T>::size() const {
    return heap.getSize();
}

// Add an element to the priority queue
template <typename T>
void PriorityQueue<T>::push(const T& value) {
    heap.push_back(value);
    // Sort manually without algorithm library
    for (int i = heap.getSize() - 1; i > 0; --i) {
        if (compare(heap[i], heap[i - 1])) {
            T temp = heap[i];
            heap[i] = heap[i - 1];
            heap[i - 1] = temp;
        }
        else {
            break;
        }
    }
}

// Remove the top element (highest priority)
template <typename T>
void PriorityQueue<T>::pop() {
    if (empty()) {
        throw std::out_of_range("PriorityQueue is empty.");
    }
    heap.erase(*(heap.begin())); // Remove the first element (highest priority)
}

// Get the top element (highest priority)
template <typename T>
const T& PriorityQueue<T>::top() const {
    if (empty()) {
        throw std::out_of_range("PriorityQueue is empty.");
    }
    return *(heap.begin());
}
