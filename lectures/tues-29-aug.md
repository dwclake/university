# Tues - 29 - Aug - 2023
---
### Complexity

- Asymptotic notation
    - Θ Big theta - Asymptotically tight bound
    - O Big O - Asymptotic upper bound
    - o Little O - upper bound not asymptotically tight
    - ω Little Omega - lower bound not asymptotically tight
- Used to compare the performance of algorithms

---
### Different cases

- Best case: inputs already sorted
- Worst case: inputs were in reverse order
- Average case: inputs unsorted
- FOCUS ON THE WORST CASE
    - The longest running time for any input size
    - knowing it provides a guarantee that the algorithm will never take any longer!

---
### Asymptotic Notations

- Worst case T(n)

---
### Big Θ Notation

- gives upper and lower bounds
- f(n) = O($n^2$)
- 2n^2 <= 2n^2 + n <= 3n^2

- 1 < log(n) < n < n^2 < n^3
- f(n) = 2n^2 + n + 100
- c_1 n^2 <= 2n^2 + n + 100 <= c_2 N^2
- 2n^2 + n + 100 <= 2n^2 + n^2 + 100n^2
- 2n^2 <= 2n^2 + n + 100 <= 103n^2
- 2 <= 2 + 1 + 100 <= 103
- 2 <= 103 <= 103
- bound from above and below
    - Check if sorted, n^2 sort, linear search

---
### Big O Notation

- asymptotic upper bound
- f(n) = 3n^3 + 10
- 0 <= 3n^3 + 10 <= c g(n)
- 0 <= 3n^3 + 10 <= 3n^2 + 10n^3
- 0 <= 3n^3 + 10 <= 13n^3 <= 13n^6

---
### Small o Notation

- Big O: there exists c > 0
- Small o: for each c > 0
- the limit to ∞ of f(n)/g(n) = 0
- f(n) = 2n
- 0 <= 2n < c n^2

---
### Small omega Notation

- limit to infinity of f(n)/g(n) = infinity
- 0 <= c g(n) < f(n)

---
### Comparison of Functions


---
### Big O of T(n) = 5n^3 + 5n^2 + 10

<pre>
5n^3 + 5n^2 + 10 <= 5n^3 + 5n^3 + 10
5n^3 + 5n^2 <= 10n^3
O(?)
</pre>

---

<pre>
2^n = 2 x 2 x 2 x 2 x 2 ... x 2
n! = 1 x 2 x 3 x 4 x 5 ... n
limit of f(n)/g(n) = 0, so 2^n = n!
</pre>

### Recursion
---
