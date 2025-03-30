# Thurs 21 Sept 2023
---
## Lists
```cpp
class Node {
  int data;
  Node* next;
};

class LinkedList {
  Node* head;
  int size;
};

void LinkedList::delete(int value) {
  delete(value, head);
  delete(value, head, nullptr);
}

void delete(int value, Node*& current) {
  if ( !current ) return;
  if ( current->data > value ) return;

  if ( current->data == value ) {
    Node* tmp = current;
    current = current->next;
    delete tmp;
    return;
  }
  
  if ( current->next && current->next->data == value ) {
    Node* tmp = current->next;
    current->next = tmp->next;

    delete tmp;
    return;
  }

  delete(value, current->next);
}

void delete(int value, Node*& current, Node* previous) {
  if ( !current ) return;
  if ( current->data > value ) return;

  if ( current->data == value && !previous ) {
    Node* tmp = current;
    current = current->next;
    delete tmp;
    return;
  }
  
  if ( current->data == value ) {
    Node* tmp = current;
    prev->next = tmp->next;

    delete tmp;
    return;
  }

  delete(value, current->next, current);
}

```
---
