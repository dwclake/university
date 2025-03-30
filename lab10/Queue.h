/*
 *  CSCI 115 - 03
 *  Lab 10
 *
 *  Devon Webb
 */

#include <cstdio>
#include <sstream>

template <class t>
struct Node {
    Node(t value): data(value), next(nullptr) {}
    ~Node();

    t data;
    Node<t>* next;
};

// List destructor
template <class t>
Node<t>::~Node() {
    if (this->next) {
        delete this->next;
    }
}

// Insert into a linked list passing the head pointer by reference
template <class t>
void insert(Node<t>*& head, t value) {
    // Create new node
    auto new_head = new Node<t>{value};
    // Make a copy of the head pointer
    Node<t>* tmp = head;

    // Point new_head->next to the old head tmp
    // Point the old head tmp->previous to the new head
    new_head->next = tmp;

    head = new_head;
}

// Seach through list and check if value exists
template <class t>
bool search(Node<t>* head, t value) {
    // Iterate through list and check if nodes data == value, return true if it does
    for ( auto node = head; node; node = node->next ) {
        if ( node->data == value ) return true;
    }

    // Return false as value was not found
    return false;
}

// Prints list to terminal
template <class t>
void debug(Node<t>* head) {
    if ( !head ) {
        std::printf("[]\n");
        return;
    }

    std::stringstream ss;

    ss << "[";
    for ( auto node = head; node; node = node->next ) {
        ss << node->data << ", ";
    }
    std::string str = ss.str().substr(0, ss.str().length() - 2);
    str.append("]");

    std::printf("%s\n", str.c_str());
}

template <class t>
struct Queue {
    Node<t>* head;
    Node<t>* tail;
    int size;

    Queue(): head(nullptr), tail(nullptr), size(0) {}
    ~Queue();

    bool is_empty() { return size == 0; }

    t dequeue();
    void enqueue(t value);
};

// Queue destructor
template <class t>
Queue<t>::~Queue() {
    delete head;
    this->head = nullptr;
    this->tail = nullptr;
}

// Pushes a value onto the stack
template <class t>
void Queue<t>::enqueue(t value) {
    if (this->size == 0) {
        insert(this->head, value);
        this->tail = this->head;
    } else {
        insert(this->head, value);
    }

    size++;
}

// Retrieves the value at the top of the stack and removes it
template <class t>
t Queue<t>::dequeue() {
    if (!this->tail) {
        // If head is null, return the default value for type t
        return t{};
    } else if(this->size == 1) {
        // If size is one, head = tail
        auto tmp = this->head;
        t value = tmp->data;

        this->head = nullptr;
        this->tail = nullptr;

        delete tmp;
        size--;

        return value;
    } else if(this->size == 2) {
        // If size is two, tail must be set to head after
        auto tmp = this->tail;
        t value = tmp->data;

        this->head->next = nullptr;
        this->tail = this->head;

        delete tmp;
        size--;

        return value;
    }
    // Get value from tail
    t value = this->tail->data;

    Node<t>* tmp = this->tail;
    delete this->tail; 

    Node<t>* current = this->head;
    
    for (current; current && current != tmp; current = current->next) {}

    current->next = nullptr;
    this->tail = current;
    size--;

    return value;
}
