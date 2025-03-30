/*
 *  CSCI 115 - 03
 *  Lab 6
 *
 *  Devon Webb
 */

#include <cstdio>
#include <tuple>
#include <functional>
#include <sstream>
#include <vector>

/* Linked List Implementation -------------------------------------------------------- */

// Node for constructing a singly linked list
template <class t>
struct Node {
  Node(t value): data(value), next(nullptr) {}
  ~Node();

  t data;
  Node<t>* next;
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
    return new Node<t>(value);
  }

  // Create new node
  auto new_head = new Node<t>{value};
  // Make a copy of the head pointer
  Node<t>* tmp = head;

  // Point new_head->next to the old head tmp
  // Point the old head tmp->previous to the new head
  new_head->next = tmp;

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

// Prints list to terminal
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

// Prints list of std::tuple<int, int> to terminal
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

/* Question #1 ----------------------------------------------------------------------- */

// Takes an std::vector<int> and returns a pointer to a list containing the unique values, sorted
Node<int>* unique_values(std::vector<int>& array) {
  Node<int>* result = nullptr;

  // Loop through array and add the element to result as long as 
  // it doesn't exist in result
  for ( int val : array ) {
    if ( !search(result, val) ) {
      result = insert(result, val);
    }
  }

  // Sort ascending
  list_sort<int>(result, [](int lhs, int rhs) { 
    return lhs > rhs; 
  });

  return result;
}

/* Question #2 ----------------------------------------------------------------------- */

// Type def to store the value and its count
// {Value, Occurrence}
typedef std::tuple<int, int> tuple;

// Takes an std::vector<int> and returns a pointer to a list containing tuples,
// the first elem is the unique value, and the second elem is the count
Node<tuple>* count_values(std::vector<int>& array) {
  Node<tuple>* result = nullptr;

  // Find the unique values
  Node<int>* unique = unique_values(array);
  // Setup result list with an element for each unique value
  for ( auto current = unique; current; current = current->next ) {
    result = insert(result, {current->data, 0});
  }
  delete unique;

  // Iterate over every element in array
  for ( int val : array ) {
    // Find the element containing the value
    for ( auto current = result; current; current = current->next ) {
      if ( val == std::get<0>(current->data) ) {
        // Increment the count of the value
        std::get<1>(current->data)++;
      }
    }
  }

  // Sort ascending
  list_sort<tuple>(result, [](tuple lhs, tuple rhs){
    return std::get<0>(lhs) > std::get<0>(rhs);
  });

  return result;
}

/* Question #3 ----------------------------------------------------------------------- */

// Takes an std::vector<int> and returns a sorted list of all the values greater than sentinal
Node<int>* values_gt(std::vector<int>& array, int sentinal) {
  Node<int>* result = nullptr;

  // Iterate through array, adding any values greater than sentinal to result
  for ( int value : array ) {
    if ( value > sentinal ) {
      result = insert(result, value);
    }
  }

  // Sort result in ascending order
  list_sort<int>(result, [](int lhs, int rhs){
    return lhs > rhs;
  });

  return result;
}

/* Question #4 */

// Stack DS implemented using a linked list
template <class t>
struct Stack {
  Node<t>* head;
  int size;
  
  Stack(): head(nullptr), size(0) {}
  ~Stack();

  void push(t value);
  t pop();
  t peek();
};

// Stack destructor
template <class t>
Stack<t>::~Stack() {
  delete head;
}

// Pushes a value onto the stack
template <class t>
void Stack<t>::push(t value) {
  insert_by_ref(this->head, value);
  size++;
}

// Retrieves the value at the top of the stack and removes it
template <class t>
t Stack<t>::pop() {
  if (!this->head) {
    // If head is null, return the default value for type t
    return t{};
  }
  // Get value from head
  t value = this->head->data;

  // Make copy of head pointer
  auto tmp = this->head;
  
  if (tmp->next) {
    // Set head to head->next
    this->head = tmp->next;
    // Clear next pointer of tmp
    tmp->next = nullptr;
  } else {
    this->head = nullptr;
  }

  delete tmp;

  return value;
}

// Retrieves the value at the top of the stack and leaving it in place
template <class t>
t Stack<t>::peek() {
  if (!this->head) {
    // If head is null, return the default value for type t
    return t();
  }
  // Get value from head
  t value = this->head->data;

  return value;
}

/* Main ------------------------------------------------------------------------------ */

int main() {
  // Create an array containing some duplicated values
  std::vector<int> array({0, 3, 12, 8, 8, 0, 1, 14, 12, 8});
  std::printf("array   : ");

  std::printf("[");
  for ( int value: array ) {
    std::printf("%d, ", value);
  }
  std::printf("]\n");

  // Get the unique values of the array
  auto unique = unique_values(array);
  // Get the unique values and their counts from the array
  auto counts = count_values(array);
  // Get the values greater than 5 from array
  auto gt_5   = values_gt(array, 5);

  // Print lists to the terminal
  std::printf("\nquestion 1: \n");
  std::printf("\tunique  : ");
  debug(unique);
  
  std::printf("\nquestion 2: \n");
  std::printf("\tcounts  : ");
  debug(counts);
  
  std::printf("\nquestion 3: \n");
  std::printf("\tvals > 5: ");
  debug(gt_5);

  // Free memory
  delete unique;
  delete counts;
  delete gt_5;

  // Create stack and push values to it
  Stack<int> stack;
  stack.push(12);
  stack.push(22);
  stack.push(38);
  stack.push(8);
  stack.push(37);

  // Print stack
  std::printf("\nquestion 4: \n");
  std::printf("\tstack    : ");
  debug(stack.head);
  // Pop and print new stack
  std::printf("\tpop: %d\n", stack.pop());
  std::printf("\tnew stack: ");
  debug(stack.head);
  // Peek and print new array
  std::printf("\tpeek: %d\n", stack.peek());
  std::printf("\tnew stack: ");
  debug(stack.head);
  // Pop and print new array
  std::printf("\tpop: %d\n", stack.pop());
  std::printf("\tnew stack: ");
  debug(stack.head);
  // Pop and print new array
  std::printf("\tpop: %d\n", stack.pop());
  std::printf("\tnew stack: ");
  debug(stack.head);
  // Pop and print new array
  std::printf("\tpop: %d\n", stack.pop());
  std::printf("\tnew stack: ");
  debug(stack.head);
  // Pop and print new array, array should be empty
  std::printf("\tpop: %d\n", stack.pop());
  std::printf("\tnew stack: ");
  debug(stack.head);
  // Pop and print new array, should return the default value of int: 0
  std::printf("\tpop: %d\n", stack.pop());
  std::printf("\tnew stack: ");
  debug(stack.head);
}
