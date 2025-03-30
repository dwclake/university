/*
 *  CSCI 115 - 03
 *  Lab 4
 *
 *  Devon Webb
 *
 *  Tests run on linux, with i7-12700h x86 cpu
 *
 */

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <thread>
#include <tuple>
#include <random>

#include "Array.h"

using namespace std::chrono;

// Typedef for test results
typedef std::tuple<unsigned, unsigned, const char*, double> test;

// Global variables to keep track of tests complete
const unsigned NUMTESTS = 240;
unsigned tests_complete = 0;
bool finished = false;

// Swaps two elements of array
void swap(int* array, const unsigned& a, const unsigned& b) {
    int tmp = array[a];
    array[a] = array[b];
    array[b] = tmp;
}

// Selection sort algorithm
void selection_sort(int* array, unsigned n) {
  for ( int i = 0; i < n - 1; i++ ) {
    int min = i;

    for ( int j = i + 1; j < n; j++ ) {
      if ( array[j] < array[min] ) {
        min = j;
      }
    }

    if ( min != i ) {
      swap(array, min, i);
    }
  }
}

// Insertion sort algorithm
void insertion_sort(int* array, unsigned n) {
  for ( int i = 1; i < n; i++ ) {
    int key = array[i];
    int j = i - 1;

    while ( key < array[j] && j >= 0 ) {
      swap(array, j + 1, j);
      j--;
    }
    array[j + 1] = key;
  } 
}

// Bubble sort algorithm
void bubble_sort(int* array, unsigned n) {
  bool swapped;

  for ( int i = 0; i < n - 1; i++ ) {
    swapped = false;

    for ( int j = 0; j < n - i - 1; j++ ) {
      if ( array[j] > array[j + 1] ) {
        swap(array, i, j);
        swapped = true;
      }
    }
    if (!swapped) break;
  }
}

// Write results to .csv file
void write_to_csv(const char* filename, Array<test>* tests) {
  std::ofstream csv;
  const char* labels = "case,algorithm,n,time(ms)\n"; // Column labels
  // Template for each row: case, algorithm, n, time ellapsed
  const char* row_template = "%d,%s,%d,%.6f\n";

  csv.open(filename); 
  csv << labels;

  // For each test in tests, format results into a string using 
  // row_template then write to csv file buffer
  for ( const test& t : *tests ) {
    unsigned test_case, n;
    const char* algorithm;
    double ellapsed;
    // Destructure test t into separate variables
    std::tie(test_case, n, algorithm, ellapsed) = t;
    // Format using row_template, resulting string is stored in row
    char row[80];
    std::snprintf(row, std::size(row), row_template, test_case, algorithm, n, ellapsed);
    // Write formatted row to csv file buffer
    csv << row;
  }

  csv.close();
}

// Create a array of size n, with randomized values
int* rand_array(unsigned n) {
  int* array = new int[n];

  // Prepare randomizer
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distribution(0, n);

  // Generate random values
  for ( int i = 0; i < n; i++ ) {
    array[i] = distribution(gen);
  }

  return array;
}

// Shuffles elements of the array based on passed in percent
void shuffle_array(int* array, unsigned n, unsigned percent) {
  // Calculate the number of elements to shuffle
  unsigned num_to_shuffle = n * (percent/100); 

  // Prepare randomizer
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distribution(0, n - 1);

  // Shuffle elements randomly
  for ( int i = 0; i < num_to_shuffle; i++ ) {
    int a = distribution(gen);
    int b = distribution(gen);
    
    if ( a != b ) {
      array[a] = array[b];
    }
  }
}

// Runs tests for a given case a input size, using fn to setup array for testing
void run_test(
  Array<test>* tests, 
  unsigned test_case,
  unsigned n,
  const char* sortname,
  const std::function<void(int*, unsigned)>& sort,
  const std::function<void(int*, unsigned)>& init
) {
  // Run 5 iterations sorting array
  for ( int i = 0; i < 5; i++ ) {
    // Create randomized array and prepare it with fn
    int* array = rand_array(n);
    init(array, n);
    
    // Time sorting
    auto start = high_resolution_clock::now();

    sort(array, n);

    auto end = high_resolution_clock::now();
    double ellapsed = duration_cast<microseconds>(end - start).count() / 1000.0;

    // Append test results to tests
    tests->append({test_case, n, sortname, ellapsed});

    delete [] array;

    // Increment tests complete count
    tests_complete++;
  }
}

// Case one, randomized arrays
void case_one(Array<test>* tests) {
  // Lambda to prepare the arrays
  auto fn = [](int* array, unsigned n){};

  // Run tests for 4 input sizes, using bubble sort
  run_test(tests, 1, 100, "bubble", bubble_sort, fn);
  run_test(tests, 1, 1000, "bubble", bubble_sort, fn);
  run_test(tests, 1, 10000, "bubble", bubble_sort, fn);
  run_test(tests, 1, 100000, "bubble", bubble_sort, fn);
  // Run tests for 4 input sizes, using selection sort
  run_test(tests, 1, 100, "selection", selection_sort, fn);
  run_test(tests, 1, 1000, "selection", selection_sort, fn);
  run_test(tests, 1, 10000, "selection", selection_sort, fn);
  run_test(tests, 1, 100000, "selection", selection_sort, fn);
  // Run tests for 4 input sizes, using insertion sort
  run_test(tests, 1, 100, "insertion", insertion_sort, fn);
  run_test(tests, 1, 1000, "insertion", insertion_sort, fn);
  run_test(tests, 1, 10000, "insertion", insertion_sort, fn);
  run_test(tests, 1, 100000, "insertion", insertion_sort, fn);
}

