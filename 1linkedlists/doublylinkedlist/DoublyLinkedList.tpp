#ifndef DOUBLYLINKEDLIST_TPP
#define DOUBLYLINKEDLIST_TPP

#include "DoublyLinkedList.h"

// used for tests, DO NOT REMOVE
template <typename Data>
DoubleNode<Data>* DoublyLinkedList<Data>::get_front() const {
    return head;
}

template <typename Data>
DoubleNode<Data>* DoublyLinkedList<Data>::get_back() const {
    return tail;
}

// your code below this line
template <typename Data>
void DoublyLinkedList<Data>::add_to_front(const Data& data) {
    // create a new node, duh
    DoubleNode<Data>* new_node = new DoubleNode<Data>(); 

    // base case, empty list
    if (head == nullptr) {
        head = tail = new_node;
    } else {
        // new node's next points to current head
        new_node->next = head;

        // current head's prev points to new node
        head->prev = new_node; 

        // update head to point to new node
        head = new_node; 
    }
    ++size; 
} 

template <typename Data>
void DoublyLinkedList<Data>::add_to_back(const Data& data) {
    // create new node 
    DoubleNode<Data>* new_node = new DoubleNode<Data>();

    // base case, empty list 
    if (tail == nullptr) {
        head = tail = new_node;
    } else {
        // current tail points to new node
        tail->next = new_node;

        // new node prev points to current tail
        new_node->prev = tail;

        // update tail to point to new node
        tail = new_node; 
    }

    ++size; 
}

template <typename Data>
void DoublyLinkedList<Data>::remove_from_front() {
    // base case, empty list
    if (head == nullptr) {
        throw std::out_of_range("list is empty");
    }

    // single node 
    if (head == tail) {
        delete head;
        head = tail = nullptr;
    } else {
        // save old head
        DoubleNode<Data>* old_head = head; 
        
        // move head to next node
        head = head->next;

        // set new head's prev to nullptr
        head->prev = nullptr;

        // delete old head
        delete old_head;
    }
    --size; 
}

template<typename Data>
void DoublyLinkedList<Data>::remove_from_back() {
    // base case, empty list 
    if (tail == nullptr) {
        throw std::out_of_range("list is empty");
    } 

    // only one node
    if (head == tail) {
        delete tail;
        head = tail = nullptr;
    } else {
        // save old tail
        DoubleNode<Data>* old_tail = tail;

        // move tail to previous node
        tail = tail-prev;

        // set new tail's next to nullptr
        tail->next = nullptr;

        // delete old tail
        delete old_tail;
    }
    --size; 
}

#endif 
