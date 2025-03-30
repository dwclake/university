/*
 *  CSCI 115 - 03
 *  Lab 2
 *
 *  Devon Webb
 */

template <class T>
class Array3D {
    private:
        T*** array;
        int n;
        int m;
        int l;
    public:
        Array3D(const int& n, const int& m, const int& l);
        ~Array3D();
        // Overloaded call operator for 3d indexing
        T& operator()(const int& n, const int& m, const int& l);
};

template <class T>
Array3D<T>::Array3D(const int& n, const int& m, const int& l) {
    // Make a copy of the dimensions
    this->n = n;
    this->m = m;
    this->l = l;

    // Allocate the first dimension
    this->array = new T**[n];
    
    // Allocate the second and third dimension
    for ( int i = 0; i < n; i++ ) {
        this->array[i] = new T*[m];

        for ( int j = 0; j < m; j++ ) {
            this->array[i][j] = new T[l];
        }
    }
}

template <class T>
Array3D<T>::~Array3D() {
    // Free the second dimension
    for ( int i = 0; i < this->n; i++ ) {
        delete [] this->array[i];
    }
    // Free the first dimension
    delete [] this->array;
}

template <class T>
T& Array3D<T>::operator()(const int& n, const int& m, const int& l) {
    // If any of the indices are out of bounds, throw exception
    if ( n < 0 || n >= this->n || m < 0 || m >= this->m || l < 0 || l >= this->l ) 
    {
        throw "indecies out of bounds";    
    }
    // Return a reference to the desired element
    return this->array[n][m][l];
}
