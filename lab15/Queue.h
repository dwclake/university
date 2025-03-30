/*
 *  CSCI 115 - 03
 *  Lab 15
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

    // Priority Queue class, which stores the highest priority node at the tail
    template <class t>
    struct Priority {
        QNode<t>* head;
        QNode<t>* tail;
        std::function<bool(const t&, const t&)> predicate;
        int size;

        // Constructor taking a predicate which will be used for sorting the priority queue
        Priority(const std::function<bool(const t&, const t&)>& predicate): head(nullptr), tail(nullptr), size(0) {
            this->predicate = predicate;
        }
        ~Priority();

        bool is_empty() { return size == 0; }
        void debug();

        t dequeue();
        void enqueue(t value);
    };
    
    // Priority destructor
    template <class t>
    Priority<t>::~Priority() {
        delete head;
        this->head = nullptr;
        this->tail = nullptr;
    }

    // Add a value to the priority queue
    template <class t>
    void Priority<t>::enqueue(t value) {
        if (this->size == 0) {
            insert(this->head, value);
            this->tail = this->head;
        } else {
            insert(this->head, value);
        }

        size++;

        list_sort(this->head, this->predicate);
    }

    // Retrieves and removes the node with the highest priority, ie the tail
    template <class t>
    t Priority<t>::dequeue() {
        if (this->size == 0) {
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
        QNode<t>* current = this->head;
        
        for (; current && current->next != tmp; current = current->next) {}

        delete tmp;

        current->next = nullptr;
        this->tail = current;
        size--;

        return value;
    }
}

#endif