/* Devon Webb */
/* CSCI 41 Lab Section 06 */
/* Lab 9 */

#include <iostream>

using namespace std;

struct Node {
    double data;
    int count;
    Node* next;
    Node* prev;

    Node(): next(nullptr), prev(nullptr) {}
    Node(double d): data(d), count(1), next(nullptr), prev(nullptr) {}
    ~Node() { delete this->next; this->next = nullptr; }
};

class List {
    Node* head;
    Node* tail;
    int size;

    public:
        List(): head(nullptr), tail(nullptr), size(0) {}
        ~List() { delete this->head; this->head = nullptr; }

        Node* get_head() { return this->head; }
        Node* get_tail() { return this->tail; }
        void print_data();
        void print_data_count();
        void insert(double);
        void insert(double, int);
        bool check(double);
        void remove_dup_unsorted();
        void remove_dup_sorted();
        List* count_val();
        void quicksort(Node*, Node*);
};

void List::print_data() {
    if (this->size == 0) {
        cout << "List is empty" << endl;
    } else {
        Node* current = this->head;
        cout << current->data << " ";

        while (current->next != nullptr) {
            current = current->next;
            cout << current->data << " ";
        }
        cout << endl;
    }
}

void List::print_data_count() {
    if (this->size == 0) {
        cout << "List is empty" << endl;
    } else {
        Node* current = this->head;
        cout << current->data << " ";
        cout << current->count << " " << endl;

        while (current->next != nullptr) {
            current = current->next;
            cout << current->data << " ";
            cout << current->count << " " << endl;
        }
    }
}

// Returns true if list contains the data argument value, returns false otherwise
bool List::check(double data) {
    if (this->size == 0) return false;

    Node* current = this->head;
    do {
        if (current->data == data) return true;
        current = current->next;
    } while (current != nullptr);

    return false;
}

// Inserts at the front of the list
void List::insert(double data) {
    if (this->size == 0) {
        
        this->head = new Node(data);
        this->tail = this->head;
       
        this->size++;
    } else {
        Node* tmp = new Node(data);

        this->head->prev = tmp;
        tmp->next = this->head;
        this->head = tmp;
        
        this->size++;
    }
}

void List::remove_dup_unsorted() {
    if (this->size == 0) {
        cout << "Cannot remove duplicates from empty list" << endl;
    } else {
        Node* current = this->head;
        Node* current2 = this->head->next;

        while (current->next != nullptr) {  // Loop through each Node 
            while (current2 != nullptr) {  // Loop through each Node starting 
                                          // one after outside loop
                if (current->data == current2->data) { // Check if data is a duplicate
                    if (current2 == this->tail) { // If current2 is the tail remove it
                        current2->prev->next = nullptr;
                        this->tail = current2->prev;
                        delete current2;
                        this->size--;
                        return;
                    } else { // If current2 is not the tail, adjust both the Node
                             // before and the Node after
                        current2->prev->next = current2->next;
                        current2->next->prev = current2->prev;

                        Node* tmp = current2;
                        current2 = current2->next;

                        tmp->next = nullptr;
                        tmp->prev = nullptr;
                        delete tmp;

                        this->size--;
                    }
                } else {
                    current2 = current2->next;
                }
            }
            current = current->next;
            current2 = current->next;
        } 
    }
}

void List::remove_dup_sorted() {
    if (this->size == 0) {
        cout << "Cannot remove duplicates from empty list" << endl;
    } else {
        Node* current = this->head;
        Node* current2 = this->head->next;

        while (current->next != nullptr) {
            while (current2 != nullptr && current->data == current2->data) {
                    if (current2 == this->tail) {
                        current2->prev->next = nullptr;
                        this->tail = current2->prev;
                        delete current2;
                        this->size--;
                        return;
                    } else {
                        current2->prev->next = current2->next;
                        current2->next->prev = current2->prev;

                        Node* tmp = current2;
                        current2 = current2->next;

                        tmp->next = nullptr;
                        tmp->prev = nullptr;
                        delete tmp;

                        this->size--;
                    }
            }
            current = current->next;
            current2 = current->next;
        } 
    }
}

List* List::count_val() {
    List* new_list = new List;
    Node* current = this->head;

    do {
        if (!new_list->check(current->data)) {
            new_list->insert(current->data);
            current = current->next;
        } else {
            Node* new_current = new_list->head;
            do {
                if (new_current->data == current->data) {
                    new_current->count++;
                    break;
                }
                new_current = new_current->next;
            } while (new_current != nullptr);

            current = current->next;
        }
    } while (current != nullptr);
    
    return new_list;
}

void swap(Node* node_one, Node* node_two) {
    double tmp = node_one->data;
    node_one->data = node_two->data;
    node_two->data = tmp;
}

Node* partition(Node* lo, Node* hi) {
    Node* pivot = lo->prev;
    Node* j = lo;
    
    while (j != hi) {
        if (j->data <= hi->data) {
            if (pivot == nullptr) {
                pivot = lo;
            } else {
                pivot = pivot->next;
            }
            swap(pivot, j);
        }
        j = j->next;
    }

    if (pivot == nullptr) {
        pivot = lo;
    } else {
        pivot = pivot->next;
    }
    swap(pivot, hi);
    
    return pivot;
}

void List::quicksort(Node* lo, Node* hi) {
    if (lo == nullptr || hi == nullptr || lo == hi->next) {
        return;
    }

    Node* pivot = partition(lo, hi);
    quicksort(lo, pivot->prev);
    quicksort(pivot->next, hi);
}

int main() {
    List* unsorted_list = new List;
    
    unsorted_list->insert(3.14);
    unsorted_list->insert(3.45);
    unsorted_list->insert(2.98);
    unsorted_list->insert(3.14);
    unsorted_list->insert(3.14);
    unsorted_list->insert(2.21);
    unsorted_list->insert(2.98);
    
    cout << "Unsorted list:" << endl;
    unsorted_list->print_data();

    cout << "New List containing unique values and their count from above list:" << endl;
    List* val_list = unsorted_list->count_val();
    val_list->print_data_count();

    unsorted_list->remove_dup_unsorted();
    cout << "Duplicates removed from unsorted list at top:" << endl;
    unsorted_list->print_data();
    cout << endl;

    delete unsorted_list;

    List* list = new List;

    list->insert(13.21);
    list->insert(3.14);
    list->insert(5.16);
    list->insert(2.45);
    list->insert(3.14);
    list->insert(2.45);
    list->insert(12.4);
    list->insert(12.4);
    list->insert(11.50);
    
    cout << "List to be sorted:" << endl;
    list->print_data();

    list->quicksort(list->get_head(), list->get_tail());
    cout << "List after quicksort:" << endl;
    list->print_data();

    list->remove_dup_sorted();
    cout << "Duplicates removed from sorted list:" << endl;
    list->print_data();
    cout << endl;

    delete list;
}
