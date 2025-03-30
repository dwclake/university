/*
 *  CSCI 115 - 01
 *  Project
 *
 *  Devon Webb
 *
 *  Matrix class, statically allocated 
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <sstream>

template <class t>
struct Matrix {
    Matrix(const int&, const int&, const t&);
    ~Matrix();

    t* operator[](const int& i);
    std::string to_string();
    void debug();

    private: 
        t** data; 
        int width;
        int height;
};

template <class t>
Matrix<t>::Matrix(const int& width, const int& height, const t& init) {
    if (width < 1 || height < 1) {
        throw "Matrix width and height must be >= 1";
    }

    this->width = width;
    this->height = height;

    this->data = new t*[height];

    for (int i = 0; i < height; i++) {
        this->data[i] = new t[width];
    }
}

template <class t>
Matrix<t>::~Matrix() {
    if (this->data == nullptr) {
        return;
    }

    for (int i = 0; i < this->height; i++) {
        delete [] this->data[i];
        this->data[i] = nullptr;
    }

    delete [] this->data;
    this->data = nullptr;
}

template <class t>
t* Matrix<t>::operator[](const int& i) {
    return this->data[i];
}

template <class t>
std::string Matrix<t>::to_string() {
    std::stringstream ss;

    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            ss << this->data[i][j];
        }
        ss << "\n";
    }

    return ss.str();
}

template <class t>
void Matrix<t>::debug() {
    if (this->width + this->height < 2) {
        std::printf("[]\n");
        return;
    }

    std::stringstream ss;

    ss << "[\n";

    for (int i = 0; i < this->height; i++) {
        ss << "    ";
        for (int j = 0; j < this->width; j++) {
            ss << this->data[i][j] << " ";
        }
        ss << "\n";
    }

    ss << "]\n";

    std::printf("%s", ss.str().c_str());
}

#endif // !MATRIX_H
