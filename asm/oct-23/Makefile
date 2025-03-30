procedures2: procedures2.o
	@ld -o procedures2 procedures2.o -nostdlib -e _start \
  && rm procedures2.o

procedures2.o: procedures2.asm
	@nasm -felf64 -gdwarf -l procedures2.lst procedures2.asm
