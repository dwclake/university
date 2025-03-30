# Tues 26 Sept 2023
---
## Skip list
space complexity n^2
```zig
pub fn Node(comptime t: type): type { 
  return struct {
    data: t,
    array: Node**, // an array of pointers, points to each element in the list
    size: usize,
    max_levels: usize
  }
};
```
```odin
Node :: struct {
  data: int,
  array: [^]Node,
  size: int
}
```
```rust
struct Node<t> {
  data: isize,
  array: Box<[Node<t>]>,
  size: int
};
```
- Start with sorted linked list
  - Add another layer linking every other element
  - Repeat for that layer
- Hierarchy of sorted linked lists
  - Base: all elements are connected
- Skip list = sorted linked list with shortcuts
---
## Perfect skip list
- We start with a normal linked list
- Then
  - every other node in level 0 is added to level 1
  - every other node in level 1 is added to level 2
  - every other node in level 3 is added to level 3
- O(log2(n)) levels
- Why
  - At each level we visit at most 2 nodes
  - There are O(2 * log(n)) levels = O(log(n))
- Keys in sorted order, O(log(n))
- like a binary tree with all elements at a given level pointing to each other
---
## Random skip list
- Use randomization to promote a node to some level i
- 50% chance
- we expect 1/2 of the elements to be promoted to the next level(included in the next level)
---
