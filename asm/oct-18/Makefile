procedures: procedures.o
	@ld -o procedures procedures.o -nostdlib -e _start \
  && rm procedures.o

procedures.o: procedures.asm
	@nasm -felf64 -gdwarf -l procedures.lst procedures.asm
