# Thurs 28 Sept 2023
---
## Hash maps
```cpp
void count_letters(char* s, int n) {
  int letters[26];

  for (int i = 0; i < 26; i++) {
    letters[i] = 0;
  }
  
  for (int i = 0; i < n; i++) {
    int index = s[i] - 'a';
    letters[index]++;
  }
}
```

- Fast insertion
- Fast searching
- Insertion and search take close to O(1)
- Higher space complexity than array

---
## Hashing
- Convert key into address
- Accomplished using a hashing function

---
## A Dictionary
- 50,000 words
- Adding the chars, not discriminate enough, not enough elements
- Multiplying by powers
  - assigns an array element to every potential word
    - cells for aaaaaaaaaaaa, ..., zzzzzzzzzzz
  - Only small fraction of cells are necissary for real words
  - most array cells are empty

---
## Hashing
- Need an array roughly twice the number of cells
  - 100,000 elements
- Divide string into individual characters
- convert each word into hugeNumber by multiplying each char by an appropriate power of 27
- arraySize = numberWords * 2;
- arrayIndex = hugeNumber % arraySize;

---
## Collisions
---
## Separate Chaining
- each index stores a list, collisions are added to the list
- Many indices may be empty

---
## Open Addressing
Make use of unused space, find empty spot increasing idx and taking the remainder with size
- Linear Probing - search sequentially for vacant cells, causes clustering
- Quadratic Probing - increase idx + (collision number)^2, less clustering
- Double Hashing

---
## Linear Probing
- Must ensure no spaces between elements with the same hashed index
---
## Quadratic Probing
---
