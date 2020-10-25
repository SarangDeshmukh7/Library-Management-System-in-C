# Mini-Project / Case-Study

## Goals
* Gain programming confidence

## Code Compilation

### Compiling files individually
	* gcc -c main.c ==> main.o
	* gcc -c member.c ==> member.o
	* gcc -c librarian.c ==> librarian.o
	* gcc -c owner.c ==> owner.o
	* gcc -o library.exe main.o member.o librarian.o owner.o

### Compiling all files together
	* gcc -o library.exe main.c member.c librarian.c owner.c date.c common.c
