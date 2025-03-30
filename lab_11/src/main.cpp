/* Devon Webb */
/* CSCI 41 Lab Section 06 */
/* Lab 11 */

#include <cstdio>
#include <cmath>
#include <string>

using namespace std;

struct BSTNode {
    int key;
    BSTNode* left;
    BSTNode* right;

    BSTNode(): key(0), left(NULL), right(NULL) {}
    BSTNode(int k): key(k), left(NULL), right(NULL) {}
    ~BSTNode() {}

    bool isLeaf(BSTNode* node);
    int numChildren(BSTNode* node);
    BSTNode* parent(BSTNode* root, BSTNode* child);
    void InsertNodeREC(BSTNode* root, int data); // Recursive version 
    void InsertNodeITE(BSTNode* root, int data); // Iterative version
    bool SearchNodeREC(BSTNode* root, int data); // Recursive version
    bool SearchNodeITE(BSTNode* root, int data); // Iterative version     
    void display(BSTNode* root, string name);
};

bool BSTNode::isLeaf(BSTNode* node) {
    return (node->left == NULL && node->right == NULL)? true: false;
}

int BSTNode::numChildren(BSTNode *node) {
    int count = 0;

    if(node->right != NULL) count++;
    if(node->left != NULL) count ++;

    return count;
}

BSTNode* BSTNode::parent(BSTNode* root, BSTNode* child) {
    BSTNode* current = root;

    while(current->left != child && current->right != child && current != NULL) {
        if(child->key > current->key) {
            current = current->right;
        } else {
            current = current->left;
        }
    }

    return current;
}

void BSTNode::InsertNodeITE(BSTNode* root, int data) {
    if(root == NULL) return;

    if(root->key == 0) {
        root->key = data;
        return;
    }

    BSTNode* current = root;

    while(current != NULL) {
        if(data > current->key) {
            if(current->right == NULL) {
                current->right = new BSTNode(data);
                return;
            }
            current = current->right;
        } else {
            if(current->left == NULL) {
                current->left = new BSTNode(data);
                return;
            }
            current = current->left;
        }
    }
}

void BSTNode::InsertNodeREC(BSTNode* root, int data) {
    if(root == NULL) return;

    if(root->key == 0) {
        root->key = data;
        return;
    }

    if(data > root->key) {
        if(root->right == NULL) {
            root->right = new BSTNode(data);
            return;
        }
        InsertNodeREC(root->right, data);
    } else {
        if(root->left == NULL) {
            root->left = new BSTNode(data);
            return;
        }
        InsertNodeREC(root->left, data);
    }
}

bool BSTNode::SearchNodeITE(BSTNode *root, int data) {
    if(root == NULL) return false;

    BSTNode* current = root;

    while(current != NULL && current->key != data) {
        if(data > current->key) {
            current = current->right;
        } else {
            current = current->left;
        }
    }

    if(current != NULL && current->key == data) return true;

    return false;
}

bool BSTNode::SearchNodeREC(BSTNode *root, int data) {
    bool found = false;

    if(root == NULL) return false;
    if(root->key == data) return true;

    if(data > root->key) {
        found = SearchNodeREC(root->right, data);
    } else {
        found = SearchNodeREC(root->left, data);
    }

    return found;
}

void print(string prefix, BSTNode* root, bool isRight) {
    if(root != NULL) {
        // print current node
        printf("%s", prefix.c_str());
        printf("%s", isRight? "├──": "└──");
        printf("%d\n", root->key);
        // print next tree level
        print(prefix + (isRight? "│   ": "    "), root->right, true);
        print(prefix + (isRight? "│   ": "    "), root->left, false);
    }
}

void BSTNode::display(BSTNode* root, string name) {
    printf("%s:\n", name.c_str());
    print("", root, false);    
}

int main() {
    BSTNode* bst1 = new BSTNode(6);
    bst1->InsertNodeITE(bst1, 9);
    bst1->InsertNodeITE(bst1, 15);
    bst1->InsertNodeITE(bst1, 21);
    bst1->InsertNodeITE(bst1, 4);
    bst1->InsertNodeITE(bst1, 8);
    bst1->InsertNodeITE(bst1, 12);
    bst1->InsertNodeITE(bst1, 7);
    bst1->InsertNodeITE(bst1, 1);
    bst1->InsertNodeITE(bst1, 5);
    bst1->display(bst1, "BST1, using iterative inserting and overload constructor");
    
    delete bst1;

    BSTNode* bst2 = new BSTNode();
    bst2->InsertNodeREC(bst2, 6);
    bst2->InsertNodeREC(bst2, 9);
    bst2->InsertNodeREC(bst2, 15);
    bst2->InsertNodeREC(bst2, 21);
    bst2->InsertNodeREC(bst2, 4);
    bst2->InsertNodeREC(bst2, 8);
    bst2->InsertNodeREC(bst2, 12);
    bst2->InsertNodeREC(bst2, 7);
    bst2->InsertNodeREC(bst2, 1);
    bst2->InsertNodeREC(bst2, 5);
    bst2->display(bst2, "BST2, using recursive insertion and default constructor");

    printf("BST2 contains 12: %s. ITE\n", bst2->SearchNodeITE(bst2, 12)? "true": "false");
    printf("BST2 contains 13: %s. ITE\n", bst2->SearchNodeITE(bst2, 13)? "true": "false");
    printf("BST2 contains 12: %s. REC\n", bst2->SearchNodeREC(bst2, 12)? "true": "false");
    printf("BST2 contains 13: %s. REC\n", bst2->SearchNodeREC(bst2, 13)? "true": "false");

    BSTNode* child = bst2->right->right->left;
    BSTNode* parent = bst2->parent(bst2, child);
    int num_child = bst2->numChildren(parent);

    printf("Parent of Node %d is %d, which has %d children\n", child->key, parent->key, num_child);

    delete bst2;

    return 0;
}
