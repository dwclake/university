/*
 *  CSCI 115 - 03
 *  Lab 5
 *
 *  Devon Webb
 *
 *  Tests run on MacOS, with M1 cpu
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
const unsigned NUMTESTS = 160;
unsigned tests_complete = 0;

// Swaps two elements of array
void swap(int* array, const unsigned& a, const unsigned& b) {
    int tmp = array[a];
    array[a] = array[b];
    array[b] = tmp;
}

// Merge function for merge sort
void merge(int* array, int lo, int mid, int hi) {
  int n1 = (mid - lo) + 1;
  int* sub1 = new int[n1];
  for ( int i = 0; i < n1; i++ ) {
    sub1[i] = array[i + lo];
  }
  
  int n2 = hi - mid;
  int* sub2 = new int[n2];
  for ( int i = 0; i < n2; i++ ) {
    sub2[i] = array[i + mid + 1];
  }

  int
    i1 = 0,
    i2 = 0,
    i3 = lo;

  while ( i1 < n1 && i2 < n2 ) {
    if ( sub1[i1] < sub2[i2] ) {
      array[i3] = sub1[i1];
      i1++;
    } else {
      array[i3] = sub2[i2];
      i2++;
    }
    i3++;
  } 

  if ( i1 < n1 ) {
    for ( int i = i1; i < n1; i++ ) {
      array[i3] = sub1[i];
      i3++;
    }
  } else {
    for ( int i = i2; i < n2; i++ ) {
      array[i3] = sub2[i];
      i3++;
    }
  }

  delete [] sub1;
  delete [] sub2;
}

// Merge sort algorithm
void merge_sort(int* array, int lo, int hi) {
  if ( lo < hi ) {
    int mid = (lo + hi) / 2;

    merge_sort(array, lo, mid);
    merge_sort(array, mid + 1, hi);

    merge(array, lo, mid, hi);
  }
}

// Partition for quick sort, using random pivot
int partition(int* array, int lo, int hi) {
  srand(time(nullptr));
  int random = lo + rand() % (hi - lo);

  swap(array, random, hi);
  
  int pivot = array[hi];

  int i = (lo - 1);

  for ( int j = lo; j <= hi - 1; j++ ) {
    if ( pivot > array[j] ) {
      i++;
      swap(array, i, j);
    }
  }

  swap(array, i + 1, hi);
  return i + 1;
}

// Quick sort algorithm
void quick_sort(int* array, int lo, int hi) {
  if ( lo < hi ) {
    int pivot = partition(array, lo, hi);

    quick_sort(array, lo, pivot - 1);
    quick_sort(array, pivot + 1, hi);
  }
}

// Write results to .csv file
void write_to_csv(const char* filename, Array<test>* tests) {
  std::ofstream csv;
  const char* labels = "case,algorithm,n,time(ms)\n"; // Column labels
  // Template for each row: case, algorithm, n, time elapsed
  const char* row_template = "%d,%s,%d,%.3f\n";

  csv.open(filename); 
  csv << labels;

  // For each test in tests, format results into a string using 
  // row_template then write to csv file buffer
  for ( const test& t : *tests ) {
    unsigned test_case, n;
    const char* algorithm;
    double elapsed;
    // Destructure test t into separate variables
    std::tie(test_case, n, algorithm, elapsed) = t;
    // Format using row_template, resulting string is stored in row
    char row[80];
    std::snprintf(row, std::size(row), row_template, test_case, algorithm, n, elapsed);
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

// Runs tests for a given case a input size, using fn to setup array for testing
void run_test(
  Array<test>* tests, 
  unsigned test_case,
  unsigned n,
  const char* sortname,
  const std::function<void(int*, int, int)>& sort, // Sorting function to be tested
  const std::function<void(int*, unsigned)>& init // Function to prepare the array for the test, ie sorting half the array
) {
  // Run 5 iterations sorting array
  for ( int i = 0; i < 5; i++ ) {
    // Create randomized array and prepare it with fn
    int* array = rand_array(n);
    init(array, n - 1);
    
    // Time sorting
    auto start = high_resolution_clock::now();

    sort(array, 0, n - 1);

    auto end = high_resolution_clock::now();
    double elapsed = duration_cast<microseconds>(end - start).count() / 1000.0;

    // Append test results to tests
    tests->append({ test_case, n, sortname, elapsed});

    delete [] array;

    // Increment tests complete count
    tests_complete++;
  }
}

// Case one, randomized arrays
void case_one(Array<test>* tests) {
  // Lambda to prepare the arrays
  auto fn = [](int* array, unsigned n){};

  // Run tests for 4 input sizes, using merge sort
  run_test(tests, 1, 100, "merge", merge_sort, fn);
  run_test(tests, 1, 1000, "merge", merge_sort, fn);
  run_test(tests, 1, 10000, "merge", merge_sort, fn);
  run_test(tests, 1, 100000, "merge", merge_sort, fn);
  // Run tests for 4 input sizes, using quick sort
  run_test(tests, 1, 100, "quick", quick_sort, fn);
  run_test(tests, 1, 1000, "quick", quick_sort, fn);
  run_test(tests, 1, 10000, "quick", quick_sort, fn);
  run_test(tests, 1, 100000, "quick", quick_sort, fn);
}

// Case two, sorted arrays
void case_two(Array<test>* tests) {
  // Lambda to prepare the arrays
  auto fn = [](int* array, unsigned n){
    quick_sort(array, 0, n);
  };

  // Run tests for 4 input sizes, using merge sort
  run_test(tests, 2, 100, "merge", merge_sort, fn);
  run_test(tests, 2, 1000, "merge", merge_sort, fn);
  run_test(tests, 2, 10000, "merge", merge_sort, fn);
  run_test(tests, 2, 100000, "merge", merge_sort, fn);
  // Run tests for 4 input sizes, using quick sort
  run_test(tests, 2, 100, "quick", quick_sort, fn);
  run_test(tests, 2, 1000, "quick", quick_sort, fn);
  run_test(tests, 2, 10000, "quick", quick_sort, fn);
  run_test(tests, 2, 100000, "quick", quick_sort, fn);
}

// Case three, 90% sorted arrays
void case_three(Array<test>* tests) {
  // Lambda to prepare the arrays, only sort from 90% to end of array
  auto fn = [](int* array, unsigned n){
    quick_sort(array, (n * (90/100)), n);
  };

  // Run tests for 4 input sizes, using merge sort
  run_test(tests, 3, 100, "merge", merge_sort, fn);
  run_test(tests, 3, 1000, "merge", merge_sort, fn);
  run_test(tests, 3, 10000, "merge", merge_sort, fn);
  run_test(tests, 3, 100000, "merge", merge_sort, fn);
  // Run tests for 4 input sizes, using quick sort
  run_test(tests, 3, 100, "quick", quick_sort, fn);
  run_test(tests, 3, 1000, "quick", quick_sort, fn);
  run_test(tests, 3, 10000, "quick", quick_sort, fn);
  run_test(tests, 3, 100000, "quick", quick_sort, fn);
}

// Case four, 50% sorted arrays
void case_four(Array<test>* tests) {
  // Lambda to prepare the arrays, only sort from 50% to end of array
  auto fn = [](int* array, unsigned n){
    quick_sort(array, (n * (50/100)), n);
  };

  // Run tests for 4 input sizes, using merge sort
  run_test(tests, 4, 100, "merge", merge_sort, fn);
  run_test(tests, 4, 1000, "merge", merge_sort, fn);
  run_test(tests, 4, 10000, "merge", merge_sort, fn);
  run_test(tests, 4, 100000, "merge", merge_sort, fn);
  // Run tests for 4 input sizes, using quick sort
  run_test(tests, 4, 100, "quick", quick_sort, fn);
  run_test(tests, 4, 1000, "quick", quick_sort, fn);
  run_test(tests, 4, 10000, "quick", quick_sort, fn);
  run_test(tests, 4, 100000, "quick", quick_sort, fn);
}

int main() {
  // Bool to signal when tests thread has completed
  bool finished = false;

  // Spawn thread to run tests in
  std::thread thread([&finished](){
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
