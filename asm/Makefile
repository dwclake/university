applesilicon: applesilicon.o
	ld -o applesilicon applesilicon.o -e _start \
  && rm applesilicon.o

applesilicon.o: applesilicon.asm
	as -gdwarf-5 applesilicon.asm -o applesilicon.o
