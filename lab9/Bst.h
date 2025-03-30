/*
 *  CSCI 115 - 03
 *  Lab 9
 *
 *  Devon Webb
 */

#include <string>
#include <tuple>
#include <iostream>

namespace Bst {
  template <class t>
  struct Node {
    t data;
    Node* left{nullptr}; 
    Node* right{nullptr};
    Node* parent{nullptr};

    Node(const t& data) : data(data), left(nullptr), right(nullptr), parent(nullptr) {}
    ~Node();
  };

  template <class t>
  Node<t>::~Node() {
    delete left;
    left = nullptr;

    delete right;
    right = nullptr;
  }
  
  // Return a tuple of {min, max, predecessor, successor}.
  // Returns -1 for predecessor and successor if those nodes are nullptr
  inline std::tuple<int, int, int, int> values(Node<int>* root) {
    int min{-1}, max{-1}, pred{-1}, succ{-1};

    // Find minimum value 
    for (auto current = root; current; current = current->left) {
      if (!current->left) {
        min = current->data;
      }
    }

    // Find maximum value 
    for (auto current = root; current; current = current->right) {
      if (!current->right) {
        max = current->data;
      }
    }
    
    // Check for predecessor
    if (root->left) {
      pred = root->left->data;
    }

    // Check for successor
    if (root->right) {
      succ = root->right->data;
    }
    
    return {min, max, pred, succ};
  }

  // Inserts a new node into the tree, using the value provided
  template <class t>
  void insert(Node<t>* root, const t& value) {
    Node<t>* current = root;

    if (current) {
      if (value >= current->data) {
        // If current->right exists, move right recursively, else create new node at ->right
        if (current->right) {
          insert(current->right, value);
        } else {
          current->right = new Node<t>(value);
        }
      } else if (value < current->data) {
        // If current->left exists, move left recursively, else create new node at ->left
        if (current->left) {
          insert(current->left, value);
        } else {
          current->left = new Node<t>(value);
        }
      }
    }
  }
  
  // Find the node with the min value in subtree
  template <class t>
  Node<t>* find_min(Node<t>* root) {
    if (!root) {
      return nullptr;
    }

    // Keep going left, as long as left exists to find min
    if (root->left) {
      return find_min(root->left);
    }

    return root;
  }

  // Deletes the node containing the value provided, if found
  template <class t>
  Node<t>* delete_rec(Node<t>* root, const t& value) {
    if (!root) {
      return nullptr;
    }

    if (value < root->data) {
      root->left = delete_rec(root->left, value);
    } else if (value > root->data) {
      root->right = delete_rec(root->right, value);
    } else {
      // No children
      if (!root->left && !root->right) {
        delete root;
        root = nullptr;
      // Just right child
      } else if (root->right) {
        Node<t>* tmp = root;
        root = root->right;
        delete tmp;
      // Just left child
      } else if (root->left) {
        Node<t>* tmp = root;
        root = root->left;
        delete tmp;
      // Both children
      } else {
        Node<t>* tmp = find_min(root->right);
        root->data = tmp->data;
        root->right = delete_rec(root->right, tmp->data);
      }
    }

    return root;
  }

  // Returns true if tree passed in is a BST
  template <class t>
  bool is_bst(Node<t>* root, int min, int max) {
    if (!root) {
      return true;
    }

    // If data is not within min..max, return false
    if (root->data < min || root->data > max) {
      return false;
    }
    
    // Check that left and right nodes are within min..max
    return (
         is_bst(root->left, min, root->data)
      && is_bst(root->right, root->data + 1, max)
    );
  }

  // Traverses the tree level by level
  template <class t>
  void print_level(Node<t>* root, int level) {
    if (root) {
      if (level == 0) {
        std::cout << " - " << root->data << " - ";
      } else {
        print_level(root->left, level - 1);
        print_level(root->right, level - 1);
      }
    }
  }

  // Performs a left rotation around root
  template <class t>
  Node<t>* rotate_left(Node<t>* root) {
    if (root != nullptr) {
      Node<t>* b = root->right;
      b->parent = root->parent;
      root->right = b->left;

      if (root->right != nullptr) {
        root->right->parent = root;
      }

      b->left = root;
      root->parent = b;

      if (b->parent != nullptr) {
        if (b->parent->right == root) {
          b->parent->right = b;
        } else {
          b->parent->left = b;
        }
      }
      return b;
    } else {
      return nullptr;
    }
  }

  // Performs a right rotation around root
  template <class t>
  Node<t>* rotate_right(Node<t>* root) {
    if (root != nullptr) {
      Node<t>* b = root->left;
      b->parent = root->parent;
      root->left = b->right;

      if (root->left != nullptr) {
        root->left->parent = root;
      }

      b->right = root;
      root->parent = b;

      if (b->parent != nullptr) {
        if (b->parent->right == root) {
          b->parent->right = b;
        } else {
          b->parent->left = b;
        }
      }
      return b;
    } else {
      return nullptr;
    }
  }

  // Pretty prints the tree to the terminal
  template <class t>
  void debug(Node<t>* root, std::string prefix = "", bool is_right = false) {
    if (root) {
        std::cout << prefix;

        std::cout << (is_right ? "├──" : "└──");

        std::cout << root->data << std::endl;

        debug(root->right, prefix + (is_right ? "│   " : "    "), true);
        debug(root->left, prefix + (is_right ? "│   " : "    "), false);
    }

  }
}
