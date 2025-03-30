# Tues 5 Sept 2023
---
### Hanoi Tower

Recursive functions:
- Arrive at a base case, can relate to n

- Try to find steps to get to n-1, those steps can then be repeated until n = 1
- For Hanoi Tower, n-1 is when the biggest (lowest) disk is in the correct position
- step 1: hanoi(n - 1, A, C, B) move all except largest from a to b
- step 2: move largest to c
- step 3: hanoi(n - 1, B, C, A) move all execpt second largest from b to c
---
### Binary Search

- Can return multiple elements using std::pair/std::tuple, or returning void and using pointers/references

```cpp
std::pair<bool, int> binary_search(MyType x) {
    return binary_search_i(a, x, 0, x.size() - 1);
}

std::pair<bool, int> binary_search_i(MyType* a, int x, int low, int high) {
    
    return std::make_pair(true, x);
}

bool a;
int x;
std::pair<bool, int> result = binary_search(...);
bool test = result.first();
int y = result.second();
std::tie(a, x) = binary_search(...);

```
---
### Recursion

- Divide 
- Conquer
- Combine

---
### Recurrences

An equation or inequality describing a function in terms of its value on smaller inputs

---
### Recurrence relations

- Substitution method
- Recursion-tree method
- Masters theorem

- T(n) = aT(n/b) + f(n)

```cpp
void T(int m, int* n, int lo, int hi) {
    int mid = (lo + hi) / 2;

    f(a, lo, mid); // subproblems
    f(a, mid, hi);

    for ( int i = lo; i < hi; i++ ) {
        for ( int j = lo; j < hi; j++ ) {
            std::cout << i * j << std::endl;
        }
    }
}
// a = subproblems = 2
// b = how many times smaller the problem gets each step = 2
// f(n) = the complexity of the non recursive portion of the function = n^2
```
- Three cases of Masters theorem
    - Recursion tree is leaf heavy (aT(n/b) > f(n))
    - Split, same as sub-problems (aT(n/b) = f(n))
    - Root heavy (aT(n/b) < f(n))
- C_(critital exponent) = log_b(a) = log(#sub-problems)/log(relative sub-problem size) = log(a)/log(b)
- C_crit = the exponent required to make b^ccrit = a

---
### Masters theorem: Case 1

- Merge sort: T(n) = 2T(n/2) + n(log(n))

---
###
<pre>
T(n) = 8(n/2) = 1000n^2
a = 8
b = 2
ccrit = 3
f(n) = 1000n^2 = Θ(n^2)

log_2(8) = 3 = ccrit

so first case, because n^ccrit > f(n)

T(n) = Θ(n^3)


(big omega         )
(big theta                    )
            (big o            )
c1 * g(n) < 1000n^2 < c2 * g(n)
500n^2    < 1000n^2 < 1001n^2

</pre>

<pre>
</pre>
---
