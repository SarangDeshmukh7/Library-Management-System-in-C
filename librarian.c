#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

void librarian_area(user_t *u) {
	int choice, memberid;
	char name[80];
	do {
		printf("\n\n0. Sign Out\n1. Add member\n2. Edit Profile\n3. Change Password\n4. Add Book\n5. Find Book\n6. Edit Book\n7. Check Availability\n8. Add Copy\n9. Change Rack\n10. Issue Copy\n11. Return Copy\n12. Take Payment\n13. Payment History\nEnter choice: ");
		scanf("%d", &choice);
		switch(choice) {
			case 1: // Add member
				add_member();
				break;
			case 2:
				break;
			case 3:
				break;
			case 4: // Add Book
				add_book();
				break;
			case 5: // Find Book
				printf("Enter book name: ");
				scanf("%s", name);
				book_find_by_name(name);
				break;
			case 6: // Edit Book
				book_edit_by_id();
				break;
			case 7: // Check Availability
				bookcopy_checkavail_details();
				break;
			case 8: // Add Copy
				bookcopy_add();
				break;
			case 9:
				break;
			case 10: // Issue Book Copy
				bookcopy_issue();
				break;
			case 11: // Return Book Copy
				bookcopy_return();
				break;
			case 12: // Take Payment
				fees_payment_add();
				break;
			case 13: // Payment History
				printf("enter member id of the member: ");
				scanf("%d", &memberid);
				payment_history(memberid);
				break;
		}
	}while (choice != 0);		
}

void add_member() {
	// input member details
	user_t u;
	user_accept(&u);
	// add librarian into the users file
	user_add(&u);
}

void add_book() {
	FILE *fp;
	// input book details
	book_t b;
	book_accept(&b);
	b.id = get_next_book_id();
	// add book into the books file
	// open books file.
	fp = fopen(BOOK_DB, "ab");
	if(fp == NULL) {
		perror("cannot open books file");
		exit(1);
	}
	// append book to the file.
	fwrite(&b, sizeof(book_t), 1, fp);
	printf("book added in file.\n");
	// close books file.
	fclose(fp);
}

void book_edit_by_id() {
	int id, found = 0;
	FILE *fp;
	book_t b;
	// input book id from user.
	printf("enter book id: ");
	scanf("%d", &id);
	// open books file
	fp = fopen(BOOK_DB, "rb+");
	if(fp == NULL) {
		perror("cannot open books file");
		exit(1);
	}
	// read books one by one and check if book with given id is found.
	while(fread(&b, sizeof(book_t), 1, fp) > 0) {
		if(id == b.id) {
			found = 1;
			break;
		}
	}
	// if found
	if(found) {
		// input new book details from user
		long size = sizeof(book_t);
		book_t nb;
		book_accept(&nb);
		nb.id = b.id;
		// take file position one record behind.
		fseek(fp, -size, SEEK_CUR);
		// overwrite book details into the file
		fwrite(&nb, size, 1, fp);
		printf("book updated.\n");
	}
	else // if not found
		// show message to user that book not found.
		printf("Book not found.\n");
	// close books file
	fclose(fp);
}

void bookcopy_add() {
	FILE *fp;
	// input book copy details
	bookcopy_t b;
	bookcopy_accept(&b);
	b.id = get_next_bookcopy_id();
	// add book copy into the books file
	// open book copies file.
	fp = fopen(BOOKCOPY_DB, "ab");
	if(fp == NULL) {
		perror("cannot open book copies file");
		exit(1);
	}
	// append book copy to the file.
	fwrite(&b, sizeof(bookcopy_t), 1, fp);
	printf("book copy added in file.\n");
	// close book copies file.
	fclose(fp);
}

void bookcopy_checkavail_details() {
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
		// if book id is matching and status is available, print copy details
		if(bc.bookid == book_id && strcmp(bc.status, STATUS_AVAIL)==0) {
			bookcopy_display(&bc);
			count++;
		}
	}
	// close book copies file
	fclose(fp);
	// if no copy is available, print the message. 
	if(count == 0)
		printf("no copies availables.\n");
}


void bookcopy_issue() {
	issuerecord_t rec;
	FILE *fp;
	// accept issuerecord details from user
	issuerecord_accept(&rec);
	// if user is not paid, give error & return.
	if(!is_paid_member(rec.memberid)) {
		printf("member is not paid.\n");
		return;
	}
	// generate & assign new id for the issuerecord
	rec.id = get_next_issuerecord_id();
	// open issuerecord file
	fp = fopen(ISSUERECORD_DB, "ab");
	if(fp == NULL) {
		perror("issuerecord file cannot be opened");
		exit(1);
	}
	// append record into the file
	fwrite(&rec, sizeof(issuerecord_t), 1, fp);
	// close the file
	fclose(fp);

	// mark the copy as issued
	bookcopy_changestatus(rec.copyid, STATUS_ISSUED);
}

