#include <cstdio>
#include <ctime>
#include <random>
#include <algorithm>
using namespace std;

const int NUM_OF_ELEMENTS = 250000;

// -- Fucntions for sorting vector ------------------------------------------------------

// Swaps two values in a vector
void swap_vec(int left, int right, vector<int> &vec) {
    int temp = vec[left];
    vec[left] = vec[right];
    vec[right] = temp;
}

// Partitioning function for quicksort
int partition(int lo, int hi, vector<int> &vec) {
    int pivot = vec[hi]; // Set pivot to the value at hi
    int i = (lo - 1); // Set i to one before lo

    // Iterate from lo to hi
    for(int j = lo; j < hi; j++) {
        if(vec[j] <= pivot) { // If value at j is less then or equal to pivot swap i and j
            i++;
            swap_vec(i, j, vec);
        }
    }
    swap_vec(i + 1, hi, vec);

    return(i + 1); // Return i + 1, the value for the vec to be partitioned around
}

// Quicksorts a vector
void quicksort(int lo, int hi, vector<int> &vec) {
    if(lo < hi) { // If lo is less then high, partition the vec from lo to hi
        int part_idx = partition(lo, hi, vec);

        quicksort(lo, part_idx -1, vec); // Sort the vec from lo to one before part_idx
        quicksort(part_idx + 1, hi, vec); // Sort the vec from one after part_idx to hi
    }
}

// -- Priority queue using a vector -----------------------------------------------------

// Data structure holding a int data and a int priority
struct Data {
    Data(int d, int p): data(d), priority(p) {}

    int data;
    int priority;
};

// Priority queue structure using a vec to store the data (lower priority num, higher priority)
struct pqueue_vec {
    pqueue_vec() {}

    void insert(int data, int priority); // Insert a Data object into the queue
    Data poll(); // Remove and return the element with the highest priority in the vec
    int peek(); // Return the highest priority element in the vec without removing it
    void bubblesort(); // Sort the vec using bubblesort
    void heapsort(); // Sort the vec using heapsort

private:
    void delMin(); // Delete element witn the lowest priority in the list
    void swap(int x, int y); // Swap the two values at the given indices
    vector<Data> data_vec; // Vector to store data in
};

// Swap the two values at the given idicies
void pqueue_vec::swap(int x, int y) {
    Data temp = data_vec[x];
    data_vec[x] = data_vec[y];
    data_vec[y] = temp;
}

// Sort the vec using bubblesort
void pqueue_vec::bubblesort() {
    int size = data_vec.size() - 1;

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size - i; j++) {
            if( data_vec[j].priority < data_vec[j + 1].priority ) {
                swap(j, j + 1);
            }
        }
    }
}

// Sort the vec using heapsort
void pqueue_vec::heapsort() {
    for(int i = 0; i < data_vec.size(); i++) {
        int j = i;

        while(j > 0 && data_vec[j / 2].priority > data_vec[j].priority) {
            swap(j / 2, j);
            j = j / 2;
        }
    }
}

// Delete the element with the highest priority (lower num, higher priority)
void pqueue_vec::delMin() {
    data_vec.pop_back();
}

// Insert a Data object into the queue
void pqueue_vec::insert(int data, int priority) {
    // Push back a new Data instance using given data and priority
    data_vec.push_back(Data(data, priority));
}

// Returns the data stored in the element with the highest priority
int pqueue_vec::peek() {
    return data_vec[data_vec.size() - 1].data;
}

// Returns and removes the data stored in the element wit the highest priority
Data pqueue_vec::poll() {
    // Copy data from the vec
    Data data = data_vec[data_vec.size() - 1];
    delMin(); // Delete the final element

    return data;
}

// -- Priority queue using heap vec -----------------------------------------------------

// Priority queue structure storing the data as a min heap using a vec (lower priority num, higher priority)
struct pqueue_heapvec {
    pqueue_heapvec() {}

    void insert(int data, int priority); // Insert a new element into the vec
    Data poll(); // Remove and return the highest priority element
    int peek(); // Return the highest priority element
    void swim(int child); // Heapify the vec from children to parents
    void sink(int parent); // Heapify the vec from parents to children
    void delMin(); // Delete the element with the highest priority

private:
    void swap(int x, int y); // Swap the elements at the given indices
    vector<Data> data_vec;
};

