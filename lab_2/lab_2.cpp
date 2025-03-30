/*
    Devon Webb CSCI 41
    lab_2.cpp
*/

#include <iostream>
#include <cmath>
#include <cassert>

using namespace std;

class Array {
public:
    Array(); //default constructor for the class
    ~Array(); //destructor
    int GetSize(); //Accessor: Retrieve the size of the array
    void AddToBeginning(double); //function to add an element at the beginning
    void AddToEnd(double); //function to add an element at the end
    void RemoveFromBeginning(); //function to remove an element at the beginning
    void RemoveFromEnd(); //function to remove an element at the end
    void DisplayArray(); //display the content of the array
    bool Search1(double); //iterative search with a for loop
    bool Search2(double); //iterative search with a while loop
    bool Search3(double); //iterative search with a do while loop
    bool Search4(double, int); //recursive search
    bool IsAllEven1(); //iterative function with a for loop
    bool IsAllEven2(); //iterative function with a while loop
    bool IsAllEven3(); //iterative function with a do while loop
    bool IsAllEven4(int); //recursive function
    Array IndexEqualToX(double); //function to return an object Array containing all elements equal to x.
    void SwapAllElements(double, double); //function to swap all elements equal to the value x to the value y.
    void RemoveAll(double); //function to
protected:
private:
    int sizeOfArray; //array size
    double* arrData; //double array
};

// Default Constructor for the class
Array::Array()
{
    sizeOfArray = 0;
    arrData = nullptr;
}

// Destructor for the class
Array::~Array()
{
    delete[] arrData;
}

// Accessor: Function to retrieve the size of the array
int Array::GetSize()
{
    return sizeOfArray;
}

//Function to insert an element to the beginning of the array
void Array::AddToBeginning(double element)
{
    double* temp = new double[sizeOfArray + 1];
    temp[0] = element;
    for (int i = 0; i < sizeOfArray; i++)
    {
        temp[i + 1] = arrData[i];
    }
    arrData = temp;
    sizeOfArray++;
}

//function to insert an element to the end of the array
void Array::AddToEnd(double element)
{
    double* temp = new double[sizeOfArray + 1];
    for (int i = 0; i < sizeOfArray; i++)
    {
        temp[i] = arrData[i];
    }
    temp[sizeOfArray] = element;
    arrData = temp;
    sizeOfArray++;
}

//function to remove an element at the beginning of the array
void Array::RemoveFromBeginning()
{
    double* temp = new double[sizeOfArray - 1];
    for (int i = 0; i < sizeOfArray - 1; i++)
    {
        temp[i] = arrData[i + 1];
    }
    arrData = temp;
    sizeOfArray--;
}

//function to remove an element at the end of the array
void Array::RemoveFromEnd()
{
    double* temp = new double[sizeOfArray - 1];
    for (int i = 0; i < sizeOfArray - 1; i++)
    {
        temp[i] = arrData[i];
    }
    arrData = temp;
    sizeOfArray--;
}

void Array::DisplayArray() // Function to Display the content of the array
{
    cout << endl;
    for (int i = 0; i < sizeOfArray; i++)
    {
        cout << *(arrData + i) << " ";
    }
    cout << endl;
}

//iterative search with a for loop
bool Array::Search1(double x) {
    bool contains_x = false;
    for ( int i = 0; i < this->GetSize(); i++ ) {
        if ( this->arrData[i] == x ) {
            contains_x = true;
        }
    }
    
    return contains_x;
}

//iterative search with a while loop
bool Array::Search2(double x) {
    bool contains_x = false;
    unsigned int i = 0;
    while ( i < this->GetSize() ) {
        if ( this->arrData[i] == x ) {
            contains_x = true;
        }
        i++;
    }
    
    return contains_x;
}

//iterative search with a do while loop
bool Array::Search3(double x) {
    bool contains_x = false;
    unsigned int i = 0;
    do {
        if ( this->arrData[i] == x ) {
            contains_x = true;
        }
        i++;
    } while ( i <= this->GetSize() );
    
    return contains_x;
}

//recursive search
bool Array::Search4(double x, int index) {
    bool contains_x = false;
    if ( index < this->GetSize() ) {
        if ( this->arrData[index] == x ) { // Base case
            contains_x = true;
        } else {  // Recursive case
            contains_x = Search4( x, index + 1 );
        }
    }
    return contains_x;
}

//iterative function with a for loop
bool Array::IsAllEven1() {
    bool isAllEven = true;
    for ( int i = 0; i < this->GetSize(); i++ ) {
        if ( int(this->arrData[i]) % 2 > 0.001 ) {
            isAllEven = false;
        }
    }
    return isAllEven;
}

//iterative function with a while loop
bool Array::IsAllEven2() {
    bool isAllEven = true;
    unsigned int i = 0;
    while ( i < this->GetSize() ) {
        if ( int(this->arrData[i]) % 2 > 0.001 ) {
            isAllEven = false;
        }
        i++;
    }
    
    return isAllEven;
}

//iterative function with a do while loop
bool Array::IsAllEven3() {
    bool isAllEven = true;
    unsigned int i = 0;
    do {
        if ( int(this->arrData[i]) % 2 > 0.001 ) {
            isAllEven = false;
        }
        i++;
    } while ( i <= this->GetSize() );
    
    return isAllEven;
}

//recursive function
bool Array::IsAllEven4(int index) {
    bool isAllEven = true;
    if ( index < this->GetSize() ) {
        if ( int(this->arrData[index]) % 2 > 0.001 ) { // Base case
            isAllEven = false;
        } else {  // Recursive case
            isAllEven = IsAllEven4( index + 1 );
        }
    }
    return isAllEven;
}

//function to return an object Array containing all elements equal to x.
Array Array::IndexEqualToX(double x) {
    Array array;
    for ( int i = 0; i < this->GetSize(); i++ )
    {
        if ( this->arrData[i] == x)
        {
            array.AddToEnd(i);
        }
    }
    
    return array;
}

//function to swap all elements equal to the value x to the value y.
void Array::SwapAllElements(double x, double y) {
    for ( int i = 0; i < this->GetSize(); i++ ) {
        if ( this->arrData[i] == x) {
            this->arrData[i] = y;
        } else if ( this->arrData[i] == y) {
            this->arrData[i] = x;
        }
    }
}

//function to remove all the elements equal to a particular value
void Array::RemoveAll(double x) {
    for ( int i = 0; i < this->GetSize(); i++ )
    {
        if ( this->arrData[i] == x ) // Recursive case if true
        {
            if ( i == 0 ) { // If i is 0, can just remove the element using RemoveFromBeginning
                this->RemoveFromBeginning();
                RemoveAll(x);
            } else // Else need to shift elements over and remove final element
            {
                for ( int j = this->GetSize( ) - 1 ;
                      j > i ; j-- ) // Shifts values from end of array down by one up to index i
                {
                    if ( j >= 1 )
                    {
                        this->arrData[j - 1] = this->arrData[j];
                    }
                }
                this->RemoveFromEnd( );
                RemoveAll(x); // Calls recursively since array size has now changed so the calls to this->GetSize() are no longer accurate
            }
        }
    }
}

int main()
{
    
    return 0;
}