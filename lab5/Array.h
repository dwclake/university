/*
 *  CSCI 115 - 03
 *  Lab 5
 *
 *  Devon Webb
 */

#include <cmath>
#include <cstdio>
#include <iterator>
#include <string>
#include <functional>
#include <sstream>

template <class T>
class Array {
  private:
    T* array;
    int _size{0};
    int capacity{0};
    // Predicate for sorting functions, defaults to ascending order
    std::function<bool(const T&, const T&)> predicate;
  public:
    Array();
    Array(const int& capacity);
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
    void update_predicate(const std::function<bool(const T&, const T&)>& predicate) { this->predicate = predicate; }
    // Adds value at the correct position in the array, will sort if unsorted
    void insert(const T& value);
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
    // Sorts using quick sort based on this->predicate
    void sort();
    T* operator[](const int& index);
    void display();
    std::string to_string();
    double std_dev();
    double mean();

    // Iterator to allow use in ranged based for loops
    struct Iterator;

    Iterator begin() { return Iterator(&array[0]); }
    Iterator end() { return Iterator(&array[_size]); }
};


// Default Constructor
template <class T>
Array<T>::Array() {
  this->array = new T[10];
  this->capacity = 10;
  this->predicate = [](const T& a, const T& b){ return a > b; };
}