// Swap the elements at the given indices
void pqueue_heapvec::swap(int x, int y) {
    Data temp = data_vec[x];
    data_vec[x] = data_vec[y];
    data_vec[y] = temp;
}

// Heapify the vec from children to parents
void pqueue_heapvec::swim(int child) {
    if(child == 0) return;

    int parent = floor(child  / 2); // Calculate the parent of the child
    // If parent is greater than it's child, swap them
    if(data_vec[parent].priority > data_vec[child].priority) {
        swap(parent, child);
        swim(parent); // Call function recursively
    }
} 

// Heapify the vec from parents to children
void pqueue_heapvec::sink(int parent) {
    // Calculate the children of the parent
    int left = 2 * parent + 1;
    int right = 2 * parent + 2;

    if(left >= data_vec.size()) return; // If left is outside the vector, return

    int min = parent; // Set min to parent
    // If min is greater than left, set min to left
    if(min > data_vec[left].priority) {
        min = left;
    }
    // If right is smaller than size of vec, and min is greater than right, set min to right
    if(right < data_vec.size() && min > data_vec[right].priority) {
        min = right;
    }
    
    // If min is not equal to parent, swap parent and min, and sort recursively
    if(min != parent) {
        swap(parent, min);
        sink(min);
    }
}

// Deletes min value from vec
void pqueue_heapvec::delMin() {
    // Swap min value to the end of the vec
    swap(0, data_vec.size() - 1);
    // Remove final element
    data_vec.pop_back();
    // Heapify the vec
    sink(0);
}

// Insert a Data object into the vec
void pqueue_heapvec::insert(int data, int priority) {
    // If no elements, pushback new Data instance
    if(data_vec.size() == 0) {
        data_vec.push_back(Data(data, priority));
    // Else pushback new Data instance and heapify up the array from the new element
    } else {
        data_vec.push_back(Data(data, priority));

        int new_element = data_vec.size() - 1;
        swim(new_element);
    }
}

// Return the data of the highest priority element
int pqueue_heapvec::peek() {
    return data_vec[0].data;
}

// Remove and return the Data of the highest priority element
Data pqueue_heapvec::poll() {
    Data data = data_vec[0];
    delMin();

    return data;
}

// -- Priority queue using a heap tree --------------------------------------------------

// Node structure for storing Data in a tree
struct Node {
    Node* left;
    Node* right;
    Data data;

    Node(Data d): data(d), left(nullptr), right(nullptr) {}
};

// Priority queue structure using a tree to store a min heap
struct pqueue_heap {
    pqueue_heap(): head(nullptr) {}

    void insert(int data, int priority); // Insert a new Data object into tree
    Data poll(); // Return and remove the highest priority Node in the tree
    int peek(); // Return the highest priority Node in the tree
    void swim(Node* child); // Heapify up
    void sink(Node* parent); // Heapify down

private:
    void delMax(); // Remove the highest priority Node in the tree
    int compute_height(); // Compute the height of the tree
    int compute_leaves(); // Compute the number of leaves in the tree
    bool lookup(int key); // Check if tree contains a Node with the given key
    vector<Node*>* sameLevel(Node* current); // Returns all the nodes on the same level
    bool descendent(Node* current, Node* aNode); // Returns true if aNode is currents child
    void swap(Node* lhs, Node* rhs); // Swaps the Data constained in two Nodes
    Node* unoccupied(Node*); // Finds first unoccupied Node in the tree
    
    Node* head; // Pointer to the min Node
};

int pqueue_heap::compute_height() {
   return {};
}

int pqueue_heap::compute_leaves() {
    return {};
}

bool lookup(int key) {
    return {};
}

vector<Node*>* sameLevel(Node* current) {
    return {};
}

bool descendent(Node* current, Node* aNode) {
    return{};
}

// Swaps the Data between two Nodes
void pqueue_heap::swap(Node* lhs, Node* rhs) {
    Data temp = lhs->data;
    lhs->data = rhs->data;
    rhs->data = temp;
}

