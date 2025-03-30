#include <iostream>

using namespace std;
int main( )
{
    cout << "Hello, World!" << endl;
    return 0;
}

// March 10, Linked Lists
//
// Array issues:
//  Cannot change size unless using alloc
//      char* arr;
//      arr = (*char) malloc(sizeof(char) * n);
//      arr = (*char) realloc( ___ ,sizeof(char) * n + 1);
//  Must be contiguous in memory
//      When "removing" a middle element, elements after must be shifted back,
//          then keep track of which element is the "top"
// Array positives:
//  Can access elements in O(1)
//      starting address + i(32) for int
//      starting address + i(8) for chars
//  Accessing is O(1)
//  
//  Linked List:
//      Dynamic data structure
//      Uses double memory size compared to arrays
//      More efficient with deletions and insertions
//      Consists of nodes which hold data and keep a pointer to the next node in the list
//      Final node holds a nullptr for the next node pointer
//
//  struct myData {
//      int ___,
//      char ___,
//      float ___,
//      myData* next,
//  }
//
//  class Node {
//      private String data,
//      private Node next 
//  }
//
//  The only way we have to access an element is the element before it 
//  When inserting, you need to connect new element to the one that will
//      be after it first, then connect the one before it, else 
//      memory will be leaked, same for removing
//
//  March 13, Linked list continued
//
//  Exam and quiz:
//      c++
//      complexity
//      binary search logn
//      sorting
//          bubble n2
//          insertion n2
//          selection n2
//          merge nlogn
//          quicksort nlogn
//
//  Linked List:
//      Self referential
//      
template<typename T>
struct node {
    private:
        T data;
        node *next;
};

//      LList list = new LList();
//      node nodeA = new node("G", null);
//      list->head = nodeA;
//      node nodeB = new node("C", null);
//
//  to insert at end:
//      list->tail->next = nodeB;
//      list->tail = nodeB;
//  to insert at front:
//      nodeB->next = list->head;
//      list->head = nodeB;
//  to insert in middle:
//      nodeC->next = nodeB->next;
//      nodeB->next = nodeC;
//  a->b->c->d
//  removing head:
//      node temp = list->head;
//      list->head = head->next;
//      delete temp;
//  removing tail:
//      node temp = list->tail;
//      list->tail = c;
//      delete temp;
//  removing in middle:
//      a->next = b->next;
//      delete b;

template<typename T>
class LList {
    private:
        node<T> *head, *tail;
};
