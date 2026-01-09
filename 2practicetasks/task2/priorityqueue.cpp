template <typename Data>
class PriorityQueue {
private:
    Node<Data>* head{};
    Node<Data>* tail{};
    int length{0};
    bool is_max_queue{};
public:
    // constructors
    PriorityQueue() = default;
    explicit PriorityQueue(bool is_max);
    // copy semantics
    PriorityQueue(const PriorityQueue& src);
    PriorityQueue& operator=(const PriorityQueue& src);
    // move semantics
    PriorityQueue(PriorityQueue&& src) noexcept;
    PriorityQueue& operator=(PriorityQueue&& src) noexcept;
    // destructor
    ~PriorityQueue();

    void enqueue(const Data& data);
    Data dequeue();
    bool is_empty() const;
    int size() const;
    const Data& peek() const;
};

template <typename Data>
PriorityQueue<Data>::PriorityQueue(bool is_max): is_max_queue(is_max) {}

template<typename Data>
void PriorityQueue<Data>::enqueue(const Data& data) {
    Node<Data> *new_node = new Node<Data>();
    new_node->data = data;

    if (head == nullptr) {
        head = tail = new_node;
    } else {
        // check priority against current head 
        if ((is_max_queue && data > head->data) || (!is_max_queue && data < head->data)) {
            new_node->next = head; // new node points to old head
            head = new_node; // make the new node head
        } else {
            tail->next = new_node; // append to tail
            tail = new_node;  
        }
    }
    ++length;
}

template<typename Data>
Data PriorityQueue<Data>::dequeue() {
    // just normal remove head operations
    if (head == nullptr) {
        throw std::out_of_range("Priority queue is empty");
    }

    Node<Data> *temp = head;
    Data data = temp->data;
    head = head->next;

    if (head == nullptr) {
        tail = nullptr;
    }

    delete temp;
    --length;
    
    // Rearrange head
    Node<Data>* max = head; // assuming head is the max
    Node<Data>* prev = nullptr; // will track node before current max
    Node<Data>* prev_max = nullptr; // will track node before max 
    Node<Data>* current = head ? head->next : nullptr; // if head is current, go forward otherwise we get a nullptr
    
    while (current != nullptr) { // start traversing 
        // if current is better than max 
        if ((is_max_queue && current->data > max->data) || (!is_max_queue && current->data < max->data)) {
            max = current; // found a better candidate
            if (prev == nullptr) {
                prev = head;
            }
            prev_max = prev; // save node before this better one
        }
        prev = current;
        current = current->next;
    }
    
    if (prev_max) {
        prev_max->next = max->next;
        max->next = head;
        head = max;
    }
    
    if (max == tail) {
        tail = prev_max;
    }
    
    return data;
}

template<typename Data>
bool PriorityQueue<Data>::is_empty() const {
    return head == nullptr;
};

template<typename Data>
int PriorityQueue<Data>::size() const {
    return length;
};

template<typename Data>
const Data& PriorityQueue<Data>::peek() const {
    if (head == nullptr) {
        throw std::out_of_range("Priority queue is empty");
    }
    
    return head->data;
};

template<typename Data>
PriorityQueue<Data>::~PriorityQueue() {
    while (head != nullptr) {
        const Node<Data> *temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
}

template<typename Data>
PriorityQueue<Data>::PriorityQueue(const PriorityQueue &src) {
    Node<Data> *current = src.head;
    is_max_queue = src.is_max_queue;

    while (current != nullptr) {
        enqueue(current->data);
        current = current->next;
    }
}

template<typename Data>
PriorityQueue<Data>& PriorityQueue<Data>::operator=(const PriorityQueue &src) {
    if (this != &src) {
        is_max_queue = src.is_max_queue;

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
PriorityQueue<Data>::PriorityQueue(PriorityQueue &&src) noexcept {
    head = src.head;
    tail = src.tail;
    length = src.length;
    is_max_queue = src.is_max_queue;

    src.head = nullptr;
    src.tail = nullptr;
    src.length = 0;
    src.is_max_queue = false;
}

template<typename Data>
PriorityQueue<Data>& PriorityQueue<Data>::operator=(PriorityQueue &&src) noexcept {
    if (this != &src) {
        while (head != nullptr) {
            dequeue();
        }

        head = src.head;
        tail = src.tail;
        length = src.length;
        is_max_queue = src.is_max_queue;

        src.head = nullptr;
        src.tail = nullptr;
        src.length = 0;
        src.is_max_queue = false;
    }
    return *this;
}