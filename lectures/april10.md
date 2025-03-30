# April 10th, 2023 CSCI 41

## Midterm 2
Starts at heap.

## Quiz 3
Sorting. (logn): (merge/quick/heap)
Hash.
Tree.
Linked List. CLL SLL DLL.
Heap.

## Heap
Heap is a "tree" stored in an array, or a tree.

### Recap
Complexity of search on unsorted array using linear search O(n).
Complexity of search on sorted array using binary search O(log2(n)). log2 is because of dividing by 2, if by 4 it would be log4.
    -Data has to be sorted.
Sorting algorithms:
    -bubble O(n2)
    -insertion O(n2)
    -selection O(n2)
    -merge O(nlogn)
    -quick O(nlogn)
    -heap O(nlogn)

Hashtable:
    -value-key pair
    -search complexity best case(1) O(m) where m < n
    -open hash (collisions stored in lists)
    -closed hash (collisions stored in free spaces based on some algorithm)
        -(f(x) + h(i)) % n
        -(f(x) + h(i^2)) % n
## Binary Trees
Has nodes with left and right nodes, and data.

```cpp
struct TNode { // Parent
        T data;
        TNode* left; // Child
        TNode* right; // Child
    }
```

Traversing a tree:
    -visiting all nodes.
Depth of a node:
    -The number of edges from the root/head to the node.
Height of a node:
    -The number of edges from the node to the deepest branch.
Levels:
    -The level of a particular node refers to how many generations the node is from the root.
Keys:
    -One data structure in an object is usually designated a key value.
    -This key is used to search for the item
Size of tree: (n)
    -Number of nodes in the tree.

### Tree topology 
Typically there is one node in the top row of a tree. (root).

## Binary search tree
A node's left child has a key less than its parent.
A node's right child has a key greater than or equivalent to its parent (left node?).

Trees are good for searching, like binary search without need for sorting. O(logn)

### Unbalanced trees
Have most nodes on one side of the root.
They become unbalanced because of the order of the data items are inserted.

### Complete binary trees
All nodes in the last level must be complete.

Important for heap. No gaps from left to right.

### Full Binary trees
Each node has either 0 or 2 children.

### Perfect binary tree
All interior nodes have 2 children, and all leaves are at the same height.

Number nodes at depth d = 2^d.
A perfect binary tree of height h has: 2^(h+1) - 1 nodes.
Number of leaf (last, bottom) nodes in a perfect binary tree of height h = 2^h.
Number of internal (in between leafs and root) nodes with height h: 2^h -1.

Can count nodes using recursion:

```cpp
int countNodes(Node* root) {
    if (root == nullptr) {
        return 0;
    } else {
        int count = 1;
        count += countNodes(root->left);
        count += countNodes(root->right);

        return count;
    }
}
```

## Tree nodes
Contain node pointers, data, and a key.

### Finding a node
```cpp
bool treeContainsNR(Node* root, item) {
    Node* runner;
    runner = root;
    while(true) {
        if (runner == NULL) {
            return false;
        } else if (item == runner->item) {
            return true;
        } else if (item < runner->item) {
            runner = runner->left;
        } else {
            runner = runner->right;
        }
    }
}
```

### Inserting a node
1) root.
2) leaf.
3) middle.

Find the node in the tree it should be after.
Place it as the left or right node depending on the type of tree.

## Traversing a tree
Visiting every node in a specified order.
Used to print out each node, or apply some function to each node.
Not particularly fast.

### In-order Tree Traversal
Nodes are visited in ascending order.
Easiest way to traverse a tree is with recursion.
Gives the list in a sorted order.
Go all the way left, then go right one, then all the way left again recursively.

Keep going left until there is no more left nodes, then print it, go right until a left node is found again or both right and left are NULL.
Once the right most node is found, that section of the tree is done.

left parent right
print left print parent print right

Can sort in O(n)

# April 14

## Project 2
Data in an array. 1E6 elements, with random data. Sort with three sorting algorithms. Time it. Display first hundred.
Another array with first 5E5 is sorted, sort with four sorting algorithms (two of heap, merge, quick, and two n^2).
See which sorts faster.
Then use tree and implement heap sort.


