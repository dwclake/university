/*
 *  CSCI 115 - 03
 *  Project
 *
 *  Devon Webb
 */

#include "queue.h"

namespace Queue {
    Priority::Priority() {
        capacity = 0;
        size = 0;
        queue = nullptr;
    }
    
    Priority::Priority(int c) {
        capacity = c;
        size = 0;
        queue = new Data[capacity];
    }

    Priority::~Priority() {
        delete [] queue;
    }
        
    int Priority::get_parent(int child) {
        if (child % 2 == 0) {
            return (child / 2) - 1;
        } else {
            return (child / 2);
        }
    }

    int Priority::get_left_child(int parent) {
        return (2 * parent + 1);
    }

    int Priority::get_right_child(int parent) {
        return (2 * parent + 2);
    } 

    // Add a value to the priority queue
    void Priority::enqueue(std::tuple<int, double> v) {
        if (size < capacity) {
            Data x;
            std::tie(x.index, x.value) = v;

            int i = size;
            while (i != 0 && (x.value < queue[i / 2].value)) {
                queue[i] = queue[i / 2];
                i /= 2;
            }

            queue[i] = x;
            size++;
        }
    }

    // Retrieves and removes the node with the highest priority, ie the tail
    std::tuple<int, double> Priority::dequeue() {
        if (size > 0) {
            Data tmp = queue[0];
            queue[0] = queue[size - 1];

            this->min_heapify(0, size);

            size--;
            return {tmp.index, tmp.value};
        } else {
            return {-1, 0.0};
        }
    }

    void Priority::decrease_key(std::tuple<int, double> v) {
        int i = 0;
        bool found = false;

        int index;
        double value;
        std::tie(index, value) = v;

        while (!found && (i < this->size)) {
            if (queue[i].index == index) {
                queue[i].value = value;
                found = true;
            }
            i++;
        }
         
        if (found) {
            int child = i - 1;
            int parent = this->get_parent(child);

            while (queue[child].value < queue[parent].value && child >= 0 && parent >= 0) {
                Data tmp = queue[child];
                queue[child] = queue[parent];
                queue[parent] = tmp;

                child = parent;
                parent = this->get_parent(child);
            }
        }
    }

    void Priority::build_min_heap() {
        for (int i = (size / 2) - 1; i >= 0; i--) {
            this->min_heapify(i, size);
        }
    }

    void Priority::min_heapify(int i, int size) {
        int left, right, smallest;

        left = 2 * i + 1;
        right = 2 * i + 2;
        smallest = i;

        if (left < size && queue[left].value < queue[i].value) {
            smallest = left;
        }
        
        if (right < size && queue[right].value <  queue[smallest].value) {
            smallest = right;
        }

        if (smallest != i) {
            Data tmp = queue[i];
            queue[i] = queue[smallest];
            queue[smallest] = tmp;

            this->min_heapify(smallest, size);
        }
    }

}