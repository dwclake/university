#include "Matrix.h"
#include <cstdint>

Matrix::Matrix(int rows, int cols) {
    this->rows = rows;
    this->cols = cols;
    this->data = new double[rows*cols]{0};
}

Matrix::Matrix(int rows, int cols, double* arr) {
    double* data = new double[rows * cols];    

    for (int i = 0; i < rows * cols; i++) {
        data[i] = arr[i];
    }

    this->rows = rows;
    this->cols = cols;
    this->data = data;
}

Matrix::~Matrix() {
    delete [] data;
}

double Matrix::get(int row, int col) {
    return this->data[this->get_index(row, col)];
}

int Matrix::get_index(int row, int col) {
    return row*cols + col;
}

Matrix Matrix::multiply(Matrix& rhs) {
    if (this->cols != rhs.rows) {
        throw "Attempted to multiply by matrix of incorrect dimensions";
    }

    double* data = new double[this->rows * rhs.cols];

    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < rhs.cols; j++) {
            double sum = 0.0;

            for (int k = 0; k < this->cols; k++) {
                sum += this->get(i, k) * rhs.get(k, j);
            }

            data[i * rhs.cols + j] = sum;
        }
    }

    return Matrix(this->rows, rhs.cols, data);
}

void Matrix::debug() {
    std::cout << "[" << std::endl;
    for (int i = 0; i < rows; i++) {
        std::cout << "    ";
        for (int j = 0; j < cols; j++) {
            std::cout << std::fixed << std::setprecision(2);
            if (j != cols - 1) {
                std::cout << data[get_index(i, j)] << ", ";
            } else {
                std::cout << data[get_index(i, j)] << std::endl;
            }
        }
    }

    std::cout << "]" << std::endl;
}
