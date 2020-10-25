#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"
#include "date.h"

void date_tester() {
	date_t d1 = {1, 1, 2000}, d2 = {31, 12, 2000};
	date_t d = {1, 1, 2000};
	date_t r = date_add(d, 366);
	date_print(&r);
	int diff = date_cmp(d1, d2);
	printf("date diff: %d\n", diff);
}

void tester() {
	user_t u;
	book_t b;
	user_accept(&u);
	user_display(&u);
	book_accept(&b);
	book_display(&b);
}

void sign_in() {
	char email[30], password[10];
	user_t u;
	int invalid_user = 0;
	// input email and password from user.
	printf("email: ");
	scanf("%s", email);
	printf("password: ");
	scanf("%s", password);
	// find the user in the users file by email.
	if(user_find_by_email(&u, email) == 1) {
		// check input password is correct.
		if(strcmp(password, u.password) == 0) {
			// special case: check for owner login
			if(strcmp(email, EMAIL_OWNER) == 0)
				strcpy(u.role, ROLE_OWNER);

			// if correct, call user_area() based on its role.
			if(strcmp(u.role, ROLE_OWNER) == 0)
				owner_area(&u);
			else if(strcmp(u.role, ROLE_LIBRARIAN) == 0)
				librarian_area(&u);
			else if(strcmp(u.role, ROLE_MEMBER) == 0)
				member_area(&u);
			else
				invalid_user = 1;
		}
		else
			invalid_user = 1;
	}
	else
		invalid_user = 1;

	if(invalid_user)
		printf("Invalid email, password or role.\n");
}

void sign_up() {
	// input user details from the user.
	user_t u;
	user_accept(&u);
	// write user details into the users file.
	user_add(&u);
}

int main() {
//	date_tester();
//	tester();
	int choice;
	do {
		printf("\n\n0. Exit\n1. Sign In\n2. Sign Up\nEnter choice: ");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1: // Sign In
			sign_in();
			break;
		case 2:	// Sign Up
			sign_up();	
			break;
		}
	}while(choice != 0);
	return 0;
}

