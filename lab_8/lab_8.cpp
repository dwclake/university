// Devon Webb
// CSCI41 Lab 06

#include <iostream>
#include <iomanip>

using namespace std;

class NodeSC {
    public:
        NodeSC(): data(0), next(nullptr) {}
        NodeSC(double d): data(d), next(nullptr) {}
        NodeSC(double d, NodeSC* nxt): data(d), next(nxt) {}
        ~NodeSC() { delete next; }
        double data;
        NodeSC *next;
};

class List {
    public:
        List(): head(nullptr) {}
        List(double x): head(new NodeSC(x)) {}
        ~List() { delete head; }
        NodeSC* get_head() { return this->head; }
        bool search_iter(double); // returns true if a node contains x
        bool search_rec(double, NodeSC*); // returns true if a node contains x
        void insert_iter(double x);
        void insert_rec(double x, NodeSC*);
        void print_list();
    private:
        NodeSC *head;
};

// searches for x in list iteratively
bool List::search_iter(double x) {
    if (this->head != nullptr) {
        NodeSC* current_node = this->head;
        while (current_node->next != nullptr) {
            if (abs(current_node->data - x) < 0.0001) {
                return true;
            }
            current_node = current_node->next;
        }
        if (abs(current_node->data - x) < 0.0001) {
            return true;
        }
    }
    return false;
}

// searches for x in list recursively
bool List::search_rec(double x, NodeSC* start_node) {
    if (start_node != nullptr) {
        if (abs(start_node->data - x) < 0.0001) {
            return true;
        }
        return search_rec(x, start_node->next);
    }
    return false;
}

// inserts node at end of list iteratively
void List::insert_iter(double x) {
    if (this->head == nullptr) {
        this->head = new NodeSC(x);
    } else {

        NodeSC* current_node = this->head;

        while (current_node->next != nullptr) {
            current_node = current_node->next;
        }

        current_node->next = new NodeSC(x);
    }
}

// inserts node at end of list recursively
void List::insert_rec(double x, NodeSC* current_node) {
    if (this->head == nullptr) {
        this->head = new NodeSC(x);
    } else if (current_node->next == nullptr) {
        current_node->next = new NodeSC(x);
    } else {
        insert_rec(x, current_node->next);
    }
}

// prints list
void List::print_list() {
    if (this->head != nullptr) {
        NodeSC* current_node = this->head;

        cout << fixed << setprecision(2) << "List values in order:" << endl;
        cout << current_node->data << " ";
        while (current_node->next != nullptr) {
            current_node = current_node->next;
            cout << current_node->data << " ";
        }

        cout << endl;
    }
}

int main() {
    List* list = new List(5.0);

    list->insert_iter(8.3);
    list->insert_iter(12.43);
    list->insert_iter(4.5);

    list->insert_rec(13.82, list->get_head());
    list->insert_rec(7.4, list->get_head());
    list->insert_rec(10.0, list->get_head());

    list->print_list();

    cout << "search for 5.0 iteratively: " << ((list->search_iter(5.0))? "true": "false") << endl;
    cout << "search for 4.5 iteratively: " << ((list->search_iter(4.5))? "true": "false") << endl;
    cout << "search for 6.5 iteratively: " << ((list->search_iter(6.5))? "true": "false") << endl;
    cout << endl;

    cout << "search for 5.0 recursively: " << ( (list->search_rec(5.0, list->get_head()) )? "true": "false") << endl;
    cout << "search for 4.5 recursively: " << ( (list->search_rec(4.5, list->get_head()) )? "true": "false") << endl;
    cout << "search for 6.5 recursively: " << ( (list->search_rec(6.5, list->get_head()) )? "true": "false") << endl;
    cout << endl;

    delete list;

    List list_two(12.7);

    list_two.insert_iter(2.34);
    list_two.insert_iter(3.14);
    list_two.insert_rec(12.34, list_two.get_head());
    list_two.insert_rec(0.34, list_two.get_head());

    list_two.print_list();

    cout << "search for 0.34 iteratively: " << ((list_two.search_iter(0.34))? "true": "false") << endl;
    cout << "search for 5.0 iteratively: " << ((list_two.search_iter(5.0))? "true": "false") << endl;
    cout <<endl;

    cout << "search for 51.1 recursively: " << ( (list_two.search_rec(51.1, list_two.get_head()) )? "true": "false") << endl;
    cout << "search for 3.14 recursively: " << ( (list_two.search_rec(3.14, list_two.get_head()) )? "true": "false") << endl;
    cout << endl;
    
    return 0;
}
