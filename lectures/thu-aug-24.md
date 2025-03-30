const int* ptr != int* const ptr

const int* ptr -> value behind ptr is immutable, ptr is mutable
int* const ptr -> value behind ptr is mutable, ptr is immutable

const int* const ptr -> all immutable

ptr = 0 = nullptr

ptr can not be null and still point to nothing -> use after free
set ptr to null after freeing


```cpp
bool exists(int x, int* arr, int n) {
    bool found = false;
    int i = 0;

    do {
        found = v[i] == i;
        i++;
    } while ( !found && i < n );

    return found;
}
```
