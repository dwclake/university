/*
 Devon Webb CSCI 41
 lab_5.cpp
*/

#include <iostream>
#include <vector>

using namespace std;

unsigned int factorial_rec(unsigned int n) {
    
    if (n == 0 || n == 1) { // Base case
        return 1;
    } else { // Recursive case
        return n * factorial_rec(n - 1);
    }
}

unsigned int factorial_for(unsigned int n) {
    
    if (n == 0 || n == 1) {
        return 1;
    } else {
        unsigned int result = 1;
        
        for (unsigned int i = n; i > 0; i--) {
            result *= i;
        }
        return result;
    }
}

unsigned int factorial_while(unsigned int n) {
    
    if(n == 0 || n == 1) {
        return 1;
    } else {
        unsigned int result = 1;
        unsigned int i = n;
        
        while(i > 0) {
            result *= i;
            i--;
        }
        return result;
    }
}

unsigned int fibonacci_rec(unsigned int n) {
    
    if (n == 0) {
        return 0;
    } else if (n == 1 || n == 2) {
        return 1;
    } else {
        return fibonacci_rec(n - 1) + fibonacci_rec(n - 2);
    }
}

unsigned int fibonacci_for(unsigned int n) {
    unsigned int first_term{ 0 };
    unsigned int second_term{ 1 };
    unsigned int next_term{ 0 };
    
    if (n == 0) {
        return first_term;
    } else if (n == 1 || n == 2) {
        return second_term;
    } else {
        for (int i = 1; i < n; i++) {
            next_term = first_term + second_term;
            first_term = second_term;
            second_term = next_term;
        }
    }
    
    return next_term;
}

unsigned int fibonacci_while(unsigned int n) {
    unsigned int first_term{ 0 };
    unsigned int second_term{ 1 };
    unsigned int next_term{ 0 };
    
    if (n == 0) {
        return 0;
    } else if (n == 1 || n == 2) {
        return 1;
    } else {
        unsigned int i = 1;
        while (i < n) {
            next_term = first_term + second_term;
            first_term = second_term;
            second_term = next_term;
            i++;
        }
    }
    
    return next_term;
}

void hanoi_tower_rec(int n, vector<int> &a, vector<int> &b, vector<int> &c) {
    if (n == 1) {
        c.push_back(a.back());
        a.pop_back();
        return;
    }
    hanoi_tower_rec(n - 1, a, c, b);
    
    c.push_back(a.back());
    a.pop_back();
    
    hanoi_tower_rec(n - 1, b, a, c);
}

void hanoi_tower_non_rec(int n) {

}

int main() {
    
    for (unsigned int i = 0; i <= 5; i++) {
        cout << "factorial using recursion  with i= " << i << " is: " << factorial_rec(i) << endl;
        cout << "factorial using for loop   with i= " << i << " is: " << factorial_for(i) << endl;
        cout << "factorial using while loop with i= " << i << " is: " << factorial_while(i) << endl << endl;
    }
    
    for (unsigned int i = 0; i <= 5; i++) {
        cout << "fibonacci term: " << i << endl;
        cout << "for: " << fibonacci_for(i) << endl;
        cout << "while: " << fibonacci_while(i) << endl;
        cout << "rec: " << fibonacci_rec(i) << endl << endl;
    }
    
    vector<int> a{3, 2, 1};
    vector<int> b;
    vector<int> c;
    int n = 3;
    
    hanoi_tower_rec(n, a, b, c);
    
    cout << "Hanoi tower 3rd tower, using recursion: " << endl;
    for (int x: c) {
        cout << x << endl;
    }
}