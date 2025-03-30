/*
 *  CSCI 115 - 03
 *  Lab 3
 *
 *  Devon Webb
 */


/*
 * Results
 *
 *   Allocating memory one element at a time:
 *     std dev: 38.94 ms, mean: 176.14 ms
 *   Allocating memory by doubling when needed:
 *     std dev: 0.03 ms, mean: 0.09 ms
 */

#include "Array.h"

#include <string>
#include <cstdio>
#include <chrono>
#include <tuple>

// Returns the steps to move n disks from tower A to tower C
void hanoi_tower(
    Array<std::string>* steps,
    int n, 
    const char* source = "A",
    const char* auxiliary = "B",
    const char* destination = "C"
) {
  // Base step: n <= 1
  if ( n <= 1 ) {
    // Format a string detailing the current step and append it to steps
    char step[80];
    std::sprintf(step,
      "Move a disk from tower %s to tower %s",
      source, 
      destination
    );
    steps->append(step);
    return;
 }

  // Recursively call hanoi_tower, swaping the destination and auxiliary
  hanoi_tower(steps, n - 1, source, destination, auxiliary);

  // Format a string detailing the current step and append it to steps
  char step[80];
  std::sprintf(step,
    "Move a disk from tower %s to tower %s", 
    source, 
    destination
  );
  steps->append(step);

  // Recursively call hanoi_tower, swaping the source and auxiliary
  hanoi_tower(steps, n - 1, auxiliary, source, destination);
}

void test_memory_allocations(Array<double>* times_i, Array<double>* times_d) {
  auto array_i = new Array<int>; // Array to use incremental memory allocation
  auto array_d = new Array<int>(10); // Array to use doubling memory allocation

  // Insert 10,000 elements allocating new memory each time
  auto start_i = std::chrono::high_resolution_clock::now();
  for ( int i = 0; i < 10000; i++ ) {
    array_i->append(i);
  }
  auto end_i = std::chrono::high_resolution_clock::now();
  double ellapsed_i = std::chrono::duration_cast<std::chrono::microseconds>(end_i - start_i).count() / 1000.0;

  // Insert 10,000 elements doubling the capacity as needed
  auto start_d = std::chrono::high_resolution_clock::now();
  for ( int i = 0; i < 10000; i++ ) {
    array_d->insert_d(i);
  }
  auto end_d = std::chrono::high_resolution_clock::now();
  double ellapsed_d = std::chrono::duration_cast<std::chrono::microseconds>(end_d - start_d).count() / 1000.0;

  times_i->insert_d(ellapsed_i);
  times_d->insert_d(ellapsed_d);

  delete array_i;
  delete array_d;
}

int main() {
  auto steps = new Array<std::string>;
  // Calculate the steps required for 5 disks, which will be stored in steps
  hanoi_tower(steps, 5);
  // Display the calculated steps
  std::printf("The steps required to solve 5 disk hanoi tower:\n");
  steps->display();
  delete steps;
  
  auto times_i = new Array<double>(10);
  auto times_d = new Array<double>(10);

  for ( int i = 0; i < 100; i++ ) {
    test_memory_allocations(times_i, times_d);
  }

  std::printf(R"(
      The std dev and mean for allocating memory each insert:
        std dev: %.2f ms. mean: %.2f ms.
      The std dev and mean for doubling capacity as needed:
        std dev: %.2f ms. mean: %.2f ms.
    )",
    times_i->std_dev(), times_i->mean(),
    times_d->std_dev(), times_d->mean()
  );
  
  delete times_i;
  delete times_d;

  return 0;
}