```cpp
#include <time.h>

clock_t starttime;
clock_t endtime;

int main() {
    starttime = clock();

    //sort

    endtime = clock();

    cout << endtime - starttime;
    cout << "\d"; //?? to display in a table
}
```

## Traversing a binary tree

### Pre-Order Traversal
Parent first, then left, then right child.

### Traversal
        *
    A       +
          B   C
*A+BC: pre-order, parent left right
A*+BC: in order, left parent right
ABC+*: post-order, left right parent

```cpp
void preorderPrint(TreeNode* root) {
    if (root != NULL) {
        cout << root->item << " ";
        preorderPrint(root->left);
        preorderPrint(root->right);
    }
}
void inorderPrint(TreeNode* root) {
    if (root != NULL) {
        inorderPrint(root->left);
        cout << root->item << " ";
        inorderPrint(root->right);
    }
}
void postorderPrint(TreeNode* root) {
    if (root != NULL) {
        postdorderPrint(root->left);
        postorderPrint(root->right);
        cout << root->item << " ";
    }
}
```

# April 19th

## Quiz up to basic pieces of trees (insertion)

## Tree
### Inverting a tree
Mirroring a tree so greater values are on left instead of on the right.
Swap the children of each node recursively.

```cpp
auto left = invert(node->left);
auto right = invert(node->right);
swap(node->left, node->right);
```

### Max Depth of a Binary tree
Depth from current node to the lowest leaf.
```cpp
int MaxDepth(TreeNode* root) {
    if (root == NULL) {
        return 0;
    } else {
        return 1 + max(MaxDepth(root->left), MaxDepth(root->right));
    }
}
```
### Min Depth of a Binary tree
Depth from current node to find null leaf
```cpp
int MinDepth(TreeNode* root) {
    if (!root) {
        return 0;        
    }
}
```

### Comparison of trees
If all nodes are equal, return true;

```cpp
return ( (a->data == b->data) && (SameTrees(a->left, b->left)) && (SameTrees(a->right, b->right)) );
```

### Checking if a tree is a binary search tree

### Searching a tree (logn)
each level takes the level # * number of nodes to find all nodes in that level

level 1 = 1 * 1 = 1
level 2 = 2 * 2 = 4
level 3 = 3 * 4 = 12
level 4 = 4 * 8 = 32

29/10 = 2.9 comparisons per search average
55/10 = 5.5 for array

takes half as many comparisons as needed to search an array

tree has high space complexity

# Monday April 24th

## AVL Trees
balanced BST?
10 20 30 

10-20-30 20-10-30 10-30-20 20-30-10 30-20-10 30-10-20 

as binary search trees:
10
  20
    30
left rotation: to create balanced trees
  20
10 30

only rotate the violated component and the tree nodes connected to it

### Left rotation

        10
      br   20
          br  30
            br

            20
        10        30
      br   br   br
            |
            br was connected to 20, it is greater than 10 and less than 20

# Exam 2 tues
Won't cover AVL trees
Up to bst traversal

## AVL trees

Insert into tree, then check if balanced, if it is not, do rotations at the node above the one you added.
To see if a tree is balanced, check is height left - right height = {1, 0, -1}

```cpp
template<class T>
struct AVLNode {
    T key;
    int balance;
    AVLNode* left, * right, * parent;

    AVLNode(T k, AVLNode* p): key(k), balance(0), parent(p), left(nullptr), right(nullptr) {}

    ~AVLNode() {
        delete left;
        delete right;
        delete parent;
    }
}

template<class T>
int AVLtree<T>::height(AVLNode<T>* n) {
    if (n == nullptr) {
        return -1;
    } else {
        return 1 + std::max(height(n->left), height(n->right));
    }
}

template<class T>
void AVLtree<T>::setBalance(AVLNode<T>* n) {
    n->balance = height(n->right) - height(n->left);
}

template<class T>
AVLNode<T>* AVLtree<T>::rotateLeft(AVLNode<T>* a) {
    AVLNode<T>* b = a->right;
    b->parent = a->parent;
    a->right = b->left;

    if(a->right) {
        a->right->parent = a;
    }

    b->left = a;
    a->parent = b;

    if(b->parent) {
        if(b->parent->right == a) {
            b->parent->right = b;
        } else {
            b->parent->left = b;
        }
    }

    setBalance(a);
    setBalance(b);
    return b;
}

template<class T>
AVLNode<T>* AVLtree<T>::rotateRight(AVLNode<T>* a) {
    AVLNode<T>* b = a->left;
    b->parent = a->parent;
    a->left = b->right;

    if(a->left) {
        a->left->parent = a;
    }

    b->right = a;
    a->parent = b;

    if(b->parent) {
        if(b->parent->right == a) {
            b->parent->right = b;
        } else {
            b->parent->left = b;
        }
    }

    setBalance(a);
    setBalance(b);
    return b;
}

template<class T> 
AVLNode<T>* AVLtree<T>::rotateLeftThenRight(AVLNode<T>* n) {
        n->left = rotateLeft(n->left);
        return rotateRight(n);
    }


template<class T> 
AVLNode<T>* AVLtree<T>::rotateRightThenLeft(AVLNode<T>* n) {
        n->right = rotateRight(n->right);
        return rotateLeft(n);
    }
```

