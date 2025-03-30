/* Devon Webb */
/* CSCI 41 Lab Section 06 */
/* Lab 12 */

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
    void InsertNodeITE(BSTNode* root, int data); // Iterative version
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

struct MyBST {
    BSTNode* root;

    MyBST(): root(new BSTNode()) {}
    ~MyBST() {}

    void InsertNode(BSTNode* root, int data);
    bool SearchNode(BSTNode* root, int data);
    void DeleteNode2(BSTNode* root, int data);
    void DeleteNode3(BSTNode* &root, int data);
    BSTNode* DeleteNode1(BSTNode* root, int data);

    void display(string name);
};

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
void MyBST::display(string name) {
    printf("%s:\n", name.c_str());
    print("", this->root, false);    
}

void MyBST::InsertNode(BSTNode* root, int data) {
    if(root == nullptr) {
        this->root = new BSTNode(data);
        return;
    }

    root->InsertNodeITE(root, data);
}

bool MyBST::SearchNode(BSTNode* root, int data) {
    if(root == nullptr) return false;

    return root->SearchNodeITE(root, data);
}

BSTNode* MyBST::DeleteNode1(BSTNode* root, int data) {
    if(root == nullptr) return root;

    if(data < root->key) {
        root->left = DeleteNode1(root->left, data);
    } else if(data > root->key) {
        root->right = DeleteNode1(root->right, data);
    } else {
        if(root->numChildren(root) == 0) {
            delete root;
            root = nullptr;
            return root;
        } else if(root->left == nullptr) {
            BSTNode* temp = root->right;
            delete root;
            return temp;
        } else if(root->right == nullptr) {
            BSTNode* temp = root->left;
            delete root;
            return temp;
        }

        BSTNode* temp = root->right;
        while(temp->left != nullptr) {
            temp = temp->left;
        }

        root->key = temp->key;
        root->right = DeleteNode1(root->right, temp->key);
    }

    return root;    
}

void MyBST::DeleteNode2(BSTNode* root, int data) {
    if(root == nullptr) return;

    BSTNode* current = root;

    while(current != nullptr && current->key != data) {
        if(data < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == nullptr) return;

    if (current->isLeaf(current)) {
        BSTNode* temp = current->parent(root, current);
        if(temp->left == current) {
            delete current;
            temp->left = nullptr;
        } else {
            delete current;
            temp->right = nullptr;
        }
    } else if (current->left == nullptr) {
        BSTNode* parent = current->parent(root, current);
        BSTNode* temp = current->right;
        if(parent->left == current) {
            parent->left = temp;
        } else {
            parent->right = temp;
        }
        delete current;
    } else if (current->right == nullptr) {
        BSTNode* parent = current->parent(root, current);
        BSTNode* temp = current->left;
        if(parent->left == current) {
            parent->left = temp;
        } else {
            parent->right = temp;
        }
        delete current;
    } else {

    }
}

void MyBST::DeleteNode3(BSTNode* &root, int data) {
    if(root == nullptr) return;

    BSTNode* current = root;

    while(current != nullptr && current->key != data) {
        if(data < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == nullptr) return;

    if (current->isLeaf(current)) {
        BSTNode* temp = current->parent(root, current);
        if(temp->left == current) {
            delete current;
            temp->left = nullptr;
        } else {
            delete current;
            temp->right = nullptr;
        }
    } else if (current->left == nullptr) {
        BSTNode* parent = current->parent(root, current);
        BSTNode* temp = current->right;
        if(parent->left == current) {
            parent->left = temp;
        } else {
            parent->right = temp;
        }
        delete current;
    } else if (current->right == nullptr) {
        BSTNode* parent = current->parent(root, current);
        BSTNode* temp = current->left;
        if(parent->left == current) {
            parent->left = temp;
        } else {
            parent->right = temp;
        }
        delete current;
    } else {
    
    }
}

int main() {
    MyBST* mbst = new MyBST();
    mbst->InsertNode(mbst->root, 6);
    mbst->InsertNode(mbst->root, 9);
    mbst->InsertNode(mbst->root, 15);
    mbst->InsertNode(mbst->root, 21);
    mbst->InsertNode(mbst->root, 4);
    mbst->InsertNode(mbst->root, 8);
    mbst->InsertNode(mbst->root, 12);
    mbst->InsertNode(mbst->root, 7);
    mbst->InsertNode(mbst->root, 1);
    mbst->InsertNode(mbst->root, 5);
    mbst->display("MyBST");

    mbst->DeleteNode1(mbst->root, 9);
    mbst->display("MyBST after delete of node 9 with two child");

    mbst->DeleteNode2(mbst->root, 8);
    mbst->display("MyBST after delete of node 8 with one children");

    mbst->DeleteNode3(mbst->root, 7);
    mbst->display("MyBST after delete of node 7 with no children");

    delete mbst;

    return 0;
}