#ifndef NODE_H
#define NODE_H

template<typename Data>
struct Node {
    Data data;
    Node<Data>* both{};
};

#endif