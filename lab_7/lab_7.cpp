#include <cstdlib>
#include <ctime>
#include <iostream>

/*
 Devon Webb CSCI 41
 lab_7.cpp
*/

using namespace std;

void random_arr(int* arr) {
    srand(time(0));
    for (int i = 0; i < 10; i++) {
        arr[i] = rand() & 100;
    }
}

void print_arr(int* arr) {
    cout << "array: ";
    for (int i = 0; i < 10; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void swap_elements(int* arr, int index_a, int index_b) {
    int temp = 0;
    temp = arr[index_a];
    arr[index_a] = arr[index_b];
    arr[index_b] = temp;
}

void selection_sort(int* arr) {
    for (int i = 0; i < 10; i++) {
        for (int j = i; j < 10; j++) {
            if (arr[j] < arr[i]) {
                swap_elements(arr, j, i);
            }
        }
    }
}

void insertion_sort(int* arr) {
    for (int i = 0; i < 9; i++) {
        int min = i;
        for (int j = i + 1; j < 10; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        swap_elements(arr, i, min);
    }
}

void bubble_sort(int* arr) {
    bool swapped;
    do {
        swapped = false;
        for (int i = 1 ; i < 10 ; i++) {
            if (arr[i] < arr[i - 1]) {
                swap_elements(arr, i, i - 1);
                swapped = true;
            }
        }
    } while (swapped);
}

/* Returns index of element if found, otherwise returns -1 */
int iter_binary_search(int* arr, int item) {
    int left = 0;
    int right = 9;
    
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] < item) {
            left = mid + 1;
        } else if (arr[mid] > item) {
            right = mid - 1;
        } else {
            return mid;
        }
    }
    return -1;
}

/* Returns index of element if found, otherwise returns -1 */
int rec_binary_search(int* arr, int item, int left = 0, int right = 9) {
    if (left > right) {
        return -1;
    }
    int mid = (left + right) / 2;
    if (arr[mid] < item) {
        rec_binary_search(arr, item, mid + 1, right);
    } else if (arr[mid] > item) {
        rec_binary_search(arr, item, left, mid - 1);
    } else {
        return mid;
    }
}

int main() {
    /* Creating a random array and sorting with selection sort */
    int arr[10];
    random_arr(arr);
    cout << "unsorted:" << endl;
    print_arr(arr);
    selection_sort(arr);
    cout << "sorted with bubble sort:" << endl;
    print_arr(arr);
    int index = iter_binary_search(arr, 100);
    cout << "index of number 100 if it exists found iteratively: " << index << endl;
    int index_r = rec_binary_search(arr, 100);
    cout << "index of number 100 if it exists found recursively: " << index_r << endl;
    cout << endl;
    
    /* Creating a random array and sorting with insertion sort */
    int arr2[10];
    random_arr(arr2);
    cout << "unsorted:" << endl;
    print_arr(arr2);
    insertion_sort(arr2);
    cout << "sorted with bubble sort:" << endl;
    print_arr(arr2);
    int index2 = iter_binary_search(arr2, 100);
    cout << "index of number 100 if it exists found iteratively: " << index2 << endl;
    int index2_r = rec_binary_search(arr2, 100);
    cout << "index of number 100 if it exists found recursively: " << index2_r << endl;
    cout << endl;
    
    /* Creating a random array and sorting with bubble sort */
    int arr3[10];
    random_arr(arr3);
    cout << "unsorted:" << endl;
    print_arr(arr3);
    bubble_sort(arr3);
    cout << "sorted with bubble sort:" << endl;
    print_arr(arr3);
    int index3 = iter_binary_search(arr3, 100);
    cout << "index of number 100 if it exists found iteratively: " << index3 << endl;
    int index3_r = rec_binary_search(arr3, 100);
    cout << "index of number 100 if it exists found recursively: " << index3_r << endl;
    cout << endl;
}
