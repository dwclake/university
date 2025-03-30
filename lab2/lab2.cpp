/*
 *  CSCI 115 - 03
 *  Lab 2
 *
 *  Devon Webb
 */

#include "Array3D.h"

#include <cstdio>
#include <cmath>

/* Part 1 ----------------------------- */
int fn_one_iter() {
    int n = 100;
    int sum = 0;

    for ( int i = 0; i < n; i++ ) {
        sum += (2 * i) + 9;
    }

    return sum;
};

int fn_one_rec(int i = 0, int n = 100, int sum = 0) {
    if ( i >= n ) {
        return sum;
    } else {
        sum += (2 * i) + 9;
        return fn_one_rec(i + 1, n, sum);
    }
}

int fn_two_iter() {
    int n = 100;
    int product = 1;

    for ( int i = 1; i < n; i++ ) {
        product *= (5 * pow(i, 3)) + pow(i, 2);
    }

    return product;
};

int fn_two_rec(int i = 1, int n = 100, int product = 1) {
    if ( i >= n ) {
        return product;
    } else {
        product *= (5 * pow(i, 3)) + pow(i, 2);
        return fn_two_rec(i + 1, n, product);
    }
}

int fn_three_iter() {
    int n = 500;
    int sum = 0;

    for ( int i = 0; i < n; i++ ) {
        sum += pow(5 * i, -0.5);
    }

    return sum;
};

int fn_three_rec(int i = 0, int n = 500, int sum = 0) {
    if ( i >= n ) {
        return sum;
    } else {
        sum += pow(5 * i, -0.5);
        return fn_one_rec(i + 1, n, sum);
    }
}

/* Part 2 -------------------------------- */

/* Part 3 -------------------------------- */

void fibonacci(int n, int* result) {
    int one = 1;
    int two = 1;
    
    for ( int i = 2; i < n; i++ ) {
        *result = one + two;
        
        int tmp = two;
        two = one + two;
        one = tmp;
    }
}

/* Testing in main ----------------------- */
int main() {
    // Part 0: 3D array test
    std::printf("Part 0, assigning 5 to [1, 2, 3]:\n");

    Array3D<int> arr(5, 5, 5);
    // Assign 5 to the element at [1, 2, 3]
    arr(1, 2, 3) = 5;

    std::printf("\tarray at [1, 2, 3]: %d\n", arr(1, 2, 3));
    std::printf("\tarray at [4, 2, 2]: %d\n", arr(4, 2, 2));

    // Part 1: function 1 iterative
    std::printf("\nPart 1:\n");

    int result;
    result = fn_one_iter();
    std::printf("\tfn_one calculated iteratively: %d\n", result);

    // Part 1: function 1 recursive
    result = fn_one_rec();
    std::printf("\tfn_one calculated recursively: %d\n", result);
    
    // Part 1: function 2 iterative
    result = fn_two_iter();
    std::printf("\tfn_two calculated iteratively: %d\n", result);

    // Part 1: function 2 recursive
    result = fn_two_rec();
    std::printf("\tfn_two calculated recursively: %d\n", result);
    
    // Part 1: function 3 iterative
    result = fn_three_iter();
    std::printf("\tfn_three calculated iteratively: %d\n", result);

    // Part 1: function 3 recursive
    result = fn_three_rec();
    std::printf("\tfn_three calculated recursively: %d\n", result);

    // Part 3: fibonacci iteratively
    std::printf("\nPart 3:\n");

    fibonacci(5, &result);
    std::printf("\tFibonacci number 5 is: %d\n", result);
}