// Heapify up
void pqueue_heap::swim(Node* child) {
    if(child == nullptr) return;

} 

// Heapify down
void pqueue_heap::sink(Node* parent) {

}

// Finds the first unoccupied Node in the tree
Node* pqueue_heap::unoccupied(Node* parent) {
    if(parent == nullptr) return nullptr;

    Node* current = parent;
    if(current->left == nullptr || current->right == nullptr) {
        return current;
    } else {
        return unoccupied(current->left);
        return unoccupied(current->right);
    }
}

// Removes the highest priority Node in the tree
void pqueue_heap::delMax() {
    if(this->head == nullptr) return; // If head is null return

    Node* current = this->head;

    // If head has no children, delete head and return
    if(current->left == nullptr && current->right == nullptr) {
        this->head = nullptr;
        delete current;
        return;
    }
    // If current right exists and is higher priority than left, set head to right
    if(current->right != nullptr && current->right->data.priority < current->left->data.priority) {
        this->head = current->right;

        // Find a place to put current left
        Node* has_unoccupied = unoccupied(this->head);
        if(has_unoccupied->left == nullptr) {
            has_unoccupied->left = current->left;
        } else if(has_unoccupied->right == nullptr) {
            has_unoccupied->right = current->left;
        }
    } else {
        // Set head to current left
        this->head = current->left;

        // Find a place to put current->right
        Node* has_unoccupied = unoccupied(this->head);
        if(has_unoccupied->left == nullptr) {
            has_unoccupied->left = current->right;
        } else if(has_unoccupied->right == nullptr) {
            has_unoccupied->right = current->right;
        }
    }
    // Heapify the tree
    sink(this->head);
}

// Add a new Data object to the tree
void pqueue_heap::insert(int data, int priority) {
    // If head is null, set head to new Node object and return
    if(this->head == nullptr) { 
        this->head = new Node( Data(data, priority) );
        return; 
    }
    // Find Node with unoccupied child/children
    Node* has_unoccupied = unoccupied(this->head);
    // Insert new Node object and heapify up from new node
    if(has_unoccupied->left == nullptr) {
        has_unoccupied->left = new Node( Data(data, priority));
        swim(has_unoccupied->left);
    } else if(has_unoccupied->right == nullptr) {
        has_unoccupied->right = new Node( Data(data, priority));
        swim(has_unoccupied->right);
    }
}

// Return data of highest priority Node
int pqueue_heap::peek() {
    return this->head->data.data;
}

// Return highest priority Node's data and remove the Node
Data pqueue_heap::poll() {
    Data data = this->head->data;
    delMax();

    return data;
}

// -- Misc fuctions ---------------------------------------------------------------------

// Print out the 100 elements with the highest priority
void display(vector<int> &vec) {
    printf("100 smallest numbers in the vector: [\n");
    for(int i = 0; i < 100; i = i + 10) {
        printf("  %d ", vec[i]);
        printf("%d ", vec[i]);
        printf("%d ", vec[i]);
        printf("%d ", vec[i]);
        printf("%d ", vec[i]);
        printf("%d ", vec[i]);
        printf("%d ", vec[i]);
        printf("%d ", vec[i]);
        printf("%d ", vec[i]);
        printf("%d\n", vec[i]);
    }
    printf("]\n");
}

// Print out the 100 elements with the highest priority
template<class T>
void display_queue(T &queue) {
    printf("100 smallest priorities in the queue: [\n");
    for(int i = 0; i < 10; i++) {
        printf("  %d ", queue.poll().priority);
        printf("%d ", queue.poll().priority);
        printf("%d ", queue.poll().priority);
        printf("%d ", queue.poll().priority);
        printf("%d ", queue.poll().priority);
        printf("%d ", queue.poll().priority);
        printf("%d ", queue.poll().priority);
        printf("%d ", queue.poll().priority);
        printf("%d ", queue.poll().priority);
        printf("%d\n", queue.poll().priority);
    }
    printf("]\n");
}

// Calculate the time elapsed in ms
double elapsed(clock_t start, clock_t end) {
    return (end - start) / (CLOCKS_PER_SEC/1000.0);
}

