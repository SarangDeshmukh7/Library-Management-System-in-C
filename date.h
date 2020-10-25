#ifndef __DATE_H
#define __DATE_H

#include <time.h>

typedef struct date {
	int day;
	int month;
	int year;
}date_t;

void date_accept(date_t *d);
void date_print(date_t *d);
int date_cmp(date_t d1, date_t d2);
date_t date_add(date_t d, int days);
date_t date_current();

#endif
