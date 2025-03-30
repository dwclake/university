# Tue 19 Sept 2023
---
## Stack
- Add to the "top", remove from the "top"
- FILO, first in last out
---
```zig
pub fn Node(comptime t: type) type {
  return struct {
    const Self = @This();
    const t = t;
    next: *Self,
    value: t,
    prev: *Self,

    pub fn new(value: t) *Self {

    }
  }
}

pub fn Stack(comptime t: type) type { 
  return struct {
    const Self = @This();
    const t = t;

    alloc: std.mem.Allocator,
    head: *Node,
    size: usize,

    pub fn init(self: *Self, alloc: std.mem.Allocator) void {
      self.alloc = alloc;
      self.size = 0;
      self.head = undefined;
    }

    pub fn pop(self: *Self) t {
      
    };

    pub fn push(self: *Self) t {

    };
  }
};
```
---
## Queue
- instead of shifting, which is O(n), can shift index used as head after removing element
- enqueue
- dequeue
- displayqueue - only elements currently being used
- displayall - all elements even those not being used
- int front, rear, size
---
## List
- single
- double
- circular
- skip
---
## Array
- doubling the capacity of array when needed means on average insertion is O(1)
- check if size is half of less of capacity, lower capacity
---
## List vs Array
- arrays are static data structures
- lists are dynamic data structures, can allocate memory element by element
---
```cpp
List::~List() {
  Node* current = head;

  while (current) {
    Node* next = current->next;

    delete current;
    current = next;
  }
}
```
