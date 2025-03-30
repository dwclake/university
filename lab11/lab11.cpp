/*
 *  CSCI 115 - 03
 *  Lab 11
 *
 *  Devon Webb
 */

#include <cstdio>
#include <functional>
#include <map>
#include <string>
#include <tuple>
#include <sstream>

using namespace std;

/* Priority queue implementation ----------------------------------------------------- */

// Singly Linked List Node class
template <class t>
struct QNode {
    QNode(t value): data(value), next(nullptr) {}
    ~QNode();

    t data;
    QNode<t>* next;
};

// List destructor
template <class t>
QNode<t>::~QNode() {
    if (this->next) {
        delete this->next;
    }
}

// Sorts the List using selection sort
template <class t>
void list_sort(QNode<t>* head, const function<bool(const t&, const t&)>& predicate) {
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

// Insert into a linked list passing the head pointer by reference
template <class t>
void insert(QNode<t>*& head, t value) {
    // Create new node
    auto new_head = new QNode<t>{value};
    // Make a copy of the head pointer
    QNode<t>* tmp = head;

    // Point new_head->next to the old head tmp
    // Point the old head tmp->previous to the new head
    new_head->next = tmp;

    head = new_head;
}

// Seach through list and check if value exists
template <class t>
bool search(QNode<t>* head, t value) {
    // Iterate through list and check if nodes data == value, return true if it does
    for ( auto node = head; node; node = node->next ) {
        if ( node->data == value ) return true;
    }

    // Return false as value was not found
    return false;
}

// Priority Queue class, which stores the highest priority node at the tail
template <class t>
struct PQueue {
    QNode<t>* head;
    QNode<t>* tail;
    function<bool(const t&, const t&)> predicate;
    int size;

    // Constructor taking a predicate which will be used for sorting the priority queue
    PQueue(const function<bool(const t&, const t&)>& predicate): head(nullptr), tail(nullptr), size(0) {
        this->predicate = predicate;
    }
    ~PQueue();

    bool is_empty() { return size == 0; }
    void debug();

    t dequeue();
    void enqueue(t value);
};

// PQueue destructor
template <class t>
PQueue<t>::~PQueue() {
    delete head;
    this->head = nullptr;
    this->tail = nullptr;
}

// Add a value to the priority queue
template <class t>
void PQueue<t>::enqueue(t value) {
    if (this->size == 0) {
        insert(this->head, value);
        this->tail = this->head;
    } else {
        insert(this->head, value);
    }

    size++;

    list_sort(this->head, this->predicate);
}

// Retrieves and removes the node with the highest priority, ie the tail
template <class t>
t PQueue<t>::dequeue() {
    if (this->size == 0) {
        return t{};
    } else if(this->size == 1) {
        // If size is one, head = tail
        auto tmp = this->head;
        t value = tmp->data;

        this->head = nullptr;
        this->tail = nullptr;

        delete tmp;
        size--;

        return value;
    } else if(this->size == 2) {
        // If size is two, tail must be set to head after
        auto tmp = this->tail;
        t value = tmp->data;

        this->head->next = nullptr;
        this->tail = this->head;

        delete tmp;
        size--;

        return value;
    }
    // Get value from tail
    t value = this->tail->data;

    QNode<t>* tmp = this->tail;
    QNode<t>* current = this->head;
    
    for (; current && current->next != tmp; current = current->next) {}

    delete tmp;

    current->next = nullptr;
    this->tail = current;
    size--;

    return value;
}

// Prints list to terminal
template <>
void PQueue<tuple<char, double>>::debug() {
    if ( !this->head ) {
        std::printf("[]\n");
        return;
    }

    std::stringstream ss;

    for ( auto node = this->head; node; node = node->next ) {
        char c;
        double d;
        tie(c, d) = node->data;

        ss << "[" << c << ", " << d << "]" << endl;
    }

    std::printf("%s\n", ss.str().c_str());
}

/* Huffman Encoding/Decoding implemetation ------------------------------------------- */

// Tree node for the frequency tree
struct TNode {
    TNode* left;
    TNode* right;
    char symbol;
    
    TNode(): left(nullptr), right(nullptr), symbol(0) {}

    TNode(char ch): left(nullptr), right(nullptr) {
        this->symbol = ch;
    }

    ~TNode() {
        delete this->left;
        delete this->right;
    }
};

// Huffman encoding, returns the encoded string and the 
// frequency tree for decoding the encoded string.
// Characters must be between 'space' and '~'
tuple<string, TNode*> encode(string source) {
    typedef tuple<char, double> frequency;

    string encoded;
    TNode* frequencies;
    map<char, int> counts; // Map for counting the symbols
    map<char, string> encodings; // Map for char to binary string encodings
    // Priority queue which keeps the lowest frequency symbol at the front of the queue 
    PQueue<frequency> queue([](const frequency& lhs, const frequency& rhs){
        return get<1>(lhs) < get<1>(rhs);
    });
    
    // Initialize the counts map, for each supported character
    for (int i = ' '; i < '~' + 1; i++) {
        counts.insert({i, 0});
    }

    // Count each symbol in the source
    for (int i = 0; i < source.length(); i++) {
        char current = source[i];

        if (current < ' ' && current > '~') {
            throw "Unsupported character in source";
        }

        counts[current]++;
    }

    // If symbols count is not zero, add it to the PQueue, with the calculated frequency
    for (int i = ' '; i < '~' + 1; i++) {
        if (counts[i] > 0) {
            queue.enqueue({i, counts[i] / source.length()});
        }
    }

    char c;
    double d;
    // Dequeue least frequent symbol, which will be encoded as all 1's
    tie(c, d) = queue.dequeue();
    frequencies = new TNode(c);
    
    // Prepare encoded binary string
    string bin = "";
    for (int i = 0; i < queue.size; i++) {
        bin = "1" + bin;
    }

    // Store first symbol encoding
    encodings.insert({c, bin});

    // Build the frequency tree and
    // store encodings for the rest of the symbols, all of which will end in '0'
    bin.back() = '0';
    int size = queue.size;
    for (int i = 0; i < size; i++) {
        // Adjust encoding to the correct length for the current leaf
        if (i != 0 && i != size - 1) {
            bin = bin.substr(1);
        } else if (i == size - 1) {
            bin = "0";
        }

        // Create new node and set frequency tree to the left of current
        TNode* current = new TNode;
        current->left = frequencies;

        // Dequeue next lowest frequency symbol and add to the right
        // of current, and store its encoding
        tie(c, d) = queue.dequeue();
        current->right = new TNode(c);
        encodings.insert({c, bin});

        // Set frequency tree to current
        frequencies = current;
    }

    // Convert source into encoded string
    for (int i = 0; i < source.length(); i++) {
        string value = encodings[source[i]];
        encoded.append(value);
    }

    return {encoded, frequencies};
}

// Decodes a huffman encoded string using the corresponding frequency tree
string decode(string encoded, TNode* frequencies) {
    string decoded = "";

    // Loop through each char of encoded string, navigate through the 
    // frequency tree until a leaf is found, pushing that node's
    // symbol to the decoded string
    for (int i = 0; i < encoded.length(); i = i) {
        TNode* current = frequencies;

        while (current->left && current->right && i < encoded.length()) {
            if (encoded[i] == '0') {
                i++;
                current = current->right;
            } else {
                i++;
                current = current->left;
            }
        }

        decoded.push_back(current->symbol);
    }

    return decoded;
}

/* Huffman Encoding/Decoding example ------------------------------------------------- */

int main() {
    string encoded;
    TNode* frequencies;

    printf("Encoding/Decoding \"Algorithms are cool!\"\n\n");

    // Encoded string
    tie(encoded, frequencies) = encode("Algorithms are cool!");
    // Decode string
    string result = decode(encoded, frequencies);

    printf("encoded: %s\n\ndecoded: %s", encoded.c_str(), result.c_str());

    delete frequencies;
}
