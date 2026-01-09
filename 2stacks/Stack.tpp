#ifndef STACK_TPP
#define STACK_TPP

#include "Node.h"
#include "Stack.h"

template<typename Data>
void Stack<Data>::push(const Data& data) {
    // first make a new node 
    Node<Data> *new_node = new Node<Data>();

    // then assign some data to it
    new_node->data = data;

    // make the new node point to the top of the stack
    new_node->next = top;
    
    // make the new node officially the top of the stack
    new_node = top; 

    // update the size counter
    ++length; 
}

template<typename Data>
Data Stack<Data>::pop() {
    // base case, empty stack
    if (is_empty()) {
        throw std::out_of_range("stack is empty");
    }

    // otherwise, make the current top temp
    Node<Data>* temp = top;
    
    // also temporarily store the data of the top
    Data data = temp->data;

    // move the pointer of the top to the next node 
    top = top->next;

    // decrement 
    --length;

    // delete the temp value
    delete temp;
    // return the data 
    return data;
}

template<typename Data>
const Data& Stack<Data>::peek() const {
    // base case, empty stack
    if(is_empty()) {
        throw std::out_of_range("stack is empty"); 
    }

    // otherwise, just return the top element
    return top->data;
}

template<typename Data>
bool Stack<Data>::is_empty() {
    // if the top is nullptr, the stack is empty 
    return top == nullptr;
}

template<typename Data>
int Stack<Data>::size() const {
    return length; // pretty self explanatory
}

template<typename Data>
void Stack<Data>::reverse() {
    // start at the top
    Node<Data>* current = top;
    // nothing comes initially before the first node 
    Node<Data>* prev = nullptr;

    // traverse through the entire stack
    while (current != nullptr) {
        // go to next node 
        Node<Data>* next = current->next;

        // reverse the link
        current->next = prev;

        // magic, same as linked list 
        prev = current;
        current = next;
    }
    top = prev;  // reverse everything 
}

// other stuff, constructor, rule of five and all that
template<typename Data>
Stack<Data>::~Stack() {
    while (top != nullptr) {
        const Node<Data> *temp = top;
        top = top->next;
        delete temp;
    }
}

template<typename Data>
Stack<Data>::Stack(std::initializer_list<Data> stack) {
    for (auto it = stack.begin(); it != stack.end(); ++it) {
        push(*it);
    }
}

template<typename Data>
Stack<Data>::Stack(const Stack &src) {
    Node<Data> *current = src.top;

    while (current != nullptr) {
        push(current->data);
        current = current->next;
    }
    reverse();
}

template<typename Data>
Stack<Data> &Stack<Data>::operator=(const Stack &src) {
    if (this != &src) {
        while (top != nullptr) {
            pop();
        }

        Node<Data>* current = src.top;
        while (current != nullptr) {
            push(current->data);
            current = current->next;
        }
        reverse();
    }
    return *this;
}

template<typename Data>
Stack<Data>::Stack(Stack &&src) noexcept {
    top = src.top;
    length = src.length;

    src.top = nullptr;
    src.length = 0;
}

template<typename Data>
Stack<Data> &Stack<Data>::operator=(Stack &&src) noexcept {
    if (this != &src) {
        while (top != nullptr) {
            pop();
        }

        top = src.top;
        length = src.length;

        src.top = nullptr;
        src.length = 0;
    }
    return *this;
}

#endif 