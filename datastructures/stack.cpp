#include <iostream>

template<typename T>
struct Node {
    T data;
    Node<T>* next;

    Node(): next(nullptr) {}
    Node(T d): data(d), next(nullptr) {}
    ~Node() { delete next; next = nullptr; }
};

template<typename T>
class Stack {
    Node<T>* head;
    int size = 0;

    public:
        Stack() {}
        Stack(T data): size(1), head(new Node<T>(data)) {}
        ~Stack() { delete head; head = nullptr; }

        void push(T data);
        T pop();
        void print();
        int length() { return this->size; }
};

template<typename T>
void Stack<T>::print() {
    if (this->size == 0) {
        std::cout << "Stack is empty";
    } else {
        Node<T>* tmp = this->head;
        std::cout << "Stack printed with newest elements first:" << std::endl;

        std::cout << tmp->data << " ";
        while (tmp->next != nullptr) {
            tmp = tmp->next;
            std::cout << tmp->data << " ";
        }
    }
    std::cout << std::endl;
}

template<typename T>
void Stack<T>::push(T data) {
    if (this->size == 0) {
       this->head = new Node<T>(data); 
       this->size++;
    } else {
        Node<T>* tmp = new Node<T>(data);
        tmp->next = this->head;
        this->head = tmp;
        this->size++;
    }
}

template<typename T>
T Stack<T>::pop() {
    if (this->head == nullptr) {
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
    Stack<char>* stack = new Stack<char>('a');
    for (int i = 1; i < 11; i++) {
        stack->push(i + 97);
    }
    stack->print();
    int length = stack->length();
    for (int i = 0; i < length; i++) {
        std::cout << stack->pop() << " ";
    }
    std::cout << stack->pop() << std::endl;
}
