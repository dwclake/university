# LV3C - Elements of Assembly Language - Data Declarations
---
## BYTE Directive
- Reserves storage for one or more bytes of data, optionally initializing storage
- Numeric data can be thought of as signed or unsigned
- Characters are assembled to ASCII codes
- Character strings (BYTE directive only)
- Examples 
  - byte1 BYTE 255
  - byte2 BYTE 91
  - byte3 BYTE 0
  - byte4 BYTE -1
  - byte5 BYTE 6 DUP (?) ; 6 bytes each with 0x00, an array
  - byte6 BYTE 'm'
  - byte7 BYTE "Joe" ; 3 bytes with 4A 6F 0x65, an array
---
## DWORD Directive
- Reserves one or more doublewords of data
- double1 DWORD -1 ; FFFFFFFF
- double4 DWORD 0, 1 ; two doublewords, an array
- double5 DWORD 100 DUP (?) ; 100 doublewords, an array
---
##
255 & -1 = 0xFF
---