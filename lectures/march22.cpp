// March 22, 
// 
// Project:
//   menu in while loop:
//
//   1) add student
//   2) remove student
//   3) edit student
//   4) display students
//   5) exit
//
//  cls, clear to clear menu
//
//   student stuct/class:
//     name:
//     id:
//     ...
//
//   using doublely linked list, last->next = first, first->prev = last, ordered by a attribute(this would be called the primary key,
//                                                                                              id is good choice as cannot have duplicates)
//   show one record at a time, can switch to prev or next record with p/n, m to go back to menu
//
//  Linked list cont.:
//
//    single circular lists:
//      last node points to first node
//      while(current->next != nullptr) no longer works 
//        can use while(current->next != head)
//      node can have a flag variable to signify if it is the head or not
//
//  pointers are 8bits/1byte
//  array is a pointer
//
//
//  New data structure: HEAP
//    binary heap:
//      uses binary tree
//      shape:
//        full binary tree(all leaves at the same level are filled)
//        complete binary tree(some leaves are missing but all missing node are clustered on the left, no gaps)
//      heap:
//        max heap(each node is greater or equal to each of its children)(head is greatest value)
//        min heap(each node is smaller or equal to each of its children)(head is smallest value)
//
//  Binary tree summary:
//    two pointers, left and right
//    != binary search tree
//    height of complete tree with N nodes is floor(logn)
//    height only increases when n is a power of 2
//    balanced tree is symmetric
//    complete tree, no gaps execpt on the right side of the lowest level
//    number of nodes is 2^(height) - 1   
//    will go into detail after spring break
//
//    Binary heap:
//      Max heap:
//          Top node has maximum value
//      Min heap:
//          Top node has minimum value
//      
//  Array representation of heap:
//      read each node from left to right top to bottom
//       1
//     2   3
//    4 5 6 7
//
//      if current node is at pos(index starting at one) i, then left child will be at 2i, and the right child will be at 2i+1, must be a complete binary tree
//      position of parent will be floor(i/2)
//      a heap with n elements will have height floor(logn)
//      a heap with height k will have between 2^k(min) and 2^(k+1) - 1(max) elements
//      could leave blanks in array
//
//      max heap insertion complexity O(1) <-> O(logn)
//          add to empty space in array, check if greater than parent, then swap with parent if neccisary, repeat until in right place
//          time taken is equal to the number of swaps
//          
//      max heap deletion complexity O(logn)
//          delete root element (the top element)
//              swap first element with the last element of the array (ignore final element as it is "deleted")
//          compare parent with its children and swap accordingly so max is the parent
//
//      heapsort(nlogn):
//          if you continuly delete root until min is in root, you get a sorted array
//          data must be in a certain order for this to work (heap tree structure)
//          
//
//      hashtable:
//          introduction to searching algorithms:
//              linear search O(n)
//                  check each element in a row
//              binary search O(logn)
//                  uses sorted arrays
//                  divide array in half each time
//          hashing:
//             uses key-value pairs to order or store elements  
//             can place elements in the element that it's index equals it value, for strings can add their chars up to a single int
//             search complexity O(1)
//             
//             for example:
//                  arr[10];
//                  index = key % 10;
//                  if two values have the same index = collision
//
//                  can have a array of linked lists so multiple values can have same value
//                  or can jump until a free space is found
//
//              solutions for collision:
//                  Open hashing:
//                      Chaining: using linked lists to allow multiple values in the same spot
//                      to search for 10, go to arr[10 % 10], check each in the list until it is found
//                      O(m) where n >= m > 0
//
//
//                  Closed hashing:
//                      linear probing:
//                          if collision, move collision to the next available place
//                          a hash function: 
//                             index:  h'(x) = [h(x) + f(i)] % n
//                              f(i) = i
//                              h(x) = x
//
//                              h'(10) = [h(10) + 0] % 10 -> 0
//                              if (collision) i++;
//                              h'(10) = [h(10) + 1] % 10 -> 1
//
//                              mathmatical way of saying if there is a collison, move to the next spot
//                              doesn't distribute values in a array efficiently, data clusters and leaves gaps
//                      quadratic probing:
//                          h'(x) = [h(x) + f(i^2)] % n
//                          f(i) = i
//                          h(x) = x
//
//                          if (collison) i++;
//                          go until i = n?
//
//                          solves clustering issues, has less empty spaces when their are many collisions
//
//
//                      
