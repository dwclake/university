# Thurs 7 Sept 2023
---
###
- O(1) - executes in the same time regardless of input size
- O(n) - execution time grows linearly
- O(n^2) - execution time grows proportional to the input size squared
- O(logn) - recursion
---
### Masters theorem
- a = # of recursive calls in the body of the function
- b = how the size changes each recursive call
- fn = the non-recursive portion of the body of the function
---
### Time measurements in C++
- Mean time is not enough, must use statistical analysis
- 1/Theory: complexity
- 2/Practise: simulations
    - run n trials with both algorithms
- Statistical evaluation
    - Rigorous
    - Standard deviation
---
### Timer solutions
- RDTSC instruction
- std::chrono
- chrono::high_resolution_clock

```cpp
auto start = std::chrono::high_resolution_clock::now();
...
auto end = std::chrono::high_resolution_clock::now();
std::chrono::duration<double, milli> duration_ms = t2 - t1;
std::cout << duration_ms.count() << std::endl;
```
---
### Multiple returns
- struct
- class
- tuple
---
### Divide & Conquer
- Subarray problem
- Find Max subarray of size s_n in an array of size n
    - s_n <= n
    - 3 cases:
        - lo-mid
        - crosses mid
        - mid-hi
    - Any subarray of A[lo..hi] crossing the midpoint comprises 2 subarrays
        - A[i..mid]
        - A[mid+1..j]
    - For -infinity -INT_MAX
```cpp

```
---
