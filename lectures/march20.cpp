// march 20, doubly linked lists
//
// empty list:
//  size = 0
//  head.next = tail
//  tail.prev = head
//
// single node list:
//  size = 1
//      first node = last node
//  first node = head.next
//  last node = tail.prev
//
#include <iostream>

template<typename T>
struct Node {
    Node<T>* next;
    Node<T>* prev;
    T data;

    Node(): data(*(new T)), next(nullptr), prev(nullptr) {}
    Node(T d): data(d), next(nullptr), prev(nullptr) {}
    ~Node() { delete this->next; this->next = nullptr; }
};

template<typename T>
class List {
    Node<T>* head;
    Node<T>* tail;
    int size{0};

    public:
        List(): head(nullptr), tail(nullptr) {}
        ~List() { delete this->head; this->head = nullptr; }

        void insert_front(T);
        void insert_back(T);
        void insert_middle(T);
        void print_forwards();
        void print_backwards();
        bool search(T);
        T pop_front();
        T pop_back();
        T pop_middle();
};

template<typename T>
void List<T>::print_forwards() {
    if (this->size == 0) {
        std::cout << "List is empty";
    } else {
        std::cout << "List printed in forward order:" << std::endl;

        Node<T>* current = this->head;
        std::cout << current->data << " ";

        while (current->next != nullptr) {
            current = current->next;
            std::cout << current->data << " ";
        }

        std::cout << std::endl;
    }
}

template<typename T>
void List<T>::insert_front(T data) {
    if (this->size == 0) {
        this->head = new Node<T>(data);
        this->tail = this->head;
        size++;
    } else {
        Node<T>* tmp = new Node<T>(data);
        
        tmp->next = this->head;
        this->head->prev = tmp;
        this->head = tmp;
        size++;
    }
}

int main() {
    List<int>* list = new List<int>;

    list->insert_front(5);
    list->insert_front(15);
    list->insert_front(32);

    list->print_forwards();
}
