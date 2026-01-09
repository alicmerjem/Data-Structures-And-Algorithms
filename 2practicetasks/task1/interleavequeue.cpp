template<typename Data>
void interleave_halves(Queue<Data>& queue) {
    // beginning of first half
    Node<Data>* start = queue.head;

    // will point to beginning of second half
    Node<Data>* mid = queue.head;

    // half the queue size
    int half = queue.size() / 2;

    // move mid to the start of the second half
    for (int i = 0; i < half; i++) {
        mid = mid->next;
    }

    // interleave by rewriting pointers
    for (int i = 0; i < half - 1; ++i) { 
        Node<Data>* old_start_next = start->next; // save next pointer before we break link
        Node<Data>* old_mid_next = mid->next; // save where mid currently is 

        start->next = mid;  // connect current first half node to current second half node 
        start = old_start_next; // move start forward to its old next

        mid->next = start; // connect current second half node to next first half node 
        mid = old_mid_next; // advance mid pointer to next node 
    }

    if (start) {
        start->next = mid; // connect everything together, because loop stops one iteration early 
    }
};