# Unsigned and Signed Integers: 27 - Aug - 2023
---
### Negative Numbers

How to represent negative numbers?
  - Signed magnitude
  - One's complement
  - Two's complement
  - Excess (biased)

---
### Signed Magnitude

+ve:
- All positions can be used with respective place values
- 00110110
Signed Representation:
- Most significant bit reserved, 1 for -ve 0 for +ve
- All other bit positions can be used with respective place values

---
### One's complement

- flip each bit
- example:
    - 37 = 0010 0101
    - -37 = 1101 1010

---
### Two's complement

- Flip every bit and add 1
- example:
<pre>
    37 = 0010 0101
         1101 1010 one's compliement
       +         1
       -----------
         1101 1011 = -37
</pre>
- in reverse subtract 1 then flip every bit, or do two's compliment again

---
### Excess (biased)

- Add bias to two's complement
- example (8-bit excess 128 (bias/offset)):
<pre>
    37 = 0010 0101
         1101 1010 one's compliment
       +         1
       -----------
         1101 1011 two's compliment
       + 1000 0000
       -----------
     (1) 0101 1011 = -37 (carry is discarded)
</pre>

---
### Convert and Compare

<pre>
signed magnitude:
    123 = 0111 1011
   -123 = 1111 1011
one's compliment:
   -123 = 1000 0100
two's compliment:
   -123 = 1000 0101
excess 128:
   -123 = 0000 0101
</pre>

---
### Picking a format

- To check if negative?
- To check if 0?
- Easy is arithmetic?
- Check for overflow?
- Check if one number is larger than another?
- Implemented in hardware, simpler $\rightarrow$ better

___
### Binary addition (Signed Magnitude)
___
### Binary addition (One's Compliment)
___
### Binary addition (Two's Compliment)
___
### Binary addition (Excess)
___
### x86 Unsigned Representation

- Just binary in one of the standard lengths
- E47A is the word-length unsigned representation for the decimal number 58490

---
### x86 Signed Representation

- Two's compliment used in 80x86
- Will use one of the standard lengths (byte, word, double-word, etc.)
- Highest order bit gives sign (0+/1-)
- For a negative number, you must perform two's compliment to find the positive value

---
### Two's Compliment Operation

- To take in hex 10000 - E47A = 1B86 = 7046 in decimal = -7046
- E = 1110 so negative
- Number to subtract from is 1 followed by 0 (one for each hex digit)

---
### Multiple Interpretations

- The word FE89 can be read as
    - Unsigned 65161
    - Signed -375

---
