# LV3F - Elements of Assembly Language - Example Macros
---
## Support parameters
atod:
  - ASCII to Decimal
  - Interprets each character as a signed integer

```x86
atod MACRO source
  lea  eax, source ; loads source's address into eax
  push eax         ; source parameter on stack
  call atodproc    ; call atodproc(source)
  add  esp, 4      ; remove parameter
ENDM

dtoa MACRO destination source

ENDM
```
---
