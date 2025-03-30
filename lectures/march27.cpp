//  March 27, review
//
//  Quicksort partition:
//
//      partition(pivot) {
//          do {
//              i++;
//          } while(pivot < a[i]);
//          do {
//              j--;
//          } while(pivot >= a[j]);
// 
//          if (i < j) {
//              swap(a[i], a[j]);
//          }
//
//          swap(a[i], pivot);
//      }
//
//  Recurrence relations:
//
//  T(n) = 4T(n/4) + n
//
//     n=4^k
//
//     T(n/4) = 4T(n/16) + (n/4)
//     T(n/4^2) = 4T(n/4^3) = n/4^2   
//     step 2:
//          T(n) = 4[4T(n/4^2) + n/4] + n
//               = 4^2T(n/n^2) + 2n
//     step 3:
//          T(n) = 4^2[4T(n/4^3) + n/4^2] + 2n
//               = 4^3[T(n/4^3)] + 3n
//     step k:
//          4^k(T(n/4^k)) + kn
//          nT(1) + kn
//          n + k(n)
//          n(1+K)
//          n(1 + logn)
//          nlogn
//
//      O(nlogn)