## Balance condition violation

If condition violated after a node insertion:
-
-

## Rebalancing a tree

```cpp
template<class T>
void AVLtree<T>::rebalance(AVLNode<T>* n) {
    setBalance(n);

    if(n->balance = 2) {
        if(height(n->left->left) >= height(n->left->right)) {
            n = rotateRight(n);
        } else {
            n =
        }
    }
}
```

## AVL Tree Complexity
High space complexity
Worst case O(logn) for insert, delete, search

# May 1

## Quadtree
- each node has exactly 4 children
- used to efficiently store data of points on a 2d space

## Octtree
- 3d version of a quadtree
- each node has exactly 8 children

# May 3

## Trie tree

```cpp
struct Node {
    char ch;
    Node* children[];
    bool isWord;
}
```

Car
Done
Try
Trie
Cat
Do

root = Node* []
        [  c       d ]
         a            o 
      r     t     true  n
     true true           e
                       true
## Radix tree
used for autocomplete, root is what you types, branching nodes are the character/s with add on to what you wrote
uses strings instead of char

## Graphs

Graph G = (V, E)
    vertices and edges

```
After inserting keys 5, 6, 8, 10, 20 in a BST in the same order,
Find the depth of the node with key 10

3
```

```
After inserting keys 5, 6, 8, 10, 20, 30, 40 in BST in same order,
FInd the height of the bst

6
```

```
After inserting keys 5, 6, 8, 10, 20, 30, 40 in BST in same order,
Find height of node with key 20

3
```

```
After inserting keys 5, 6, 8, 10, 20, 30, 40, 100 in BST in same order,
Find the size of the tree

8
```

```
Given 20, 30, 33, 35, 39, 40, 50, 60, 100
What order would construct a Full Binary Tree

40, 30, 60, 20, 35, 50, 100, 33, 38
```

```
Given 20, 30, 35, 39, 40, 60, 100
What order of key insertion would construct a complete binary tree

39, 30, 60, 20, 35, 40, 100
```

```
4, 2, 6, 1, 3 ,5 ,15, 7, 16 inserted into empty AVL tree
Find resulting avl after inserting 12 followed by rotations

4, 2, 7, 1, 3, 6, 15, --, --, --, --, 5, 12, 16
```

```
True statements for a perfect binary tree

number of leaf nodes at height 5 is 32
number of internal nodes with height 5 is 31
number of nodes at septh of 5 is 32
```

```
Worst case time complexity for search, insert and delete in general BST

O(logn)
```

```
Which of the following traversal outputs the data in sorted order in a BST

inorder
```

```
13, 11, 7, 14, 9, 12, 6, 15, 10, 8 inserted into initially empty BST
What is the inorder traversal

6, 7, 8, 9, 10, 11, 12, 13, 14, 15
```

```
Preorder trav of BST is 30, 20, 10, 15, 25, 23, 39, 35, 42
Which is the postorder

15, 10, 23, 25, 20, 35, 42, 39, 30
```

```
void travel(node, k)
    if root !null and count <= k
travel(root->right, k)
    count++
    if count == k
    print root->data
travel(root->left, k)

prints the kth largetst element in bst
```

