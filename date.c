#include <stdio.h>
#include <time.h>
#include "date.h"

void date_accept(date_t *d) {
	printf("date: ");
	scanf("%d%d%d", &d->day, &d->month, &d->year);
}

void date_print(date_t *d) {
	printf("date: %d-%d-%d\n", d->day, d->month, d->year);
}

int date_equal(date_t d1, date_t d2) {
	if(d1.day == d2.day && d1.month == d2.month && d1.year == d2.year)
		return 1;
	return 0;
}

int date_greater(date_t d1, date_t d2) {
	if(d1.year > d2.year || (d1.year == d2.year && d1.month > d2.month) || (d1.year == d2.year && d1.month == d2.month && d1.day > d2.day))
		return 1;
	return 0;
}

int is_leap(int year) {
	if(year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
		return 1;
	return 0;
}

int month_days(int month, int year) {
	int mon_days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if(is_leap(year))
		mon_days[2] = 29;
	return mon_days[month];
}

int year_days(int year) {
	if(is_leap(year))
		return 366;
	return 365;
}

int date_cmp(date_t d1, date_t d2) {
	int diff = -1, days = 0;
	date_t min = d1, max = d2;
	if(date_greater(d1, d2)) {
		diff = 1;
		min = d2;
		max = d1;
	}
	while(!date_equal(min, max)) {
		days = days + 1;
		min.day = min.day + 1;
		if(min.day > month_days(min.month, min.year)) {
			min.day = 1;
			min.month = min.month + 1;
		}
		if(min.month > 12) {
			min.day = 1;
			min.month = 1;
			min.year = min.year + 1;
		}
	}
	return diff * days;
}

date_t date_add(date_t d, int days) {
	date_t res = d;
	while(days > 0) {
		days--;
		res.day = res.day + 1;
		if(res.day > month_days(res.month, res.year)) {
			res.day = 1;
			res.month = res.month + 1;
		}
		if(res.month > 12) {
			res.day = 1;
			res.month = 1;
			res.year = res.year + 1;
		}
	}
	return res;
}

date_t date_current() {
	time_t t = time(NULL);
	struct tm *tm = localtime(&t);
	date_t now;
	now.day = tm->tm_mday;
	now.month = tm->tm_mon + 1;
	now.year = tm->tm_year + 1900;
	return now;
}
