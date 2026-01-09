#ifndef LINKEDLIST_TPP
#define LINKEDLIST_TPP

#include "LinkedList.h"

#include <stdexcept>
#include <iterator>
#include <utility>

template<typename Data>
void LinkedList<Data>::add_to_front(const Data& data) {
    // make a new node
    Node<Data>* new_node = new Node<Data>();

    // populate with data
    new_node->data = data;

    // connect to the list
    new_node->next = head;

    // make the new node the head
    head = new_node;

    // increment duh
    ++size;
}

template<typename Data>
void LinkedList<Data>::remove_from_front() {
    // base case, empty list
    if (head == nullptr) {
        throw std::out_of_range("List is empty");
    }

    // save old head in temp pointer
    const Node<Data>* temp = head;

    // move the head to next node
    head = head->next;

    // delete old head
    delete temp;

    // decrement 
    --size;
}

template<typename Data>
void LinkedList<Data>::add_to_back(const Data& data) {
    // make a new node
    Node<Data>* new_node = new Node<Data>();

    // populate with data
    new_node->data = data;

    // base case, empty list
    if (head == nullptr) {
        head = new_node; // add a new node
    } else {
        // create a temp pointer to head
        Node<Data>* temp = head;

        // then traverse through the list, until we reach nullptr
        while(temp->next != nullptr) {
            temp = temp->next; // move forward
        }
        temp->next = new_node; // attach the new node to the end 
    }
    size++;
}

template<typename Data>
void LinkedList<Data>::remove_from_back() {
    // base case, empty list
    if (head == nullptr) {
        throw std::out_of_range("List is empty");
    } else if (head->next == nullptr) { // single node
        delete head; // delete that single head
        head = nullptr;
    } else {
        // temporary head
        Node<Data>* temp = head;
        
        // find second to last node
        while (temp->next->next != nullptr) {
            temp = temp->next; // traverse 
        }
        delete temp->next; // delete last node 
        temp->next = nullptr;
    }
    --size;
}

template<typename Data>
Data& LinkedList<Data>::get(int index) {
    if(index < 0 || index >= size) {
        throw std::out_of_range("index is out of range");
    }

    Node<Data>* temp = head; 
    for(int i = 0; i < index; ++i) {
        temp = temp->next;
    }
    return temp->data; 
}

template<typename Data>
int LinkedList<Data>::count() const {
    return size;
}

template<typename Data>
void LinkedList<Data>::reverse() {
    Node<Data>* current = head; // current is head
    Node<Data>* prev = nullptr; // before head is nothing

    while (current != nullptr) { // get to last node 
        Node<Data>* next = current->next; // store next node
        current->next = prev; // reverse, point current node back to previous
        prev = current; // move prev forward
        current = next; // move to the next node 
    }
    head = prev; // prev pointing to first node 
}

template<typename Data>
class LinkedList<Data>::Iterator : public std::iterator<std::forward_iterator_tag, Data> {
private:
    Node<Data>* current;
public:
    explicit Iterator(Node<Data>* current) : current(current) {}
    Data& operator*() {
        return current->data;
    }
    Iterator& operator++() {
        current = current->next;
        return *this;
    }

    Iterator operator++(int) {
        Iterator temp = *this;
        current = current->next;
        return temp;
    }

    bool operator==(const Iterator& other) const {
        return current == other.current;
    }

    bool operator!=(const Iterator& other) const {
        return current != other.current;
    }
};

template<typename Data>
typename LinkedList<Data>::Iterator LinkedList<Data>::begin() {
    return Iterator(head);
}

template<typename Data>
typename LinkedList<Data>::Iterator LinkedList<Data>::end() {
    return Iterator(nullptr);
}

template<typename Data>
const Data& LinkedList<Data>::operator[](int index) const {
    return get(index);
}

template<typename Data>
Data& LinkedList<Data>::operator[](const int index) {
    return get(index);
}

template<typename Data>
LinkedList<Data>::~LinkedList() {
    while (head != nullptr) {
        const Node<Data>* temp = head;
        head = head->next;
        delete temp;
    }
}

template<typename Data>
LinkedList<Data>::LinkedList(const LinkedList<Data> &src) {
    std::cout << "Linked list copy constructor" << std::endl;
    Node<Data>* current = src.head;
    while (current != nullptr) {
        add_to_back(current->data);
        current = current->next;
    }
}

template<typename Data>
LinkedList<Data> &LinkedList<Data>::operator=(const LinkedList<Data> &src) {
    std::cout << "Linked list copy assignment" << std::endl;
    // Prevent self-assignment
    if (this != &src) {
        // Clean up old data
        while (head != nullptr) {
            remove_from_front();
        }

        // Add new data
        Node<Data>* current = src.head;
        while (current != nullptr) {
            add_to_back(current->data);
            current = current->next;
        }
    }
    return *this;

    // Alternative way:
    // if (this != &src) {
    //     LinkedList<Data> temp(src);
    //     std::swap(head, temp.head);
    //     std::swap(size, temp.size);
    // }
    // return *this;
}

template<typename Data>
LinkedList<Data>::LinkedList(LinkedList<Data> &&src) noexcept {
    std::cout << "Linked list move constructor" << std::endl;
    head = src.head;
    size = src.size;

    src.head = nullptr;
    src.size = 0;

    // Alternative way:
    // std::swap(head, src.head);
    // std::swap(size, src.size);
}

template<typename Data>
LinkedList<Data> &LinkedList<Data>::operator=(LinkedList<Data> &&src) noexcept {
    std::cout << "Linked list move assignment" << std::endl;
    // Prevent self-assignment
    if (this != &src) {
        // Clean up old resources
        while (head != nullptr) {
            remove_from_front();
        }

        // Change ownership
        head = src.head;
        size = src.size;

        src.head = nullptr;
        src.size = 0;
    }
    return *this;

    // Alternative way:
    // if (this != &src) {
    //     std::swap(head, src.head);
    //     std::swap(size, src.size);
    // }
    // return *this;
}

template<typename Data>
LinkedList<Data>::LinkedList(std::initializer_list<Data> list) {
    std::cout << "Linked list initializer" << std::endl;
    for (auto it = list.begin(); it != list.end(); ++it) {
        add_to_back(*it);
    }
}

#endif