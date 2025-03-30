# Number Systems : 26 - Aug - 2023
---

- Binary (0,1)
- Octal (0-7)
- Decimal (0-9)
- Hexadecimal (0-9, A-F)

Radix == Base

---
### Decimal $\rightarrow$ Decimal

<pre>
4053
4 0 5 3
      10^0 | 3 * 10^0 +
    10^1   | 5 * 10^1 +
  10^2     | 0 * 10^2 +
10^3       | 4 * 10^3 = 4053
</pre>
---
### N $\rightarrow$ Decimal

Base: N<br/>
<pre>
pos : 3 2 1 0
      λ γ β α
            N^0 | α * N^0 +
          N^1   | β * N^1 +
        N^2     | γ * N^2 +
      N^3       | λ * N^3
</pre>

- If positions are 0,1,2,3... starting from the right
    - value at position p: $digit \times N^{p}$
---
### $10111_2$ $\rightarrow$ Decimal

<pre>
1 | 1 * 2^4 = 16
0 | 0 * 2^3 = 0
1 | 1 * 2^2 = 4
1 | 1 * 2^1 = 2
1 | 1 * 2^0 = 1
----------------
            = 23
</pre>
---
### $20_{10}$ $\rightarrow$ $N_8$

$$20_{10} \rightarrow N_8$$

$$20 \div 8 = 2 rem 4$$

$$2 \div 8 = 0 rem 2$$

$$20_{10} = 24_8$$
---
### Decimal $\rightarrow$ N Algorithm

```ruby
def decimal_to_n(decimal, base, result = [])
    # Base case
    return result.join if decimal <= 0
    # Calculate quotient and remainder
    quotient = decimal.div base
    rem = decimal.remainder base
    # Prepend result with remainder
    result.unshift rem
    # Recursive call
    decimal_to_n(quotient, base, result)
end
```
---
### Binary $\leftrightarrow$ Hexadecimal

$16 = 2^4$: so 1 Hex digit is 4 bits<br/>
<br/>
$Binary \rightarrow Hexidecimal$:<br/>
    Group binary into nibbles(4 bits), then convert each nibble into a hex digit:<br/>
    10100011 $\rightarrow$ 1010 | 0011 $\rightarrow$ A | 3 $\rightarrow$ A3<br/>
<br/>
$Hexidecimal \rightarrow Binary$:<br/>
    Convert each hex digit into a nibble:<br/>
    2C $\rightarrow$ 2 | C $\rightarrow$ 0010 | 1100 $\rightarrow$ 00101100<br/>

---
### Binary $\leftrightarrow$ Octal

$8 = 2^3$: so 1 Octal digit is 3 bits<br/>
<br/>
$Binary \rightarrow Octal$:<br/>
    Group binary into threes, then convert to octal:<br/>
    10100011 $\rightarrow$ 010 | 100 | 011 $\rightarrow$ 2 | 4 | 3 $\rightarrow$ 243

---
### Higher order units for bits
- Byte: 8 bits
    - typically smallest addressable unit of memory
- Nibble: 4 bits
    - Bytes contain two nibbles, a higher and a lower order nibble
- Word: 16 bits (for x86, depends on architecture)
- Double Word: 32 bits (for x86)
- Quad Word: 64 bits (for x86)
- In a word addressable system, a word not a byte is the smallest addressable unit of memory