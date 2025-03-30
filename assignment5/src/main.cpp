/*
 * @author: Devon Webb
 *
 * CSCI 114
 * Section 01
 * Programming Assignment 5
 *
 * How to execute:
 *
 * gcc CSCI114_P5.cpp --std=c++11 -lstdc++ -o CSCI114_P5
 * ./CSCI114_P5
 */


#include <cstdio>

using namespace std;

struct Node {
    Node() {
        this->next = nullptr;
    }

    Node* next;
    int blocks;
    int free_blocks;
    int alloc_blocks;
    int id;
};

struct List {
    List() {
        this->root = nullptr;
        this->tail = nullptr;
        this->length = 0;
    }

    ~List() {
        if (this->root != nullptr) {
            Node* current = this->root;
            while (current != nullptr) {
                Node* next = current->next;

                delete current;
                current = next;
            }

            this->root = nullptr;
            this->tail = nullptr;
        }
    }

    void append() {
        if (length == 0) {
            this->root = new Node();
            this->tail = root;

            length++;
        } else if (length == 1) {
            this->root->next = new Node();
            this->tail = this->root->next;

            length++;
        } else {
            this->tail->next = new Node();
            this->tail = this->tail->next;

            length++;
        }
    }

    void remove(int index) {
        if (index >= this->length) return;
    }

    void sort() {

    }

    private:
    Node* root;
    Node* tail;
    int length;
};

int main() {
    printf("Dobar dan\n");
    List list = List();
    list.append();
    list.append();
    list.append();
}
