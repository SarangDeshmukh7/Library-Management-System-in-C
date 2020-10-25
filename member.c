#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

void member_area(user_t *u) {
	int choice;
	char name[80];
	do {
		printf("\n\n0. Sign Out\n1. Find Book\n2. Edit Profile\n3. Change Password\n4. Book Availability\n5. Issued Books\nEnter choice: ");
		scanf("%d", &choice);
		switch(choice) {
			case 1: // Find Book
				printf("Enter book name: ");
				scanf("%s", name);
				book_find_by_name(name);
				break;
			case 2:
				break;
			case 3:
				break;
			case 4: // Book Availability
				bookcopy_checkavail();
				break;
			case 5: // List issued books
				display_issued_bookcopies(u->id);
				break;
		}
	}while (choice != 0);	
}

void bookcopy_checkavail() {
	int book_id;
	FILE *fp;
	bookcopy_t bc;
	int count = 0;
	// input book id
	printf("enter the book id: ");
	scanf("%d", &book_id);
	// open book copies file
	fp = fopen(BOOKCOPY_DB, "rb");
	if(fp == NULL) {
		perror("cannot open bookcopies file.");
		return;
	}

	// read bookcopy records one by one
	while(fread(&bc, sizeof(bookcopy_t), 1, fp) > 0) {
		// if book id is matching and status is available, count the copies
		if(bc.bookid == book_id && strcmp(bc.status, STATUS_AVAIL)==0) {
		//	bookcopy_display(&bc);
			count++;
		}
	}
	// close book copies file
	fclose(fp);
	// print the message. 
	printf("number of copies availables: %d\n", count);
}
