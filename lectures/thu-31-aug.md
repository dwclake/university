# 30 - Aug - 2023
---
### Recursion in mathematics

- n: Natural number
- P: logical proposition

- Base case
    - P(n_0): true
- Inductive hypothesis
    - P(n): true
- Inductive step
    - P(n): true ->(implies) P(n+1) true for all n > n_0
---
### Recursion
<pre>
P(n): sum(0->n) of 2^i = 2^{n+1} - 1
- Base case
    - n_0 = 0: P(0): sum(0) of = 0 = 2^0 - 1 
- Hypothesis
    - P(n): true
    - P(n) implies P(n+1) for all n >= n_0
- ???
    - P(n+1) sum(0->n+1) of 2^i = 2^{n+1+1} - 1
    - sum = 2^0 + 2^1 + 2^3 ... + 2^n + 2^{n+1}
    - sum(0->n) of 2^i + 2^{n+1}
    - 2^{n+1} - 1 + 2^{n+1}
    - 2(2^{n+1}) - 1 = 2^{(n+1) + 1} - 1
</pre>
---
<pre>
n^3 - n
p(1) = 1 - 1 = 0 = 0 x 3
p(2) = 8 - 2 = 6 = 2 x 3
p(3) = 27 - 3 = 24 = 8 x 3

hypo: assume P(n): true, n^3 - n is divisable by three

show P(n+1) is true, can be divided by three
P(n+1): (n+1)^3 - (n + 1)
    (n+1)(n+1)^2 - n + 1
    (n+1)(n^2 + 2n + 1) - n - 1
    n^3 + 2n^2 + n + n^2 + 2n + 1 -n - 1
    n^3 + 3n^2 + 2n
    n^3 + 3n^2 +3n - n
    (n^3 - n) + 3(n^2 + n)
    3k + 3(n^2 + n)
    3(k + n^2 + n)
    can be divided by three
</pre>
---
<pre>
prove 2^n < n! for all n >= 4
P(4): 16 < 24
P(n): true
P(n+1): 2^{n+1} < (n+1)! && 2^1/n! < 1
        2^{n+1} < (n+1)(n!)
        2^{n+1}/(n+1)! = (2^n * 2)/n! * (n+1)
                         (<1) * (<1)
                         < 1
</pre>
---
### Explanation
---
### Factorial
<pre>
N! = N * (N-1) * (N-2) ... 3 * 2 * 1
</pre>
```cpp
int factorial(int n) {
    int result{1};

    if ( n <= 1 ) return result;

    do {
        result *= n--;
    } while ( n > 0 );

    return result;
}

int factorial(int n, int acc = 1) {
    if ( n <= 1 ) return 1;
    acc *= n;
    return factorial(--n, acc);
}

int factorial(int n) {
    return ( n <= 1 )? 1 : n * factorial(--n);
}
```
<pre>
    f(n) = sum(1->n) of i
    f(n+1) = sum(1->n+1) of i = sum(1->n) of i * (n+1)
</pre>
---
### Anagrams 
- (ABC) anagrams
    - ABC
    - ACB
    - CBA
    - CAB
    - BAC
    - BCA
- Number of anagrams = (n of characters)!
- Assume word has N letters
    - Anagram the N-1 letters
    - Rotate all N letters
    - Repeat N times
```cpp

```
---
### Hanoi tower
- Best case: can put the biggest disk in its final position (n-1 disks left to move)
- 
---
