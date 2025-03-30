/*
 *  CSCI 115 - 03
 *  Lab 11
 *
 *  Devon Webb
 */

#include <cstdint>
#include <string>
#include <iostream>
#include <iomanip>

struct Matrix {
    // Constructors and destructors
    Matrix(int rows, int cols);
    Matrix(int rows, int cols, double* data);
    ~Matrix();

    // Getters
    double get(int row, int col);
    int get_index(int row, int col);

    Matrix multiply(Matrix& rhs);

    // Display
    void debug();

    private: 
        int rows;
        int cols;
        double* data;
};
