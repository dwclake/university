bit: bit.o
	@ld -o bit bit.o -nostdlib -e _start \
  && rm bit.o

bit.o: bit.asm
	@nasm -felf64 -gdwarf -l bit.lst bit.asm
