/*
 *  CSCI 115 - 01
 *  Project
 *
 *  Devon Webb
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <cstdio>
#include <sstream>
#include <tuple>
#include <functional>

namespace Queue {
    // Singly Linked List Node class
    template <class t>
    struct QNode {
        QNode(t value): data(value), next(nullptr) {}
        ~QNode();

        t data;
        QNode<t>* next;
    };
    
    struct Data {
        int index;
        double value;
    };

    // Priority Queue class, which stores the highest priority node at the tail
    struct Priority {
        Priority();
        Priority(int c);
        ~Priority();

        bool is_empty() { return size == 0; }
        bool is_full() { return size == capacity; }

        int get_parent(int child);
        int get_left_child(int parent);
        int get_right_child(int parent);

        std::tuple<int, double> dequeue();
        void enqueue(std::tuple<int, double> value);
        void decrease_key(std::tuple<int, double> value);

        void build_min_heap();
        void min_heapify(int i, int size);

        int capacity;
        int size;
        Data* queue;
    };
    
    template <class t>
    struct Queue {
        QNode<t>* head;
        QNode<t>* tail;
        int size;

        Queue(): head(nullptr), tail(nullptr), size(0) {}
        ~Queue();

        bool is_empty() { return size == 0; }

        t dequeue();
        void enqueue(t value);
    };
    
    // List destructor
    template <class t>
    QNode<t>::~QNode() {
        if (this->next) {
            delete this->next;
        }
    }

    // Sorts the List using selection sort
    template <class t>
    void list_sort(QNode<t>* head, const std::function<bool(const t&, const t&)>& predicate) {
      // Iterate through list starting at head
      for ( auto i = head; i; i = i->next ) {
        // Iterate through list starting at head->next
        for ( auto j = i->next; j; j = j->next ) {
          // If predicate returns true, swap data between nodes
          if (predicate(i->data, j->data)) {
            t tmp = i->data;
            i->data = j->data;
            j->data = tmp;
          }
        }
      }
    }

    // Insert into a linked list passing the head pointer by reference
    template <class t>
    void insert(QNode<t>*& head, t value) {
        // Create new node
        auto new_head = new QNode<t>{value};
        // Make a copy of the head pointer
        QNode<t>* tmp = head;

        // Point new_head->next to the old head tmp
        // Point the old head tmp->previous to the new head
        new_head->next = tmp;

        head = new_head;
    }

    // Seach through list and check if value exists
    template <class t>
    bool search(QNode<t>* head, t value) {
        // Iterate through list and check if nodes data == value, return true if it does
        for ( auto node = head; node; node = node->next ) {
            if ( node->data == value ) return true;
        }

        // Return false as value was not found
        return false;
    }

    // Queue destructor
    template <class t>
    Queue<t>::~Queue() {
        delete head;
        this->head = nullptr;
        this->tail = nullptr;
    }
    
    // Pushes a value onto the queue
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
    
    // Retrieves the value at the top of the queue and removes it
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

        QNode<t>* tmp = this->tail;
        delete this->tail; 

        QNode<t>* current = this->head;
        
        for (current; current && current != tmp; current = current->next) {}

        current->next = nullptr;
        this->tail = current;
        size--;

        return value;
    }
}

#endif
