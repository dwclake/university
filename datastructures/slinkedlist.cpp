// Singlely linked list implementation

#include <cmath>
#include <iostream>

template <typename T>
struct Node {
    T data;
    Node<T>* next;

    Node(): next(nullptr) {}
    Node(T d): data(d), next(nullptr) {}
    ~Node() { delete next; next = nullptr; }
};

template <typename T>
class SList {
    Node<T>* head;
    int size;
    
    public:
    SList(): size(0), head(nullptr) {}
    SList(T data): size(1), head(new Node<T>(data)) {}
    ~SList() { delete head; head = nullptr; }

    void print();
    void insert_end(T);
    void insert_front(T);
    bool search(T);
    T pop();
};

template<typename T>
void SList<T>::print() {
    if (this->head != nullptr) {
        std::cout << "List printed out in order:" << std::endl;
        
        Node<T>* current = this->head;
        std::cout << current->data << " ";
        
        while (current->next != nullptr) {
           current = current->next;
           std::cout << current->data << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "List contains no elements/head points to null" << std::endl;
    }
}

template<typename T>
void SList<T>::insert_end(T data) {
    if (this->head == nullptr) {
        this->head = new Node<T>(data);
        this->size++;
    } else {
        Node<T>* current = this->head;

        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new Node<T>(data);
        this->size++;
    }
}

template<typename T>
void SList<T>::insert_front(T data) {
    if (this->head == nullptr) {
        this->head = new Node<T>(data);
        this->size++;
    } else {
        Node<T>* new_node = new Node<T>(data);
        new_node->next = this->head;
        this->head = new_node;
        this->size++;
    }
}

template<typename T>
bool SList<T>::search(T data) {
    if (this->head == nullptr) {
        return false;
    } else if (std::abs(this->head->data - data) < 0.000001) {
        return true;
    } else {
        Node<T>* current = this->head;

        while (current->next != nullptr) {
            current = current->next;
            if (std::abs(current->data - data) < 0.000001) {
                return true;
            }
        }
    }
    return false;
}

template<typename T>
T SList<T>::pop() {
    if (this->size == 0) {
        return  *(new T);
    } else {
        Node<T>* tmp = this->head;
        T data = tmp->data;
        this->head = this->head->next;
        size--;
        return data;
    }
}

int main() {
    SList<double>* list = new SList<double>(2.4);
    list->insert_end(12.5);
    list->insert_front(3.14);
    list->print();

    std::cout << "Does 2.4 exist in list?: " << ((list->search(2.4))? "true" : "false") << std::endl;
    std::cout << "Does 6.8 exist in list?: " << ((list->search(6.8))? "true" : "false") << std::endl;
    std::cout << list->pop() << std::endl;
    std::cout << list->pop() << std::endl;
    std::cout << list->pop() << std::endl;
    list->print();
    std::cout << list->pop() << std::endl;
}