// Constructor
template <class T>
Array<T>::Array(const int& capacity) {
  this->array = new T[capacity];
  this->capacity = capacity;
  this->predicate = [](const T& a, const T& b){ return a > b; };
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
void Array<T>::prepend(const T& value) {
  // Copy array and size
  int old_size = this->_size;

  // Assign new size
  int new_size = old_size + 1;
  this->_size = new_size;

  // If new size is greater than the capacity, allocate new memory
  if ( new_size >= this->capacity ) {
    T* tmp = this->array;
    this->array = new T[this->capacity * 2];
    this->capacity *= 2;

    // Copy old values
    for ( int i = 0; i < new_size; i++ ) {
      this->array[i + 1] = tmp[i];
    }
  } else {
    for ( int i = old_size; i > 0; i-- ) {
      this->array[i] = this->array[i - 1];
    }
  }

  // Assign new element
  this->array[0] = value;
}

// Add a new element to the end of the array
template <class T>
void Array<T>::append(const T& value) {
  // Copy array and size
  int old_size = this->_size;

  // Assign new size
  int new_size = old_size + 1;

  // If new size is greater than the capacity, allocate new memory
  if ( new_size > this->capacity ) {
    T* tmp = this->array;
    this->array = new T[this->capacity * 2];
    this->capacity *= 2;

    // Copy old values
    for ( int i = 0; i < old_size; i++ ) {
      this->array[i] = tmp[i];
    }
  }

  this->_size = new_size;

  // Assign new element
  this->array[old_size] = value;
}

// Check if array is sorted according to passed in predicate
template <class T>
bool sorted(T* const arr, const int& size, const std::function<bool(const T&, const T&)>& predicate) {
  bool sorted = true;

  for ( int i = 0; i < size; i += 2) {
    if ( predicate(arr[i], arr[i + 1]) ) {
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

template <class T>
int partition(T* array, int lo, int hi, const std::function<bool(const T&, const T&)>& predicate) {
  
  srand(time(nullptr));
  int random = lo + rand() % (hi - lo);

  swap(array, random, hi);
  
  int pivot = array[hi];

  int i = (lo - 1);

  for ( int j = lo; j <= hi - 1; j++ ) {
    if ( predicate(pivot, array[j]) ) {
      i++;
      swap(array, i, j);
    }
  }

  swap(array, i + 1, hi);
  return i + 1;
}

template <class T>
void quicksort(T* array, int lo, int hi, const std::function<bool(const T&, const T&)>& predicate) {
  if ( lo < hi ) {
    int pivot = partition(array, lo, hi, predicate);

    quicksort(array, lo, pivot - 1, predicate);
    quicksort(array, pivot + 1, hi, predicate);
  }
}

// Sorts based on predicate lambda passed in, using quicksort
template <class T>
void Array<T>::sort() {
  quicksort(this->array, 0, this->_size - 1, this->predicate);
}


// Finds the first element greater than given value
template <class T>
int first_match(T* const arr, const int& size, const T& value, const std::function<bool(const T&, const T&)>& predicate) {
  for ( int i = 0; i <= size; i ++ ) {
    if ( predicate(arr[i], value) ) return i;
  } 

  return -1;
}

// Adds a new element at the correct position in a sorted array, sorts array if unsorted based on predicate
template <class T>
void Array<T>::insert(const T& value) {
  // Check if array is sorted, if not sort the array
  if ( !sorted(this->array, this->_size, this->predicate) ) {
    this->sort();
  }

  // Find the first element where predicate returns true, which will be the idx to insert
  int in_idx = first_match(this->array, this->_size, value, this->predicate); 

  // If in_idx is -1, that means new element is greater than all in array, so must be
  // inserted at end. So append the new value and return
  if ( in_idx == -1 ) {
    this->append(value);
    return;
  }

  // Create copy of size
  int old_size = this->_size;

  // Set new size and allocate new memory
  int new_size = old_size + 1;
  this->_size = new_size;

  if ( new_size >= this->capacity ) {
    T* tmp = this->array;
    this->array = new T[capacity * 2];
    this->capacity *= 2;
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
  } else {
    // Copy tmp from insert idx shifting one idx forward, leaving space for new element
    for ( int i = old_size; i > in_idx; i-- ) {
      this->array[i] = this->array[i - 1];
    }

    // Assign new value
    this->array[in_idx] = value;
  }
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
  this->capacity = new_size;

  // Copy old values, starting at the second element
  for ( int i = 1; i < old_size; i++ ) {
    this->array[i - 1] = tmp[i];
  }
}

// Removes the last element
template <class T>
void Array<T>::delete_back() {
  // Copy array and size
  int old_size = this->_size;

  // Assign new size
  int new_size = old_size - 1;
  this->_size = new_size;
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
  this->capacity = new_size;

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
  this->capacity = new_size;

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
  this->capacity = new_size;

  // The following inner loop (j) loops up to each matching idx,
  // so push back old_size, so it can iterate through the entire array
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
  if ( this->_size < 1 ) {
    std::printf("[]\n");
    return;
  }

  std::stringstream ss;

  ss << "[\n";
  for ( int i = 0; i < this->_size; i++ ) {
    ss << "  " << this->array[i] << ",\n";
  }
  std::string str = ss.str().substr(0, ss.str().length() - 2);
  str.append("\n]");

  std::printf("%s\n", str.c_str());
}

// Returns std::string of array contents
template <class t>
std::string Array<t>::to_string() {
  if ( this->_size > 1 ) {
    return "[]";
  }

  std::stringstream ss;

  ss << "[\n";
  for ( int i = 0; i < this->_size; i++ ) {
    ss << "  " << this->array[i] << ",\n";
  }
  std::string str = ss.str().substr(0, ss.str().length() - 2);
  str.append("\n]");

  return str;
}

template <class T>
double Array<T>::std_dev() {
  double mean = this->mean();
  
  double sum = 0;
  for ( int i = 0; i < this->_size; i++ ) {
    sum += std::pow(this->array[i] - mean, 2);
  }

  return std::sqrt(sum / this->_size);
}

template <class T>
double Array<T>::mean() {
  double sum = 0;

  for ( int i = 0; i < this->_size; i++ ) {
    sum += this->array[i];
  }

  return sum / this->_size;
}

template <class T>
struct Array<T>::Iterator {
  private:
    T* m_ptr;
  public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;

    Iterator(T* ptr) : m_ptr(ptr) {}

    T& operator*() const { return *m_ptr; }
    T* operator->() { return m_ptr; }
    
    Iterator& operator++() { m_ptr++; return *this; }
    Iterator& operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

    friend bool operator==(const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; }
    friend bool operator!=(const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; }
};
