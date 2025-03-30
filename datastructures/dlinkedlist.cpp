// Doublely Linked List Implimentation

#include <iostream>
#include <ostream>

template<typename T>
struct Node {
   T data;
   Node<T>* next;
   Node<T>* prev;

   Node(): next(nullptr), prev(nullptr) {}
   Node(T d): data(d), next(nullptr), prev(nullptr) {}
   ~Node() { delete next; next = nullptr; }
};

template<typename T>
class DList {
    public:
        DList(): size(0), head(nullptr), tail(nullptr) {}
        DList(T d): size(1), head(new Node<T>(d)), tail(this->head) {}
        ~DList() { delete head; head = nullptr; }

        void print();
        void insert_front(T);
        void insert_back(T);
        bool search(T);
    private:
        int size;
        Node<T>* head;
        Node<T>* tail;
};

template<typename T>
void DList<T>::print() {
    if (this->head == nullptr) {
        std::cout << "list has no elements" << std::endl;
    } else {
        std::cout << "List printed in forward order: ";
        
        Node<T>* tmp = this->head;
        std::cout << tmp->data << " ";
        
        while (tmp->next != nullptr) {
            tmp = tmp->next;
            std::cout << tmp->data << " ";
        }

        std::cout << std::endl;
    }
}

template<typename T>
void DList<T>::insert_front(T data) {
    if (this->size == 0) {
        this->head = new Node<T>(data);
        this->tail = this->head;
        this->size++;
    } else {
        Node<T>* tmp = new Node<T>(data);
        tmp->next = this->head;
        this->head->prev = tmp;
        this->head = tmp;
        this->size++;
    }
}

template<typename T>
void DList<T>::insert_back(T data) {
    if (this->size == 0) {
        this->tail = new Node<T>(data);
        this->head = this->tail;
        this->size++;
    } else {
        Node<T>* tmp = new Node<T>(data);
        this->tail->next = tmp;
        tmp->prev = this->tail;
        this->tail = tmp;
        this->size++;
    }
}

template<typename T>
bool DList<T>::search(T data) {
    if (this->size == 0) {
        return false;
    } else if (this->head->data == data || this->tail->data == data) {
        return true;
    } else {
        Node<T>* current = this->head;
        if (current->data == data) return true;

        while (current->next != nullptr) {
            if (current->data == data) return true;
            current = current->next;
        }
    }
    return false;
}

int main() {
    DList<std::string>* list = new DList<std::string>("Hello");   
    list->insert_front(", World");
    list->insert_front("Dobar dan");
    list->insert_back("Ichigo");
    list->insert_back("yo");
    list->print();
    std::cout << list->search("Dobar dan") << std::endl;
    std::cout << list->search("Dobar dom") << std::endl;

    delete list;
}   
