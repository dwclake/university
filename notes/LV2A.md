# LV2A - Parts of a Computer System - Overview and Memory
---
### Microcomputer - Basic Design
Processor comprised of:
    - A Set of registers
    - I/O Devices
    - Memory Storage
        - Each 'piece' of memory is a byte
        - Each address points to a single byte
    - Clock (keeps 'tempo')
    - ALU (arithmetic/logical unit)
    - CU (control unit)
    - 3 buses
        - Data bus (data being read/written)
        - Control bus (read/write signal, operate I/O devices)
        - Address bus (address to read/write from/to)

---
### Memory

Memory Storage:
    - Holds data and instructions
Bus:
    - A group of parallel wires, used to transfer data through-out computer
    - Data bus - transfers instructions and data between the CPU and memory 
    - Control bus - uses binary signals to synchronize the actions of all devices
    - Address bus - holds the addresses of instructions and data when the currently executing instruction needs to transfer data between the CPU and memory

---
### 80x86 Memory

Collection of 'slots' each of which holds one byte (8 bits/ 2 nibbles).
Each slot identified by an address
    - 32-bit systems use 32-bit addresses
    - 64-bit systems use 64-bit addresses

---
### Memory Addressing

32-bit systems:
    - Address length: 32-bits/4-bytes/8-nibbles
    - Address space: 2^32 = 4 GB
    - Lowest 0x0 (all 0)
    - Highest 0xFFFFFFFF (all 1)

64-bit systems:
    - Address length: 64-bits/8-bytes/16-nibbles
    - Address space: 2^64

---
### Memory Units

- 1 Kb = 2^10 bits = 1024
- 1 Mb = 2^20 bits = 1,048,576
- 1 Gb = 2^30 bits

---
### Memory Types 

- RAM/ROM
    - RAM - Volatile, dead without power
    - ROM - Retains information, read only
- Flat/Segmented
    - Flat - Unique address for each byte
    - Segmented - memory divided into blocks, each addressing from 0x0 to 0xFFFF

---
