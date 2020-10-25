#ifndef _LIBRARY_H
#define _LIBRARY_H

#include "date.h"

#define USER_DB		"users.db"
#define BOOK_DB		"books.db"
#define BOOKCOPY_DB	"bookcopies.db"
#define ISSUERECORD_DB	"issuerecord.db"
#define PAYMENT_DB	"payment.db"

#define ROLE_OWNER 		"owner"
#define ROLE_LIBRARIAN 	"librarian"
#define ROLE_MEMBER 	"member"

#define STATUS_AVAIL	"available"
#define STATUS_ISSUED	"issued"

#define PAY_TYPE_FEES	"fees"
#define PAY_TYPE_FINE	"fine"

#define FINE_PER_DAY			5
#define BOOK_RETURN_DAYS		7
#define MEMBERSHIP_MONTH_DAYS	30

#define EMAIL_OWNER		"sarang@sunbeaminfo.com"

typedef struct user {
	int id;
	char name[30];
	char email[30];
	char phone[15];
	char password[10];
	char role[15];
}user_t;

typedef struct book {
	int id;
	char name[50];
	char author[50];
	char subject[30];
	double price;
	char isbn[16];
}book_t;

typedef struct bookcopy {
	int id;
	int bookid;
	int rack;
	char status[16];
}bookcopy_t;

typedef struct issuerecord {
	int id;
	int copyid;
	int memberid;
	date_t issue_date;
	date_t return_duedate;
	date_t return_date;
	double fine_amount;
}issuerecord_t;

typedef struct payment {
	int id;
	int memberid;
	double amount;
	char type[10];
	date_t tx_time;
	date_t next_pay_duedate;
}payment_t;

// user functions
void user_accept(user_t *u);
void user_display(user_t *u);

// book functions
void book_accept(book_t *b);
void book_display(book_t *b);

// owner functions
void owner_area(user_t *u);
void appoint_librarian();

// librarian functions
void librarian_area(user_t *u);
void add_member();
void add_book();
void book_edit_by_id();
void bookcopy_add();
void bookcopy_checkavail_details();
void bookcopy_issue();
void bookcopy_changestatus(int bookcopy_id, char status[]);
void display_issued_bookcopies(int member_id);
void bookcopy_return();
void fees_payment_add();
void payment_history(int memberid);
int is_paid_member(int memberid);
void fine_payment_add(int memberid, double fine_amount);

// member functions
void member_area(user_t *u);
void bookcopy_checkavail();

// bookcopy functions
void bookcopy_accept(bookcopy_t *c);
void bookcopy_display(bookcopy_t *c);

// issuerecord functions
void issuerecord_accept(issuerecord_t *r);
void issuerecord_display(issuerecord_t *r);

// payment functions
void payment_accept(payment_t *p);
void payment_display(payment_t *p);

// common functions
void sign_in();
void sign_up();
void edit_profile(user_t *u);
void change_password(user_t *u);
int get_next_user_id();
int get_next_book_id();
int get_next_bookcopy_id();
int get_next_issuerecord_id();
int get_next_payment_id();

void user_add(user_t *u);
int user_find_by_email(user_t *u, char email[]);

void book_find_by_name(char name[]);
#endif

