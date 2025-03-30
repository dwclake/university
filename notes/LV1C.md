# Character Codes: 27 - Aug - 2023
---
### ASCII

Represent characters with a single byte, only using the 7 lowest order bits<br/>
Based on telecommunications codes (Telex)

Details:
- "A" is at $41_{16}$
- "a" is at $61_{16}$
- "0" is at $30_{16}$
- "5" is at $35_{16}$, subtract $30_{16}$ to get number from character
- whitespace code $20_{16}$
- backspace code $08_{16}$
- CR ($OD_{16}$) & LF ($0A_{16}$) together create line break

---
### Unicode

Represent characters with multiple bytes, to additionally allow for 
a wide variety of non-latin characters

Details:
- Assigns a code to every character and symbol in every language in the world
- Provides a unique number for every character no matter the platform program or language
- UTF-8
    - 1...4 bytes
    - backwards compatible with ASCII
    - preferred for e-mail and websites
- UTF-16
    - 2/4 bytes long
    - used in major OS / environments, windows, java, .net
- UTF-32
    - Always uses 4 bytes, fixed width

---
### BCD: Binary Coded Decimal

Each character represented using 4 bits, only supporting decimal characters<br/>
Based on punched card codes

---
### EBCDIC: Extended BCD

Supports BCD + upper and lower case alphabetic characters<br/>
Still in use by IBM mainframes today

---
### 

Contents in memory are TYPE less. A byte in memory might be
- a character
- a number
- a symbol
- a special character
- portion of a multi-byte integer in big or little endian
- part of a multi-byte floating point number

---
