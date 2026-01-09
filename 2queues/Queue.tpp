#ifndef QUEUE_TPP
#define QUEUE_TPP

#include "Node.h"
#include "Queue.h"

template<typename Data>
void Queue<Data>::enqueue(const Data& data) {
    // make a new node, duh 
    Node<Data> *new_node = new Node<Data>();

    // add some data to it
    new_node->data = data;

    // check if list is empty 
    if (is_empty()) {
        head = tail = new_node; // tail is head, and new node 
    } else {
        tail->next = new_node; // set the pointer to new node
        tail = new_node; // make the new node tail
    }
    ++length;
}

template<typename Data>
Data Queue<Data>::dequeue() {
    // base case, empty list
    if (is_empty()) {
        throw std::out_of_range("queue is empty");
    }

    Node<Data> *temp = head; // storing head in a temp value
    Data data = temp->data; // storing data in a temp as well
    head = head->next; // make the next node head

    if (head == nullptr) { // one element case, if we remove the head we also remove the tail
        tail = nullptr;
    }

    --lenght;
    delete temp; // delete the temp
    return data; // return data
}

template<typename Data>
const Data &Queue<Data>::peek() const {
    // base case, empty list
    if(is_empty()) {
        throw std::out_of_range("queue is empty");
    }

    // otherwise, just look at the top element, or the head if you will
    return head->data; 
}

template<typename Data>
bool Queue<Data>::is_empty() const {
    // if head is nullptr, ofc it is 
    return head == nullptr;
}

template<typename Data>
int Queue<Data>::size() const {
    return length; 
}

template<typename Data>
void Queue<Data>::reverse() {
    Node<Data>* current = head; // current is head
    Node<Data>* prev = nullptr; // before head there is nothing 

    tail = head; // the old head becomes the new tail

    while(current != nullptr) { // traverse
        Node<Data>* next = current->next; // go to next node
        current->next = prev; // next becomes prev
        prev = current; // swap and all that
        current = next;
    }
    head = prev; // prev is new head 
}

// other methods
template<typename Data>
Queue<Data>::~Queue() {
    while (head != nullptr) {
        const Node<Data> *temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
}

template<typename Data>
Queue<Data>::Queue(std::initializer_list<Data> queue) {
    for (auto it = queue.begin(); it != queue.end(); ++it) {
        enqueue(*it);
    }
}

template<typename Data>
Queue<Data>::Queue(const Queue &src) {
    Node<Data> *current = src.head;

    while (current != nullptr) {
        enqueue(current->data);
        current = current->next;
    }
}

template<typename Data>
Queue<Data> &Queue<Data>::operator=(const Queue &src) {
    if (this != &src) {
        while (head != nullptr) {
            dequeue();
        }

        Node<Data> *current = src.head;

        while (current != nullptr) {
            enqueue(current->data);
            current = current->next;
        }
    }
    return *this;
}

template<typename Data>
Queue<Data>::Queue(Queue &&src) noexcept {
    head = src.head;
    tail = src.tail;
    length = src.length;

    src.head = nullptr;
    src.tail = nullptr;
    src.length = 0;
}

template<typename Data>
Queue<Data> &Queue<Data>::operator=(Queue &&src) noexcept {
    if (this != &src) {
        while (head != nullptr) {
            dequeue();
        }

        head = src.head;
        tail = src.tail;
        length = src.length;

        src.head = nullptr;
        src.tail = nullptr;
        src.length = 0;
    }
    return *this;
}

#endif