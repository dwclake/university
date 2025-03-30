/*
 *  CSCI 115 - 03
 *  Lab 1
 *
 *  Devon Webb
 */

#include "Array.h"

#include <cstdlib>

int main() {
    // Array creation and assignment by indexing
    Array<int> array(10);
    *array[5] = 23;
    array.display();

    // Array size and indexing
    std::printf("array size: %d\n", array.size());
    std::printf("index %d = %d\n", 5, *array[5]);

    // Counting the elements with values 23 and 0 in the array
    std::printf("number of elements with value 23: %d\n", array.count(23));
    std::printf("number of elements with value 0: %d\n", array.count(0));

    // Inserting at the end of the array
    std::printf("\nAppend 32 to array:\n");
    array.append(32);
    array.display();

    // Inserting at the beginning of the array
    std::printf("\nPrepend 12 to array:\n");
    array.prepend(12);
    array.display();

    // Sorting array in ascending order
    std::printf("\nSorting array in ascending order\n");
    Array<int> array2 = array;
    array2.sort();
    array2.display();

    // Sorting array using lambda
    std::printf("\nSorting array in descending order\n");
    Array<int> array3 = array;
    array3.sort( [](int a, int b) -> bool { 
        return a < b; 
    });
    array3.display();

    // Insert into correct position of sorted array
    Array<int> array4(10);
    std::printf("\nInserting 35 into the correct postition [sorted]\nInitial: ");
    for ( int i = 0; i < array4.size(); i++ ) {
        *array4[i] = i * 10;
    }
    array4.display();
    array4.insert_sorted(35);
    std::printf("Final:   %s\n", array4.to_string().c_str());
    
    // Insert into correct position of unsorted array
    Array<int> array5(10);
    std::printf("\nInserting 35 into the correct postition [unsorted]\nInitial: ");
    for ( int i = 0; i < array5.size(); i++ ) {
        *array5[i] = rand() % 100;
    }
    array5.display();
    array5.insert_sorted(35);
    std::printf("Final:   %s\n", array5.to_string().c_str());
    
    // Insert into correct position of unsorted array
    Array<int> array6(10);
    std::printf("\nInserting 35 into the correct postition [unsorted]\nInitial: ");
    for ( int i = 0; i < array6.size(); i++ ) {
        *array6[i] = rand() % 100;
    }
    array6.display();
    array6.insert_sorted(35);
    std::printf("Final:   %s\n", array6.to_string().c_str());

    // Delete front
    Array<int> array7 = array4;
    std::printf("\nDeleting from front\nInitial: ");
    array7.display();
    array7.delete_front();
    std::printf("Final: ");
    array7.display();

    // Delete back
    Array<int> array8 = array4;
    std::printf("\nDeleting from back\nInitial: ");
    array8.display();
    array8.delete_back();
    std::printf("Final: ");
    array8.display();
    
    // Delete at index 5
    Array<int> array9 = array4;
    std::printf("\nDeleting at index 5\nInitial: ");
    array9.display();
    array9.delete_at(5);
    std::printf("Final: ");
    array9.display();
    
    // Delete first element matching 35
    Array<int> array10(0);
    array10.append(20);
    array10.append(35);
    array10.append(20);
    array10.append(40);
    array10.append(40);
    array10.append(20);
    array10.append(20);
    array10.append(35);
    array10.append(35);
    array10.append(20);
    std::printf("\nDeleting first element matching 35\nInitial: ");
    array10.display();
    array10.delete_match(35);
    std::printf("Final: ");
    array10.display();
    
    // Delete first element matching 35
    Array<int> array11(0);
    array11.append(20);
    array11.append(35);
    array11.append(20);
    array11.append(40);
    array11.append(40);
    array11.append(20);
    array11.append(20);
    array11.append(35);
    array11.append(35);
    array11.append(20);
    std::printf("\nDeleting all elements matching 35\nInitial: ");
    array11.display();
    array11.delete_matches(35);
    std::printf("Final: ");
    array11.display();
    
    // Recursive binary search for 35
    Array<int> array12 = array4;
    std::printf("\nRecursive binary search for 35\n");
    array12.display();
    std::printf(
        "Index 35 was found at: %d\n", 
        array12.binary_search(35, 0, array12.size())
    );
    
    // Iterative binary search for 35
    Array<int> array13 = array4;
    std::printf("\nIterative binary search for 35\n");
    array13.display();
    std::printf(
        "Index 35 was found at: %d\n", 
        array13.binary_search_iter(35, 0, array13.size())
    );
}
