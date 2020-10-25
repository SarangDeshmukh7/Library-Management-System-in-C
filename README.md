# Mini-Project / Case-Study

## Goals
* Gain programming confidence

# Library Management

* Documentation:
	* https://gitlab.com/nilesh-g/library-management

* Understanding design of project


## Code Compilation

### Compiling files individually
	* gcc -c main.c ==> main.o
	* gcc -c member.c ==> member.o
	* gcc -c librarian.c ==> librarian.o
	* gcc -c owner.c ==> owner.o
	* gcc -o library.exe main.o member.o librarian.o owner.o

### Compiling all files together
	* gcc -o library.exe main.c member.c librarian.c owner.c date.c common.c

## GIT steps

### Create repository on gitlab.com

### Clone that repository in some folder on your computer.
* git clone https://gitlab.com/your-userid/your-project.git

### Commit Steps
* step 1: go to the directory in which source code is kept.
* step 2: open gitbash there
* step 3: (staging) -- git add .
* step 4: (commit) -- git commit -m "skeleton code"
* step 5: (push code) -- git push -u origin master

