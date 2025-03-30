/*
 *  CSCI 115 - 03
 *  Lab 1
 *
 *  Devon Webb
 */

#include <cstdio>
#include <string>
#include <functional>

template <class T>
class Array {
    private:
        T* array;
        int _size = 0;
    public:
        Array(const int& initial_size);
        // Copy constructor
        Array(const Array<T>& rhs);
        ~Array();
        int size() const { return this->_size; }
        // Counts how many elements contain the parameter value
        int count(const T& value) const;
        // Adds value to the end of the array
        void append(const T& value);
        // Adds value to the beginning of the array
        void prepend(const T& value);
        // Adds value at the correct position in the array, will sort if unsorted
        void insert_sorted(const T& value);
        void delete_front();
        void delete_back();
        // Deletes element at given idx
        void delete_at(const int& index);
        // Deletes the first element with a matching value
        void delete_match(const T& value);
        // Deletes all elements with a matching value
        void delete_matches(const T& value);
        int binary_search(const T& value, int lo, int hi);
        int binary_search_iter(const T& value, int lo, int hi);
        // Sorts using bubble sort in ascending order
        void sort();
        // Sorts using bubble sort based on predicate lambda passed in
        void sort(const std::function<bool(T, T)>& predicate);
        T* operator[](const int& index);
        void display();
        std::string to_string();
};

// Constructor
template <class T>
Array<T>::Array(const int& initial_size) {
    this->array = new T[initial_size];
    this->_size = initial_size;
}

// Copy constructor
template <class T>
Array<T>::Array(const Array<T>& rhs) {
    this->array = new T[rhs.size()];
    this->_size = rhs.size();

    for ( int i = 0; i < rhs.size(); i++ ) {
        this->array[i] = rhs.array[i];
    }
}

// Destructor
template <class T>
Array<T>::~Array() {
    delete [] this->array;
}

// Counts the number of elements containing the parameter value
template <class T>
int Array<T>::count(const T& value) const {
    int count = 0;

    // Iterate through array and increment counter if match is found
    for ( int i = 0; i < this->_size; i++) {
        if ( this->array[i] == value ) {
            count++;
        }
    }

    return count;
}

// Add a new element to the end of the array
template <class T>
void Array<T>::append(const T& value) {
    // Copy array and size
    T* tmp = this->array;
    int old_size = this->_size;
    
    // Assign new size and allocate new memory
    int new_size = old_size + 1;
    this->array = new T[new_size];
    this->_size = new_size;

    // Copy old values
    for ( int i = 0; i < old_size; i++ ) {
        this->array[i] = tmp[i];
    }
    
    // Assign new element
    this->array[old_size] = value;
}

// Add a new element to the beginning of the array
template <class T>
void Array<T>::prepend(const T& value) {
    // Copy array and size
    T* tmp = this->array;
    int old_size = this->_size;

    // Assign new size and allocate memory
    int new_size = old_size + 1;
    this->array = new T[new_size];
    this->_size = new_size;

    // Copy old values, moving the values one position further into the array
    for ( int i = 0; i < new_size; i++ ) {
        this->array[i + 1] = tmp[i];
    }

    // Assign new element
    this->array[0] = value;
}

// Check if array is sorted in ascending order
template <class T>
bool sorted_asc(T* const arr, const int& size) {
    bool sorted = true;

    for ( int i = 0; i < size; i += 2) {
        if ( arr[i] > arr[i + 1] ) {
            sorted = false;
        }
    }

    return sorted;
}

// Swaps two elements in the given array
template <class T>
void swap(T* arr, const int& a, const int& b) {
    T tmp = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;
}

// Sorts in ascending order using bubblesort
template <class T>
void Array<T>::sort() {
    for ( int i = 0; i < this->_size; i++ ) {
        for ( int j = i + 1; j < this->_size; j++ ) {
            if ( this->array[i] > this->array[j] ) {
                swap(this->array, i, j);
            }
        }
    }

}

// Sorts based on predicate lambda passed in, using bubblesort
template <class T>
void Array<T>::sort(const std::function<bool(T, T)>& predicate) {
    for ( int i = 0; i < this->_size; i++ ) {
        for ( int j = i + 1; j < this->_size; j++ ) {
            if ( predicate(this->array[i], this->array[j]) ) {
                swap(this->array, i, j);
            }
        }
    }
}


// Finds the first element greater than given value
template <class T>
int first_greater(T* const arr, const int& size, const T& value) {
    for ( int i = 0; i <= size; i ++ ) {
        if ( arr[i] > value ) return i;
    } 

    return -1;
}

// Adds a new element at the correct position in a sorted array, sorts array if unsorted
template <class T>
void Array<T>::insert_sorted(const T& value) {
    // Check if array is sorted, if not sort the array
    if ( !sorted_asc(this->array, this->_size) ) {
        this->sort();
    }

    // Find the first element greater than value, which will be the idx to insert
    int in_idx = first_greater(this->array, this->_size, value); 
    
    // If in_idx is -1, that means new element is greater than all in array, so must be
    // inserted at end. So append the new value and return
    if ( in_idx == -1 ) {
        this->append(value);
        return;
    }

    // Create copy of array and size
    T* tmp = this->array;
    int old_size = this->_size;
    
    // Set new size and allocate new memory
    int new_size = old_size + 1;
    this->array = new T[new_size];
    this->_size = new_size;

    // Copy array from tmp up til the insert idx
    for ( int i = 0; i < in_idx; i++ ) {
        this->array[i] = tmp[i];
    }
    
    // Copy tmp from insert idx shifting one idx forward, leaving space for new element
    for ( int i = in_idx; i < old_size; i++ ) {
        this->array[i + 1] = tmp[i];
    }

    // Assign new value
    this->array[in_idx] = value;
}

