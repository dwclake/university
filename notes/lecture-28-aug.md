# Lecture 28 - Aug - 2023
---
### Number Conversions
<pre>
0x17 = 0001 1000
       1110 0111 : one's complement
       1110 1110 : two's complement

0d17 = 0001 0001
       1110 1110 : one's complement
       1110 1111 : two's complement

0d17 = 0x11 
        100
       - 11
       ----
         EF
</pre>

$not(x) + 1 + x = 0$: two's compliment + original number = 0

00101101 - first digit represents sign (0+/1-)

In hex, 0-7 for most significant digit is positive, 8-F is negative

<pre>
A015 - 0000A015, sign changes based on the size it is stored in
 (-)      (+)
</pre>

In one byte, the range of signed values is +127...-128

$2^n - 1$: the max signed value which can be stored in a give number of bytes

<pre>
    10110110
  - 01010010
  ----------
    01100100

borrowing a 1 in binary gives you 2, so 10 - 01 = 01
</pre>

---
### Overflow

Occurs if adding two positive numbers results in a negative number, or
    when adding two negative numbers results in a positive number
Occurs when there is a carry-in to the sign position but not a carry-out

Adding a positive and a negative number never results in overflow

---
