#ifndef XORLINKEDLIST_TPP
#define XORLINKEDLIST_TPP

#include <cstdint>
#include <iterator>

#include "XorLinkedList.h"

/**
 * These methods are already implemented for you.
 */
template<typename Data>
Node<Data>* ptr_xor(Node<Data> *p, Node<Data> *q) {
    return reinterpret_cast<Node<Data>*>(reinterpret_cast<uintptr_t>(p) ^ reinterpret_cast<uintptr_t>(q));
}

template<typename Data>
Node<Data> *XorLinkedList<Data>::get_head() const {
    return head;
}


/**
 * Your implementations below this comment.
 */

template<typename Data>
XorLinkedList<Data>::~XorLinkedList() {
    // your code
    Node<Data>* current = head;
    Node<Data>* prev = nullptr;
    Node<Data>* next;

    while (current != nullptr) {
        next = ptr_xor(prev, current->both);
        delete current;
        prev = current;
        current = next;
    }

    head = nullptr;
    size = 0;

}

template<typename Data>
XorLinkedList<Data>::XorLinkedList(const XorLinkedList<Data> &src) {
    // your code
    head = nullptr;
    size = 0;

    Node<Data>* current = src.head;
    Node<Data>* prev = nullptr;
    Node<Data>* next;

    while (current != nullptr) {
        add_to_back(current->data);
        next = ptr_xor(prev, current->both);
        prev = current;
        current = next;
    }
}

template<typename Data>
XorLinkedList<Data> &XorLinkedList<Data>::operator=(const XorLinkedList<Data> &src) {
    // your code
    if (this == &src) {
        return *this;
    }

    Node<Data>* current = head;
    Node<Data>* prev = nullptr;
    Node<Data>* next;

    while (current != nullptr) {
        next = ptr_xor(prev, current->both);
        delete current;
        prev = current;
        current = next;
    }

    head = nullptr;
    size = 0;

    current = src.head;
    prev = nullptr;

    while (current != nullptr) {
        add_to_back(current->data);
        next = ptr_xor(prev, current->both);
        prev = current;
        current = next;
    }

    return *this;
}

template<typename Data>
XorLinkedList<Data>::XorLinkedList(XorLinkedList<Data> &&src) noexcept {
    // your code
    head = src.head;
    size = src.size;

    src.head = nullptr;
    src.size = 0;
}

template<typename Data>
XorLinkedList<Data> &XorLinkedList<Data>::operator=(XorLinkedList<Data> &&src) noexcept {
    // your code
    if (this == &src) {
        return *this;
    }

    Node<Data>* current = head;
    Node<Data>* prev = nullptr;
    Node<Data>* next;

    while (current != nullptr) {
        next = ptr_xor(prev, current->both);
        delete current;
        prev = current;
        current = next;
    }

    head = src.head;
    size = src.size;

    src.head = nullptr;
    src.size = 0;

    return *this;
}

template<typename Data>
XorLinkedList<Data>::XorLinkedList(std::initializer_list<Data> list) {
    // your code
    head = nullptr;
    size = 0;

    for (const Data& item : list) {
        add_to_back(item);
    }
}

template<typename Data>
void XorLinkedList<Data>::add_to_front(const Data &data) {
    // your code
    Node<Data>* new_node = new Node<Data>{data, head};

    if (head != nullptr) {
        head->both = ptr_xor(new_node, head->both);
    }

    head = new_node;
    size++;
}

template<typename Data>
void XorLinkedList<Data>::add_to_back(const Data &data) {
    // your code
    if (head == nullptr) {
        add_to_front(data);
        return;
    }

    Node<Data>* prev = nullptr;
    Node<Data>* current = head;
    Node<Data>* next;

    while (true) {
        next = ptr_xor(prev, current->both);
        if (next == nullptr) break;
        prev = current;
        current = next;
    }

    Node<Data>* new_node = new Node<Data>{data, current};
    current->both = ptr_xor(prev, new_node);

    size++;
}

template<typename Data>
void XorLinkedList<Data>::remove_from_front() {
    // your code
    if (head == nullptr) return;

    Node<Data>* old_head = head;
    Node<Data>* next = ptr_xor(static_cast<Node<Data>*>(nullptr), head->both);


    if (next != nullptr) {
        next->both = ptr_xor(old_head, next->both);
    }

    head = next;
    delete old_head;
    size--;
}

template<typename Data>
void XorLinkedList<Data>::remove_from_back() {
    // your code
    if (head == nullptr) {
        throw std::out_of_range("List is empty");
    }

    Node<Data>* prev = nullptr;
    Node<Data>* current = head;
    Node<Data>* next = nullptr;

    if (ptr_xor(prev, current->both) == nullptr) {
        delete head;
        head = nullptr;
        size--;
        return;
    }

    while (true) {
        next = ptr_xor(prev, current->both);
        if (next == nullptr) break;
        prev = current;
        current = next;
    }

    prev->both = ptr_xor(ptr_xor(prev->both, current), static_cast<Node<Data>*>(nullptr));
    delete current;
    size--;
}

template<typename Data>
Data &XorLinkedList<Data>::get(int index) {
    // your code
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }

    Node<Data>* current = head;
    Node<Data>* prev = nullptr;
    Node<Data>* next;

    for (int i = 0; i < index; i++) {
        next = ptr_xor(prev, current->both);
        prev = current;
        current = next;
    }

    return current->data;
}

template<typename Data>
int XorLinkedList<Data>::count() const {
    // your code
    return size;
}

template<typename Data>
void XorLinkedList<Data>::reverse() {
    // your code
    if (head == nullptr || head->both == nullptr) return;

    Node<Data>* prev = nullptr;
    Node<Data>* current = head;
    Node<Data>* next;

    while (true) {
        next = ptr_xor(prev, current->both);
        if (next == nullptr) break;
        prev = current;
        current = next;
    }

    head = current;
}

template <typename Data>
class XorLinkedList<Data>::Iterator : public std::iterator<std::forward_iterator_tag, Data> {
private:
    Node<Data>* current;
    Node<Data>* prev;
public:
    explicit Iterator(Node<Data>* start) : current(start), prev(nullptr) {}

    Data& operator*() {
        // your code
        return current->data;
    }
    Iterator& operator++() {
        // your code
        if (current != nullptr) {
            Node<Data>* next = ptr_xor(prev, current->both);
            prev = current;
            current = next;
        }
        return *this;
    }

    Iterator operator++(int) {
        // your code
        Iterator temp = *this;
        ++(*this);
        return temp;
    }

    bool operator==(const Iterator& other) const {
        // your code
        return current == other.current;
    }

    bool operator!=(const Iterator& other) const {
        // your code
        return current != other.current;
    }
};

template<typename Data>
typename XorLinkedList<Data>::Iterator XorLinkedList<Data>::begin() {
    // your code
    return Iterator(head);
}

template<typename Data>
typename XorLinkedList<Data>::Iterator XorLinkedList<Data>::end() {
    // your code
    return Iterator(nullptr);
}

template<typename Data>
const Data& XorLinkedList<Data>::operator[](int index) const {
    // your code
    return const_cast<XorLinkedList<Data>*>(this)->get(index);
}

template<typename Data>
Data& XorLinkedList<Data>::operator[](const int index) {
    // your code
    return get(index);
}

#endif //XORLINKEDLIST_TPP