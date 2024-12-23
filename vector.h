#pragma once
//#include "Graph.h"
#include <iostream>
#include <stdexcept> // For exception handling
template <typename T>
class Vector {
private:
    T* data;         // Pointer to the array that holds the vector elements
    int capacity; // Maximum capacity of the vector
    int size;     // Number of elements currently in the vector

    void resize(int newCapacity); // Resizes the vector's capacity

public:
    // Constructors and Destructor
    Vector();
    void destroy_elements();
    ~Vector();

    // Capacity and Size
    int getSize() const;
    int getCapacity() const;
    bool empty() const;

    // Element Access
    T& operator[](int index);
    const T& operator[](int index) const;

    // Modifiers
    void push_back(const T& value);
    void pop_back();
    void clear();
    bool contains(const T& value);
    // Utility
    void display() const;
    void erase(const T& value);


    // Get an iterator (or pointer) to the first element
    T* begin();

    const T* begin() const;

};



// ------------------- Constructors and Destructor -------------------

// Default constructor
template <typename T>
Vector<T>::Vector() : data(nullptr), capacity(0), size(0) {
    // Pre-allocate space for 4 elements to optimize initial insertions
    resize(4);
}
template <typename T>
void Vector<T>::destroy_elements() {
   

    // Ensure that we iterate over valid elements only
    for (int i = 0; i < size; ++i) {
       

        // Explicitly call the destructor of each element
        data[i].~T(); // Calling destructor for non-trivial types
    }

    
}


//// Destructor
//template <typename T>
//Vector<T>::~Vector() {
//    delete[] data;
//}
template <typename T>
Vector<T>::~Vector() {
    destroy_elements();  // Properly destroy elements if necessary
    if (data != nullptr) {
        
        delete[] data;
        
        // Use the built-in operator delete[] to free memory
    }
}

// ------------------- Private Methods -------------------

// Resizes the vector to the new capacity

template <typename T>
void Vector<T>::resize(int newCapacity) {
    T* newData = new T[newCapacity];
   
   
    for (int i = 0; i < size; i++) {
       
        newData[i] = data[i]; /////
        
    }
   
    if (data) {
       
        delete[] data;  ////
    }
   
    data = newData;
   
    capacity = newCapacity;
    
}

// ------------------- Capacity and Size -------------------

// Returns the size of the vector (number of elements)
template <typename T>
int Vector<T>::getSize() const {
    return size;
}

// Returns the capacity of the vector
template <typename T>
int Vector<T>::getCapacity() const {
    return capacity;
}

// Checks if the vector is empty
template <typename T>
bool Vector<T>::empty() const {
    return size == 0;
}

// ------------------- Element Access -------------------

// Operator[] for non-const objects
template <typename T>
T& Vector<T>::operator[](int index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range.");
    }
    return data[index];
}

// Operator[] for const objects
template <typename T>
const T& Vector<T>::operator[](int index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range.");
    }
    return data[index];
}

// ------------------- Modifiers -------------------

// Adds an element to the end of the vector
template <typename T>
void Vector<T>::push_back(const T& value) {

   
    if (size == capacity) {
       
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
       
        resize(newCapacity);
        
    }
   
   
    data[size++] = value;
   
}

// Removes the last element from the vector
template <typename T>
void Vector<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("Cannot pop from an empty vector.");
    }
    size--;
}

// Clears the vector (removes all elements)
template <typename T>
void Vector<T>::clear() {
    delete[] data;
    data = nullptr;
    size = 0;
    capacity = 0;
}

template <typename T>
inline bool Vector<T>::contains(const T& value) {

    for (int i = 0; i < size; ++i) {
        if (data[i] == value) {  // Compare each element with the provided value
            return true;
        }
    }
    return false;  // Return false if no match was found
}

// ------------------- Utility -------------------

// Displays the contents of the vector
template <typename T>
void Vector<T>::display() const {
    if (this->getSize() == 0) {
       
    }
    
    for (int i = 0; i < size; i++) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void Vector<T>::erase(const T& value) {
    // Find the first occurrence of the value
    int index = -1;
    for (int i = 0; i < size; ++i) {
        if (data[i] == value) {
            index = i;
            break;
        }
    }

    // If the value is not found, throw an exception or return (depending on your use case)
    if (index == -1) {
        throw std::out_of_range("Value not found in the vector.");
    }

    // Shift elements to the left to overwrite the element at index
    for (int i = index; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }

    --size; // Decrement size
}


template <typename T>
T* Vector<T>::begin() {
    return data; // Return a pointer to the first element
}

template <typename T>
const T* Vector<T>::begin() const {
    return data;
}
