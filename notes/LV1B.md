# Memory Basics : 26 - Aug - 2023

- A single byte of memory holds 8 binary digits (bits)
- Each byte of memory had it's own address
- A 32-bit CPU can address $2^{32}$ or 4 gigabytes of memory (RAM) 
- A 64-bit CPU can address $2^{64}$ bytes of memory (RAM)

---
### Random Access Memory (RAM)

- Like a large array of bytes
- Data stored in a byte is **not typed**
- Programmer must remember to use the appropriate type while using such data
- Can access any byte ramdomly, doesn't have to be searched sequentially. Like indexing into an array<br/>
<pre>
| Addr | Byte     | Hex |
|------|----------|-----|
| 2034 | 01001001 | 49  |
| 2035 | 00111001 | 39  |
| 2036 | 01101001 | 69  |
| 2037 | 00011001 | 19  |
|------|----------|-----|
</pre>

---
### Contents in a Byte

<pre>
| Base | Min value       | Max value       |
| ---- | --------------- | --------------- |
| Oct  | 0     0     0   | 3     7     7   | 
| Bin  | 0 0 0 0 0 0 0 0 | 1 1 1 1 1 1 1 1 |
| Hex  |    0       0    |    F       F    |
| Dec  |        1        |       255       |
| ---- | --------------- | --------------- |
# Highest order in octal only has access to 2 bits
</pre>

---
### Storage format

Byte ordering, or endianness
  - Big endian (MIPS): Bytes are stored in order as they would be read by a person 
    - 0000 1000 is stored as 0000 1000
  - Little endian (Intel x86): Bytes are stored in the opposite order
    - 0000 1000 is stored as 1000 0000
  - In either case, the order of bits inside the byte does not change
  - Architecture dependent
  - Only for numbers, everything else will be big endian

Benefits
  - Big endian:
    - More natural
    - Sign of number can be determined by looking at address offset 0
    - Strings and integers are stored in the same order
  - Little endian
    - Easier to place values on non word boundaries
    - Conversion from 16-bit integer address to a 32-bit integer address does not require any arithmetic
---