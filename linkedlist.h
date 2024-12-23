#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <exception> // For exception handling
using namespace std;
template <typename T>
class LinkedList {
private:
    
     // Pointer to the first node
     // Pointer to the last node
    int listSize; // Number of elements in the list

public:
    class accessnode {

      public:
        T* OG_NODE;
        accessnode* next;
        // mmkn yb2a fy error 3shan graph::usernode
        accessnode(T* x) {
            this->OG_NODE = x;
            this->next = nullptr;
        }
        //~accessnode() {
        //    // Ensure proper cleanup of the linked list structure
        //    cout << "u1";
        //    delete OG_NODE;
        //    cout << "u2";
        //    // Free the dynamically allocated node, if applicable
        //    OG_NODE = nullptr; 
        //    cout << "u3";// Avoid dangling pointer

        //    // No need to delete 'next' here since it is usually managed by the container
        //    next = nullptr; // Safety measure

        //    // Optional debug output
        //    std::cout << "Destructor called for accessnode." << std::endl;
        //}
    };
    // Constructor and destructor
    accessnode* head;
    accessnode* tail;
    LinkedList();
    LinkedList(const LinkedList& other);
    ~LinkedList();
    // List operations
    int size() const;
    bool empty() const;
    void append(T* node_to_add);
    void remove(const T& value);
    void IterateByIndex() const;
    T* search_by_index(int index);
    void clear();
};

//t =usernode
//Node=accessnode
// Node constructor template
//template <typename T>
//LinkedList<T>::Node::Node(const T& value) : data(value), next(nullptr) {}

// LinkedList constructor template
template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), listSize(0) {}

// LinkedList destructor template
template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

// Return the size of the list
template <typename T>
int LinkedList<T>::size() const {
    return listSize;
}

// Check if the list is empty
template <typename T>
bool LinkedList<T>::empty() const {
    return listSize == 0;
}

// Add an element to the back of the list
template <typename T>
void LinkedList<T>::append(T* node_to_add) {
    accessnode* node = new accessnode(node_to_add);
    if (tail!=0) {
        tail->next = node;     // Link the new node to the current tail
    }
    else {
        head = node;  // If the list is empty, set the new node as the head
    }

    tail = node;
    listSize++;// Update the tail to point to the new node
}

// Iterate through the list by index and print (placeholder functionality)
template <typename T>
void LinkedList<T>::IterateByIndex() const {
    accessnode* temp = head;
    int index = 1;
    while (temp) {
        cout << " at index " << index << ": " << *(temp->OG_NODE)<< endl;
        temp = temp->next;
        index++;
    }
}
template <typename T>
T* LinkedList<T>::search_by_index(int index) {
    if (!head) {
        // If the list is empty
        throw std::out_of_range::out_of_range("The list is empty.");
    }

    if (index < 1 || index > listSize) {
        // If the index is out of range
        throw out_of_range("Index out of range.");
    }

    // Traverse the list to find the node at the given index
    accessnode* temp = head;
    int currentIndex = 1; // Start at the first node (1-based index)
    while (currentIndex < index) {
        temp = temp->next;
        currentIndex++;
    }

    return temp->OG_NODE; // Return the node at the specified index
}
// Remove a node by value
template <typename T>
void LinkedList<T>::remove(const T& value) {
    try {
        if (this->empty()) {
            throw std::out_of_range("List is empty99999999999");
        }

        // Handle the case where the value is at the head
        while (head && *(head->OG_NODE) == value) {
            accessnode* temp = head;
            head = head->next;
            delete temp;
            --listSize;
        }

        if (!head) {
            tail = nullptr;
            return;
        }

        // Handle other cases
        accessnode* current = head;
        while (current->next) {
            if (*(current->next->OG_NODE) == value) {
                accessnode* temp = current->next;
                current->next = current->next->next;
                delete temp;
                --listSize;
                if (!current->next) {
                    tail = current;
                }
            }
            else {
                current = current->next;
            }
        }
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Error:111111111111111 " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "An unknown error occurred." << std::endl;
    }
}




template <typename T>
  LinkedList<T>:: LinkedList(const LinkedList& other) : head(nullptr) {
        if (!other.head) {
            return;
        }
        head = new accessnode(other.head->OG_NODE);
        accessnode* current = head;
        accessnode* otherCurrent = other.head->next;
        while (otherCurrent) {
            current->next = new accessnode(otherCurrent->OG_NODE);
            current = current->next;
            otherCurrent = otherCurrent->next;
        }
 }




 

// Clear the list
template <typename T>
void LinkedList<T>::clear() {
    cout << "clear";
    while (head) {
        cout << "clear2";
        accessnode* temp = head;
        
        head = head->next;
        delete temp;
        cout << "clear3";
    }
    listSize = 0;
    cout << "clear4";
}

#endif // LINKEDLIST_H