int main() {
    
    // -- Algorith #1 - vector quicksort ------------------------------------------------
    // Vector to store random numbers
    vector<int> vec;

    // Setup random num generator
    random_device rd;
    default_random_engine generator(rd());
    uniform_int_distribution<int> distribution(0, NUM_OF_ELEMENTS * 2);
    // Insert random numbers into vec
    for(int i = 0; i < NUM_OF_ELEMENTS; i++) {
        vec.push_back(distribution(generator));
    }
    
    clock_t v_start = clock();
    // Sort the vector
    quicksort(0, vec.size(), vec);

    clock_t v_end = clock();
    // Display the highest priority elements and print time elapsed
    display(vec);
    printf("Time taken to sort a 250,000 element vector with quicksort %.3f ms\n\n", 
            elapsed(v_start, v_end));

    // -- Algorithm #2 - Priority queue bubblesort --------------------------------------
    // Priority queue using vec 
    pqueue_vec queue1;
    // Insert random numbers into queue
    for(int i = 0; i < NUM_OF_ELEMENTS; i++) {
        queue1.insert(distribution(generator), distribution(generator));
    }
    
    clock_t qv_start1 = clock();
    // Sort the queue
    queue1.bubblesort();

    clock_t qv_end1 = clock();
    // Display the highest priority elements, and print time elapsed
    display_queue(queue1);
    printf("Time taken to sort a 250,000 element p-queue with bubblesort %.3f ms\n\n", 
            elapsed(qv_start1, qv_end1));

    // -- Algorithm #3 - Priority queue heapsort ----------------------------------------
    // Priority queue using vec 
    pqueue_vec queue2;
    // Insert random numbers into queue
    for(int i = 0; i < NUM_OF_ELEMENTS; i++) {
        queue2.insert(distribution(generator), distribution(generator));
    }
    
    clock_t qv_start2 = clock();
    // Sort with heapsort
    queue1.heapsort();

    clock_t qv_end2 = clock();
    // Print highest priority elements and print time elapsed
    display_queue(queue2);
    printf("Time taken to sort a 250,000 element p-queue with heapsort %.3f ms\n\n", 
            elapsed(qv_start2, qv_end2));

    // -- Algorithm #4 - Priority queue storing data as a heap vector -------------------
    // Priority queue with a min heap
    pqueue_heapvec queue3;

    clock_t qh_start1 = clock();
    // Insert random numbers into queue
    for(int i = 0; i < NUM_OF_ELEMENTS; i++) {
        queue3.insert(distribution(generator), distribution(generator));
    }

    clock_t qh_end1 = clock();
    // Display highest priority elements and print time taken
    display_queue(queue3);
    printf("Time taken to create a 250,000 element p-queue storing data as heap(vec) %.3f ms\n\n", 
            elapsed(qh_start1, qh_end1));

    // -- Algorithm #5 - Priority queue storing data as a heap tree ---------------------
    // Priority queue with a min heap tree
    pqueue_heap queue4;

    clock_t qh_start2 = clock();
    // Insert random numbers into queue
    for(int i = 0; i < NUM_OF_ELEMENTS; i++) {
        queue4.insert(distribution(generator), distribution(generator));
    }

    clock_t qh_end2 = clock();
    // Display highest priority numbers and print time taken
    display_queue(queue4);
    printf("Time taken to create/sort a 250,000 element p-queue storing data as heap(tree) %.3f ms\n\n", 
            elapsed(qh_start2, qh_end2));

    // Display time taken all next to each other so I can take screenshots
    printf("\nTime taken summary(each is using 250,000 elements):\n"); 
    printf("Vector with quicksort             %.3f ms\n", 
            elapsed(v_start, v_end));
    printf("P-queue with bubblesort           %.3f ms\n", 
            elapsed(qv_start1, qv_end1));
    printf("P-queue with heapsort             %.3f ms\n", 
            elapsed(qv_start2, qv_end2));
    printf("P-queue storing data as heap(vec) %.3f ms\n", 
            elapsed(qh_start1, qh_end1));
}
