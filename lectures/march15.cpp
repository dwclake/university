// March 15, Linked List Cont.
//

#include <iostream>
template<typename T>
struct Node {
    T data;
    Node* next;
    Node* prev;

    Node(): next(nullptr), prev(nullptr) {}
    Node(T d): data(d), next(nullptr), prev(nullptr) {}
    ~Node() { delete next; }
};

template<typename T>
class LinkedList {
    Node<T>* head;
    Node<T>* tail;
public:
    LinkedList(): head(nullptr), tail(nullptr) {}
    ~LinkedList() { delete head; }

    void print();
    void insert_front(T);
    void insert_back(T);
};

template<typename T>
void LinkedList<T>::print() {
    std::cout << "List printed out in froward order:" << std::endl;
    if (this->head != nullptr) {
        Node<T>* curr = this->head;
    
        std::cout << curr->data << " ";
        while(curr->next != nullptr) {
            curr = curr->next;
            std::cout << curr->data << " ";
        }
    }
    std::cout << std::endl;
}

template<typename T>
void LinkedList<T>::insert_front(T data) {
    if (this->head == nullptr) {
        this->head = new Node<T>(data);
    } else {
        Node<T>* tmp = new Node<T>(data);
        tmp->next = this->head;
        this->head = tmp;

        if (tail == nullptr) {
            this->tail = this->head->next;
        }
    }
}

template<typename T>
void LinkedList<T>::insert_back(T data) {
    if (this->tail == nullptr) {
        this->tail = new Node<T>(data);
    } else {
        Node<T>* tmp = new Node<T>(data);
        this->tail->next = tmp;
        this->tail = tmp;
    }
}

int main() {
    LinkedList<int> list;
    
    list.insert_front(5);
    list.print();
    list.insert_front(6);
    list.print();
}
