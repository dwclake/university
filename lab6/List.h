/*
 *  CSCI 115 - 03
 *  Lab 6
 *
 *  Devon Webb
 */

#include <tuple>
#include <cstdio>
#include <sstream>
#include <functional>

// Node for constructing a doubly linked list
template <class t>
struct Node {
  Node(t value): data(value), next(nullptr), previous(nullptr) {}
  ~Node();

  t data;
  Node<t>* next;
  Node<t>* previous;
};

// List destructor
template <class t>
Node<t>::~Node() {
  Node<t>* current = this;

  if (current->next) {
    delete current->next;
  }
}

// Insert into a linked list passing the head pointer by value, and returning the new head
template <class t>
Node<t>* insert(Node<t>* head, t value) {
  // If head is null, just return a new node pointer
  if (!head) {
    return new Node<t>{value};
  }

  // Create new node
  auto new_head = new Node<t>{value};
  // Make a copy of the head pointer
  Node<t>* tmp = head;

  // Point new_head->next to the old head tmp
  // Point the old head tmp->previous to the new head
  new_head->next = tmp;
  tmp->previous = new_head;

  return new_head;
}

// Insert into a linked list passing a pointer to the head pointer
template <class t>
void insert_by_ptr(Node<t>** head, t value) {
  // Create new node
  auto new_head = new Node<t>{value};
  // Make a copy of the head pointer
  Node<t>* tmp = *head;

  // Point new_head->next to the old head tmp
  // Point the old head tmp->previous to the new head
  new_head->next = tmp;
  tmp->previous = new_head;

  *head = new_head;
}

// Insert into a linked list passing the head pointer by reference
template <class t>
void insert_by_ref(Node<t>*& head, t value) {
  // Create new node
  auto new_head = new Node<t>{value};
  // Make a copy of the head pointer
  Node<t>* tmp = head;
  
  // Point new_head->next to the old head tmp
  // Point the old head tmp->previous to the new head
  new_head->next = tmp;
  tmp->previous = new_head;

  head = new_head;
}

// Seach through list and check if value exists
template <class t>
bool search(Node<t>* head, t value) {
  // Iterate through list and check if nodes data == value, return true if it does
  for ( auto node = head; node; node = node->next ) {
    if ( node->data == value ) return true;
  }

  // Return false as value was not found
  return false;
}

// Sorts the linked list using selection sort
template <class t>
void list_sort(Node<t>* head, const std::function<bool(const t&, const t&)>& predicate) {
  // Iterate through list starting at head
  for ( auto i = head; i; i = i->next ) {
    // Iterate through list starting at head->next
    for ( auto j = i->next; j; j = j->next ) {
      // If predicate returns true, swap data between nodes
      if (predicate(i->data, j->data)) {
        t tmp = i->data;
        i->data = j->data;
        j->data = tmp;
      }
    }
  }
}

template <class t>
void debug(Node<t>* head) {
  if ( !head ) {
    std::printf("[]\n");
    return;
  }

  std::stringstream ss;

  ss << "[";
  for ( auto node = head; node; node = node->next ) {
    ss << node->data << ", ";
  }
  std::string str = ss.str().substr(0, ss.str().length() - 2);
  str.append("]");

  std::printf("%s\n", str.c_str());
}

void debug(Node<std::tuple<int, int>>* head) {
  if ( !head ) {
    std::printf("[]\n");
    return;
  }

  std::stringstream ss;

  ss << "[";
  for ( auto node = head; node; node = node->next ) {
    ss << "{" << std::get<0>(node->data) << ", " << std::get<1>(node->data) << "}" << ", ";
  }
  std::string str = ss.str().substr(0, ss.str().length() - 2);
  str.append("]");

  std::printf("%s\n", str.c_str());
}
