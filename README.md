# Mini-Project / Case-Study

## Goals
* Gain programming confidence
* Practice multiple file handling

## Workflow
- This is console based menu-driven application. Based on user login appropriate menu will be
visible.
- Each book can have multiple copies and organized into multiple racks.
- Issue/return of individual copy is expected. For example, if “C Programming Language (by
Ritchie)” have 10 copies, each copy can be issued and returned independently.
- Book can be issued if and only if user is paid user. Otherwise error message will be displayed.
Payment of each user will be collected by Librarian on monthly basis.
- Book is expected to return in 7 days. If delayed, fine of Rs. 5/- is applicable and should be
taken by Librarian while returning book.

## Technologies & tools
- Programming language: C
- Database: File-IO
- IDE: Eclipse or VIM or any other IDE


## Code Compilation

### Compiling files individually
	* gcc -c main.c ==> main.o
	* gcc -c member.c ==> member.o
	* gcc -c librarian.c ==> librarian.o
	* gcc -c owner.c ==> owner.o
	* gcc -o library.exe main.o member.o librarian.o owner.o

### Compiling all files together
	* gcc -o library.exe main.c member.c librarian.c owner.c date.c common.c
