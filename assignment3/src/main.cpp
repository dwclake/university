/*
 * @author: Devon Webb
 *
 * CSCI 114
 * Section 01
 * Programming Assignment 3
 *
 * How to execute:
 *
 * gcc CSCI114_P3.cpp --std=c++11 -lstdc++ -o CSCI114_P3
 * ./CSCI114_P3 4 5 6
 */

#include <thread>
#include <fstream>

using namespace std;

typedef int Matrix[100][100];
Matrix MatrixA;
Matrix MatrixB;
Matrix MatrixC;

// Load the matrices from A.txt and B.txt
void setupMatrices(int M, int N, int K) {
    ifstream A;
    ifstream B;

    A.open("A.txt", ios::in);
    B.open("B.txt", ios::in);

    // Load matrix from A.txt
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            A >> MatrixA[i][j];
        }
    }

    // Load matrix from B.txt
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < K; j++) {
            B >> MatrixB[i][j];
        }
    }

}

// Calculate the dot product for MatrixC[row][col]
void processElement(int row, int col, int N) {
    int sum = 0;

    for (int i = 0; i < N; i++) {
        sum += MatrixA[row][i] * MatrixB[i][col];
    }

    MatrixC[row][col] = sum;
}

// Pretty print the matrix to the screen
void printMatrix(Matrix* matrix, int rows, int cols) {
    // Print the colomn numbers
    printf("  \u2502 ");
    for (int i = 0; i < cols; i++) {
        printf("%4d ", i + 1);
    }
    printf("\n");

    // Print a separator
    printf("\u2500\u2500\u253c");
    for (int i = 0; i < cols * 5; i++) {
        printf("\u2500");
    }
    printf("\n");

    // Print each row
    for (int i = 0; i < rows; i++) {
        printf("%d \u2502 ", i + 1);
        for (int j = 0; j < cols; j++) {
            printf("%4d ", (*matrix)[i][j]);
        }
        printf("\n");
    }
}


int main(int argc, char** argv) {
    if (argc != 4) {
        printf("Incorrect number of arguments\n");
        return -1;
    }

    int M = atoi(argv[1]);
    int N = atoi(argv[2]); 
    int K = atoi(argv[3]);

    if (M > 100 || N > 100 || K > 100) {
        printf("Matrix dimensions cannot be larger than 100\n");
        return -1;
    }

    thread Threads[M][K];

    // Read the matrices from file
    setupMatrices(M, N, K);

    // Launch threads to calculate each element
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < K; j++) {
            Threads[i][j] = thread(processElement, i, j, N);
        }
    }

    // Join threads
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < K; j++) {
            Threads[i][j].join();
        }
    }

    // Print result
    printMatrix(&MatrixC, M, K);

    return 0;
}