```
[1..=100] bst
search for 55, which cannot be the sequence of nodes examined

9, 85, 47, 68, 43, 57, 55
```

```
24
12       26
11    16
13

if we remove the root node, which node from the left subtree will be the new root

16
```

```
preorder = 15, 10, 12, 11, 20, 17, 19
find post order

11, 12, 10, 16, 19, 18, 20, 15
```

```
5
3               10
2   4       7       11
1           6   9       12
8
Find balance factors of 2, 4, 7, 5

-1, 0, 1, 1
```

```
int avl(root)
    if !root
    reutrn 0
left-HEIGHT = avl(root.left)

if left-height = -1
return left-height

right-height = avl)root.right)

if right-height = -1
return right-height

check validity of avl tree
```

```
double rotation
RL
LR
```

```
find # rot to insert 9, 6, 5, 8, 7, 10 to AVLtree

3
```

```
worst case selection sort

o(n2)
```

```
in merge sort, how combine two sorted arrays

use an auxilary array
```

```
auxilery space comlpexity of merge sort

o(n)
```

```
which methhod is used for merge sort

merging
```

```
correct code for merge sort

merge_sort(arr[], int left, int right)
    if(left < right) 
        int mid = left + (right-left)/2
        merge_sort(arr, left, mid)
        merge_sort(arr, mid+1, right)
        merge(arr, left, mid, right)
```

```
quick sort uses partitioning
```

```
apply quicksort on 6, 10, 13, 5, 8, 4, 3 ,12, pivot first element
what is seq after first phase

5, 3, 4, 6, 8, 13, 10, 12
```

```
binary search works when array is sorted accending or descending
```

```
max comparisons needed in binary search for [i32; 64]
6
```

```
best case time of binary search

omega(1)
```

```
in selection sort, there are two loops one nested in the other
```

```
what are the intermediate steps of the following sort with insertion
15, 20, 10, 18

15, 20, 10, 18 - 10, 15, 20, 18 - 10, 15, 18, 20 - 10, 15, 18, 20
```

```
[1 3 4 8 9 || 5 2] insertion sort
how many comp and swaps needed to sort next number

3 comp, 2 swaps
```

```
which of the following is not an application of priority queue

undo operation
first come first serve line
```

```
node p
p = front
while p.next != null
    cout data 
    p = p.next

traverse linked list and print data
```

```
node p1 p2
p1 = front1
p2 = front2

while p1.next != null
    p1 = p1.next
p1.next = p2

combining two linked lists
```

```
which of the following is true about binary trees

height of complete witn N nodes is floor(logN)
height of binary tree is max number of edges in any root to leaf path
```

```
node p
while front != null
    p = front
    front = front.next
    delete p

remove nodes from the front repeatedly
```

```
let h'(x) = [h(x)+f(i2)] % n where i = 0, 1, 2, 3, 4, ...

insert 7, 2, 17, 65, 40 into hash of size 5

65 17 7 2 40
```

```
        100
    19      36
  17  3   25   1
 2  7

insert 15, what are leaf nodes of right half

15, 1
```

```
which array represents the max heap

10 8 6 4 5 1 2 -- --
```

```
32, 15, 20, 30, 12, 25, 16 inserted into max heap

32 30 25 15 12 20 16
```

```
location of parent node

floor(i/2)
```

```
in max heap, greatest key is stored in root node
```

```
time taken to delete min of min heap is O(logN)
```

```
which are true

hash func takes message of arb length and generates a fixed length code
if x.equals(y) and y.equals(z), then x.equals(z)
a hash func may give the same hash val for distinct messages
```

```
can you store a duplicate key in hashtable

strictly no
cannot retrieve data after store values
```

```
10 1 3 5 15 12 16 inserted int BST
what height

3
```

```
height of binary tree is max num edges in any root->leaf path
max num of nodes in binary tree of height h is 2^(h+1)-1
```

```
which is true bout binary trees

constructing binary tree with sorted keys give shape of linked list
max number of binary trees that can be formed with three unlabeled nodes is 5
```

```
close hashing technique used to prevent data clustering

quadratic probing
```

```
20, 30, 35, 39, 40, 60, 100
what order insertion will construct complete binary tree

39, 30, 60, 20, 35, 40, 100
```
