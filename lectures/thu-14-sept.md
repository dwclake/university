# Thur 14 Sept
---
##
```cpp
int main() {
  std::printf("%s\n", __func__); // Prints the name of current function, like __MODULE__ in elixir
}
```
---
## Merge sort
```cpp
int* merge(int* a1, int* a2, int n1, int n2) {
  int n3 = n1 + n2;
  int* tmp = new int[n3];

  int i1{0}, i2{0}, i3{0};

  do {
    if ( a1[i1] < a2[i2] ) {
      tmp[i3] = a1[i1];
      i1++;
    } else {
      tmp[i3] = a2[i2];
      i2++;
    }

    i3++;

  } while ( i1 < (n1 - 1) && i2 < (n2 - 1) );

  while ( i1 < n1 ) {
    tmp[i3] = a1[i1];
    i1++;
  };

  while ( i2 < n2 ) {
    tmp[i3] = a2[i2];
    i2++;
  };

  return tmp;
}
```
```cpp
void merge_sort (int* a, int start, int end) {
  if ( start < end ) {
    int mid = ( end + start ) / 2;

    merge_sort(a, start, mid);
    merge_sort(a, mid + 1, end);

    merge(a, start, mid, end);
  }
}

void MyArray::MergeSort() {
  step = 0;
  merge_sort(this->a, 0, n-1);
  DisplayStep(__func__);
}

// Masters theorem: a=2 b=2, c=log_2(2) = 1 n = n^2 => case 2: O(nlogn)

void merge(int* a, int start, int mid, int end) {
  int n1 = mid - start + 1;
  int n2 = end - mid;
}
```
---
## Quick sort
O(nlogn)
- pivot:
  - could pick first element, last element, middle element
  - first element not normally recommended
  - ideally should pick the middle element as the pivot
```cpp
quicksort(int[] a, int p, int r) {
  if ( p < r ) {
    pivot = partition(a, p, r);
    quicksort(a, p, pivot - 1);
    quicksort(a, pivot + 1, r);
  }
}
```
---