// Removes the first element
template <class T>
void Array<T>::delete_front() {
    // Copy array and size
    T* tmp = this->array;
    int old_size = this->_size;
    
    // Assign new size and allocate new memory
    int new_size = old_size - 1;
    this->array = new T[new_size];
    this->_size = new_size;

    // Copy old values, starting at the second element
    for ( int i = 1; i < old_size; i++ ) {
        this->array[i - 1] = tmp[i];
    }
}

// Removes the last element
template <class T>
void Array<T>::delete_back() {
    // Copy array and size
    T* tmp = this->array;
    int old_size = this->_size;
    
    // Assign new size and allocate new memory
    int new_size = old_size - 1;
    this->array = new T[new_size];
    this->_size = new_size;

    // Copy old values, except for the final element
    for ( int i = 0; i < new_size; i++ ) {
        this->array[i] = tmp[i];
    }
}

// Removes the element at the given index
template <class T>
void Array<T>::delete_at(const int& index) {
    // Copy array and size
    T* tmp = this->array;
    int old_size = this->_size;
    
    // Assign new size and allocate new memory
    int new_size = old_size - 1;
    this->array = new T[new_size];
    this->_size = new_size;

    // Copy old values, up to the index to remove
    for ( int i = 0; i < index; i++ ) {
        this->array[i] = tmp[i];
    }
    
    // Copy old values, up to the index to remove
    for ( int i = index; i < new_size; i++ ) {
        this->array[i] = tmp[i + 1];
    }
}

// Removes the first element matching the given value
template <class T>
void Array<T>::delete_match(const T& value) {
    // Copy array and size
    T* tmp = this->array;
    int old_size = this->_size;
    
    // Assign new size and allocate new memory
    int new_size = old_size - 1;
    this->array = new T[new_size];
    this->_size = new_size;

    int match_idx = -1;

    // Linearly search for match
    for ( int i = 0; i < old_size; i++ ) {
        if ( value == tmp[i] ) {
            match_idx = i;
            break;
        }
    }
    if ( match_idx == -1 ) return;

    // Copy old values, up to the index to remove
    for ( int i = 0; i < match_idx; i++ ) {
        this->array[i] = tmp[i];
    }
    
    // Copy old values, up to the index to remove
    for ( int i = match_idx; i < new_size; i++ ) {
        this->array[i] = tmp[i + 1];
    }
}

// Removes every element matching the given value
template <class T>
void Array<T>::delete_matches(const T& value) {
    // Copy array and size
    T* tmp = this->array;
    int old_size = this->_size;
    
    // Find all the matching values, adding their idx to the matches array
    Array<int> matches(0); 
    for ( int i = 0; i < old_size; i++ ) {
        if ( value == tmp[i] ) {
            matches.append(i);
        }
    }
    if ( matches.size() == 0 ) return;
    
    // Assign new size and allocate new memory
    int new_size = old_size - matches.size();
    this->array = new T[new_size];
    this->_size = new_size;
    
    // The following inner loop (j) loops up to each matching idx,
    // so push back old_size so it can iterate through the entire array
    matches.append(old_size);
    // Copy old values
    // i = the number of matches removed in loop so far, 
    // so it is the offset that values need to be shifted by.
    // j = the index in the old array
    int start = 0; // The index for j to start at
    for ( int i = 0; i < matches.size(); i++ ) {
        for ( int j = start; j < *matches[i]; j++ ) {
            this->array[j - i] = tmp[j];
        }
        // Set start to the idx after the removed value
        start = *matches[i] + 1;
    }
}

// Recursive binary search, returning idx of matching value, -1 if not found
template <class T>
int Array<T>::binary_search(const T& value, int lo, int hi) {
    if ( lo > hi ) return -1;

    int mid = ( lo + hi ) / 2;
    // Check if value matches array[mid]
    if ( value == this->array[mid] ) {
        return mid;
    } else if ( value > this->array[mid] ) {
        return binary_search(value, mid + 1, hi);
    } else {
        return binary_search(value, lo, mid - 1);
    }
}

// Iterative binary search, returns idx of matching value, -1 if not found
template <class T>
int Array<T>::binary_search_iter(const T& value, int lo, int hi) {
    int mid;

    while ( lo <= hi ) {
        mid = ( lo + hi ) / 2;

        // Check if value matches array[mid]
        if ( value == this->array[mid] ) {
            return mid;
        } else if ( value > this->array[mid] ) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    return -1;
}

// Allows indexing into the array
template <class T>
T* Array<T>::operator[](const int& index) {
    T* val = nullptr;

    if ( index >= 0 && index <= this->_size ) {
        val = &this->array[index];
    }

    return val;
}

// Prints out the array to stout
template <class t>
void Array<t>::display() {
    std::string str = "[";
    for ( int i = 0; i < this->_size; i++ ) {
        str.append(std::to_string(this->array[i]) + ", ");
    }
    str = str.substr(0, str.length() - 2);
    str.append("]");

    std::printf("%s\n", str.c_str());
}

// Returns std::string of array contents
template <class t>
std::string Array<t>::to_string() {
    std::string str = "[";
    for ( int i = 0; i < this->_size; i++ ) {
        str.append(std::to_string(this->array[i]) + ", ");
    }
    str = str.substr(0, str.length() - 2);
    str.append("]");

    return str;
}
