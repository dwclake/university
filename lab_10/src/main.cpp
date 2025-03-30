/* Devon Webb */
/* CSCI 41 Lab Section 06 */
/* Lab 10 */

#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

struct Data {
    Data(int d, int p): data(d), priority(p) {}

    int data;
    int priority;
};

struct priority_queue {
    priority_queue() {}

    void insert(int data, int priority);
    int poll();
    int peek();
    void sort_up(int child);
    void sort_down(int parent);
    void display();

    private:
        void print(int parent, int height);
        int height(int idx);
        void swap(int x, int y);
        void remove();
        vector<Data> data_heap;
};

void priority_queue::swap(int x, int y) {
    Data temp = data_heap[x];
    data_heap[x] = data_heap[y];
    data_heap[y] = temp;
}

void priority_queue::sort_up(int child) { // Sorts elements from children to parents
    if(child == 0) return;

    int parent = floor(child  / 2);
    if(data_heap[parent].priority > data_heap[child].priority) {
        swap(parent, child);
        sort_up(parent);
    }
} 

void priority_queue::sort_down(int parent) { // Sorts elements from parent to children
    int left = 2 * parent + 1;
    int right = 2 * parent + 2;

    if(left >= data_heap.size()) return;

    int min = parent;
    if(data_heap[parent].priority > data_heap[left].priority) {
        min = left;
    }
    if(right < data_heap.size() && data_heap[right].priority > data_heap[right].priority) {
        min = right;
    }

    if(min != parent) {
        swap(parent, min);
        sort_down(min);
    }
}

void priority_queue::remove() {
    swap(0, data_heap.size() - 1);
    data_heap.pop_back();
    
    sort_down(0);
}

void priority_queue::insert(int data, int priority) {
    Data temp(data, priority);

    if(this->data_heap.size() == 0) {
        data_heap.push_back(temp);
    } else {
        data_heap.push_back(temp);

        int new_element = this->data_heap.size() - 1;
        sort_up(new_element);
    }
}

int priority_queue::peek() {
    return data_heap[0].data;
}

int priority_queue::poll() {
    int data = data_heap[0].data;
    remove();

    return data;
}

void priority_queue::display() { // Displays queue level by level
    int height = floor(log2(data_heap.size())) + 1;
    printf("Priority queue: [data, priority]\n");
    for(int i = 1; i <= height; i++) {
        print(0, i);
        printf("\n");
    }
}

void priority_queue::print(int parent, int height) {
    if(parent >= data_heap.size()) return;
    if(height == 1) {
        printf("[%d, %d] ", data_heap[parent].data, data_heap[parent].priority); // Display parent
    } else if(height > 1) {
        print(2 * parent + 1, height - 1); // Display left child
        print(2 * parent + 2, height - 1); // Display right child
    }
}

int main() {
    priority_queue queue;

    queue.insert(5, 2); 
    queue.insert(3, 1); 
    queue.insert(6, 12);
    queue.insert(2, 4);
    queue.insert(5, 6);
    queue.insert(6, 6);
    queue.insert(17, 5);
    queue.insert(10, 8);
    queue.insert(4, 3);
    queue.insert(3, 2);

    queue.display();
    
    printf("\nThe highest priority item in the priority queue is: %d (peek)\n", queue.peek());
    printf("The highest priority item in the priority queue is: %d (poll)\n\n", queue.poll());
    queue.display();

    printf("The highest priority item in the priority queue is: %d (poll)\n\n", queue.poll());
    queue.display();
    return 0;
}
