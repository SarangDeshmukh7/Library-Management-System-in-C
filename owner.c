#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

void owner_area(user_t *u) {
	int choice;
	do {
		printf("\n\n0. Sign Out\n1. Appoint Librarian\n2. Edit Profile\n3. Change Password\n4. Fees/Fine Report\n5. Book Availability\n6. Book Categories/Subjects\nEnter choice: ");
		scanf("%d", &choice);
		switch(choice) {
			case 1: // Appoint Librarian
				appoint_librarian();
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
		}
	}while (choice != 0);	
}

void appoint_librarian() {
	// input librarian details
	user_t u;
	user_accept(&u);
	// change user role to librarian
	strcpy(u.role, ROLE_LIBRARIAN);
	// add librarian into the users file
	user_add(&u);
}