void bookcopy_changestatus(int bookcopy_id, char status[]) {
	bookcopy_t bc;
	FILE *fp;
	long size = sizeof(bookcopy_t);
	// open book copies file
	fp = fopen(BOOKCOPY_DB, "rb+");
	if(fp == NULL) {
		perror("cannot open book copies file");
		return;
	}

	// read book copies one by one
	while(fread(&bc, sizeof(bookcopy_t), 1, fp) > 0) {
		// if bookcopy id is matching
		if(bookcopy_id == bc.id) {
			// modify its status
			strcpy(bc.status, status);
			// go one record back
			fseek(fp, -size, SEEK_CUR);
			// overwrite the record into the file
			fwrite(&bc, sizeof(bookcopy_t), 1, fp);
			break;
		}
	}
	
	// close the file
	fclose(fp);
}

void display_issued_bookcopies(int member_id) {
	FILE *fp;
	issuerecord_t rec;
	// open issue records file
	fp = fopen(ISSUERECORD_DB, "rb");
	if(fp==NULL) {
		perror("cannot open issue record file");
		return;
	}

	// read records one by one
	while(fread(&rec, sizeof(issuerecord_t), 1, fp) > 0) {
		// if member_id is matching and return date is 0, print it.
		if(rec.memberid == member_id && rec.return_date.day == 0)
			issuerecord_display(&rec);
	}
	// close the file
	fclose(fp);
}

void bookcopy_return() {
	int member_id, record_id;
	FILE *fp;
	issuerecord_t rec;
	int diff_days, found = 0;
	long size = sizeof(issuerecord_t);
	// input member id
	printf("enter member id: ");
	scanf("%d", &member_id);
	// print all issued books (not returned yet)
	display_issued_bookcopies(member_id);
	// input issue record id to be returned.
	printf("enter issue record id (to return): ");
	scanf("%d", &record_id);
	// open issuerecord file
	fp = fopen(ISSUERECORD_DB, "rb+");
	if(fp==NULL) {
		perror("cannot open issue record file");
		return;
	}
	// read records one by one
	while(fread(&rec, sizeof(issuerecord_t), 1, fp) > 0) {
		// find issuerecord id
		if(record_id == rec.id) {
			found = 1;
			// initialize return date
			rec.return_date = date_current();
			// check for the fine amount
			diff_days = date_cmp(rec.return_date, rec.return_duedate);
			// update fine amount if any
			if(diff_days > 0) {
				rec.fine_amount = diff_days * FINE_PER_DAY;
				fine_payment_add(rec.memberid, rec.fine_amount);
				printf("fine amount Rs. %.2lf/- is applied.\n", rec.fine_amount);
			}
			break;
		}
	}
	
	if(found) {
		// go one record back
		fseek(fp, -size, SEEK_CUR);
		// overwrite the issue record
		fwrite(&rec, sizeof(issuerecord_t), 1, fp);
		// print updated issue record.
		printf("issue record updated after returning book:\n");
		issuerecord_display(&rec);
		// update copy status to available 
		bookcopy_changestatus(rec.copyid, STATUS_AVAIL);
	}
	
	// close the file.
	fclose(fp);
}

void fees_payment_add() {
	FILE *fp;
	// accept fees payment
	payment_t pay;
	payment_accept(&pay);
	pay.id = get_next_payment_id();
	// open the file
	fp = fopen(PAYMENT_DB, "ab");
	if(fp == NULL) {
		perror("cannot open payment file");
		exit(1);
	}
	// append payment data at the end of file
	fwrite(&pay, sizeof(payment_t), 1, fp);
	// close the file
	fclose(fp);
}

void payment_history(int memberid) {
	FILE *fp;
	payment_t pay;
	// open file
	fp = fopen(PAYMENT_DB, "rb");
	if(fp==NULL) {
		perror("cannot open payment file");
		return;
	}
	// read payment one by one till eof
	while(fread(&pay, sizeof(payment_t), 1, fp) > 0) {
		if(pay.memberid == memberid)
			payment_display(&pay);
	}
	// close file	
	fclose(fp);
}

int is_paid_member(int memberid) {
	date_t now = date_current();
	FILE *fp;
	payment_t pay;
	int paid = 0;
	// open file
	fp = fopen(PAYMENT_DB, "rb");
	if(fp==NULL) {
		perror("cannot open payment file");
		return 0;
	}
	// read payment one by one till eof
	while(fread(&pay, sizeof(payment_t), 1, fp) > 0) {
		if(pay.memberid == memberid && pay.next_pay_duedate.day != 0 && date_cmp(now, pay.next_pay_duedate) < 0) {
			paid = 1;
			break;
		}
	}
	// close file	
	fclose(fp);
	return paid;
}

void fine_payment_add(int memberid, double fine_amount) {
	FILE *fp;
	// initialize fine payment
	payment_t pay;
	pay.id = get_next_payment_id();
	pay.memberid = memberid;
	pay.amount = fine_amount;
	strcpy(pay.type, PAY_TYPE_FINE);
	pay.tx_time = date_current();
	memset(&pay.next_pay_duedate, 0, sizeof(date_t));
	// open the file
	fp = fopen(PAYMENT_DB, "ab");
	if(fp == NULL) {
		perror("cannot open payment file");
		exit(1);
	}
	// append payment data at the end of file
	fwrite(&pay, sizeof(payment_t), 1, fp);
	// close the file
	fclose(fp);
}






