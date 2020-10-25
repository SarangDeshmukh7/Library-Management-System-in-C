# Mini-Project / Case-Study

## Goals
* Gain programming confidence
* Hands-on with GIT --> Future lab exams

## Not Goals
* Learning C programming

## Execution
* step 1: Discuss design document
* step 2: Coding flow
* step 3: GIT repository
* step 4: Implementing step by step (commit by commit).

### Trainer role
* Guide you for the coding steps & code organization
* Implement major functionalities in the project

### Student role
* Coding: classwork
* Coding: Implement additional functionalities

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

## Homework-1
1. Implement date struct (day, month, year).
	* input and display date.
	* add given days into date.
	* compare two dates - returns number of days.
2. Add members to the struct (refer the document).
3. Revise concept of menu driven program.
	* do-while and switch case.

## Homework-2
1. Implement accept() and display() function for all structures.
2. Add Book, Find Book.

## Homework-3
1. Edit Profile, Change Password
2. Add New Copy, Change Rack

## Homework-4
1. Librarian - Add menu - Display all members
2. Librarian - Fee Payment.


