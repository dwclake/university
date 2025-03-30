assignment3: assignment3.o
	@ld -o assignment3 assignment3.o -melf_i386 -nostdlib -e _start \
  && rm assignment3.o

assignment3.o: assignment3.asm
	@nasm -felf32 -gdwarf -l assignment3.lst assignment3.asm
