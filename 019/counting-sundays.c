/*
 *
 * 1 Jan 1900 was a Monday.
 *
 * Thirty days has September,
 * April, June and November.
 * All the rest have thirty-one,
 * Saving February alone,
 * Which has twenty-eight, rain or shine.
 * And on leap years, twenty-nine.
 *
 * A leap year occurs on any year evenly
 * divisible by 4, but not on a century unless
 * it is divisible by 400.
 * 
 * How many Sundays fell on the first of the month during the twentieth century
 * (1 Jan 1901 to 31 Dec 2000)?
 */
#include <stdio.h>

char *months[] = {
	"jan", "feb", "mar", "apr", "may", "jun",
	"jul", "aug", "sep", "oct", "nov", "dec"
};
int month_days[] = {
	31, 28, 31, 30, 31, 30,
	31, 31, 30, 31, 30, 31
};
char *days[] = {
	"sun", "mon", "tue", "wed", "thu", "fri", "sat"
};
int main(void) {
	int month = 0;		// Jan
	int date = 1;		// 1st
	int year = 1900;	// 1901
	int day = 1;		// Monday
	int n = 0;
	while (year < 2001) {
		// is a Sunday on the 1st of the month?
		if (date == 1 && day == 0 && year > 1900) {
			n++;
			printf("%s, %s %d, %d\n", days[day], months[month], date, year);
		}
		// increment date
		day++;
		if (day > 6) {
			day = 0;
		}
		date++;
		if (date > month_days[month]) {
			// is a leap day?
			if (
					// month is feb
					month == 1
					// date is 29th
					&& date == 29
					// year divisible by 4
					&& (year % 4 == 0)
					// year not divisible by 100 but is divisible by 400
					&& ((year % 100 != 0) || (year % 400 == 0))
			   ) {
				printf("leap year: %s, %s %d, %d\n", days[day], months[month], date, year);
			} else {
				date = 1;
				month++;
				if (month > 11) {
					month = 0;
					year++;
				}
			}
		}
	}
	printf("total: %d\n", n);
	return 0;
}
