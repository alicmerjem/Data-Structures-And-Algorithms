#ifndef QUEUEBASEDSTACK_TPP
#define QUEUEBASEDSTACK_TPP

#include "QueueBasedStack.h"
#include "Node.h"

template<typename Data>
QueueBasedStack<Data>::QueueBasedStack() {
    // Constructor - Initialize any required data if needed
}

template<typename Data>
void QueueBasedStack<Data>::push(const Data& data) {
    // add new element to empty queue2
    q2.enqueue(data);

    // move all elements from q1 to q2
    while(!q1.is_empty()) {
        q2.enqueue(q1.dequeue());
    }

    // swap q1 and q2
    Queue<Data> temp = q1;
    q1 = q2;
    q2 = temp;
}

template<typename Data>
Data QueueBasedStack<Data>::pop() {
    // base case, empty stack
    if(q1.is_empty()) {
        throw std::out_of_range("stack is empty");
    }

    // otherwise, just dequeue from q1
    // because the first element gets dequeued 
    return q1.dequeue(); 
}

template<typename Data>
Data QueueBasedStack<Data>::peek() const {
    // base case, empty 
    if (q1.is_empty()) {
        throw std::out_of_range("empty stack");
    }

    return q1.peek();
}

// helper methods 
template<typename Data>
int QueueBasedStack<Data>::size() const {
    return q1.size();
}

template<typename Data>
bool QueueBasedStack<Data>::is_empty() const {
    return q1.is_empty();
}

#endif