// Case two, sorted arrays
void case_two(Array<test>* tests) {
  // Lambda to prepare the arrays
  auto fn = [](int* array, unsigned n){
    bubble_sort(array, n);
  };

  // Run tests for 4 input sizes, using bubble sort
  run_test(tests, 2, 100, "bubble", bubble_sort, fn);
  run_test(tests, 2, 1000, "bubble", bubble_sort, fn);
  run_test(tests, 2, 10000, "bubble", bubble_sort, fn);
  run_test(tests, 2, 100000, "bubble", bubble_sort, fn);
  // Run tests for 4 input sizes, using selection sort
  run_test(tests, 2, 100, "selection", selection_sort, fn);
  run_test(tests, 2, 1000, "selection", selection_sort, fn);
  run_test(tests, 2, 10000, "selection", selection_sort, fn);
  run_test(tests, 2, 100000, "selection", selection_sort, fn);
  // Run tests for 4 input sizes, using insertion sort
  run_test(tests, 2, 100, "insertion", insertion_sort, fn);
  run_test(tests, 2, 1000, "insertion", insertion_sort, fn);
  run_test(tests, 2, 10000, "insertion", insertion_sort, fn);
  run_test(tests, 2, 100000, "insertion", insertion_sort, fn);
}

// Case three, 90% sorted arrays
void case_three(Array<test>* tests) {
  // Lambda to prepare the arrays
  auto fn = [](int* array, unsigned n){
    bubble_sort(array, n);
    shuffle_array(array, n, 10);
  };

  // Run tests for 4 input sizes, using bubble sort
  run_test(tests, 3, 100, "bubble", bubble_sort, fn);
  run_test(tests, 3, 1000, "bubble", bubble_sort, fn);
  run_test(tests, 3, 10000, "bubble", bubble_sort, fn);
  run_test(tests, 3, 100000, "bubble", bubble_sort, fn);
  // Run tests for 4 input sizes, using selection sort
  run_test(tests, 3, 100, "selection", selection_sort, fn);
  run_test(tests, 3, 1000, "selection", selection_sort, fn);
  run_test(tests, 3, 10000, "selection", selection_sort, fn);
  run_test(tests, 3, 100000, "selection", selection_sort, fn);
  // Run tests for 4 input sizes, using insertion sort
  run_test(tests, 3, 100, "insertion", insertion_sort, fn);
  run_test(tests, 3, 1000, "insertion", insertion_sort, fn);
  run_test(tests, 3, 10000, "insertion", insertion_sort, fn);
  run_test(tests, 3, 100000, "insertion", insertion_sort, fn);
}

// Case four, 50% sorted arrays
void case_four(Array<test>* tests) {
  // Lambda to prepare the arrays
  auto fn = [](int* array, unsigned n){
    bubble_sort(array, n);
    shuffle_array(array, n, 50);
  };

  // Run tests for 4 input sizes, using bubble sort
  run_test(tests, 4, 100, "bubble", bubble_sort, fn);
  run_test(tests, 4, 1000, "bubble", bubble_sort, fn);
  run_test(tests, 4, 10000, "bubble", bubble_sort, fn);
  run_test(tests, 4, 100000, "bubble", bubble_sort, fn);
  // Run tests for 4 input sizes, using selection sort
  run_test(tests, 4, 100, "selection", selection_sort, fn);
  run_test(tests, 4, 1000, "selection", selection_sort, fn);
  run_test(tests, 4, 10000, "selection", selection_sort, fn);
  run_test(tests, 4, 100000, "selection", selection_sort, fn);
  // Run tests for 4 input sizes, using insertion sort
  run_test(tests, 4, 100, "insertion", insertion_sort, fn);
  run_test(tests, 4, 1000, "insertion", insertion_sort, fn);
  run_test(tests, 4, 10000, "insertion", insertion_sort, fn);
  run_test(tests, 4, 100000, "insertion", insertion_sort, fn);
}



int main() {
  // Spawn thread to run tests in
  std::thread thread([](){
    auto tests = new Array<test>;

    // Run each test case, accumulating results in tests
    case_one(tests);
    case_two(tests);
    case_three(tests);
    case_four(tests);

    // Write results to .csv file
    write_to_csv("data.csv", tests);

    delete tests;

    finished = true;
  });

  // Print out current progress of tests out of 240, until thread has signaled it finished
  while ( !finished ) {
    duration<int, std::milli> sleep(100);
    std::this_thread::sleep_for(duration_cast<milliseconds>(sleep));
    
    std::system("clear");
    std::printf("Tests complete: %d/%d\n", tests_complete, NUMTESTS);
  }

  // Wait for thread to finish execution
  thread.join();
}
