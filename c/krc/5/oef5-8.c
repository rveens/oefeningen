/*
 * Exercise 5.8. There is no error checking in day_of_year or month_day.
 * Remedy this defect.
 */
#include <stdio.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *day);

#define TESTLIMIT 	1000

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int main(int argc, const char *argv[])
{
	int month, day, yearday;

	int teller;
	
	for (teller = 0; teller < TESTLIMIT; teller++) {
		printf("--------------------------------------------------------------------------------\n");
		printf("day_of_year (teller, teller, teller): %d\n", yearday = day_of_year(teller, teller, teller));
		month_day(teller, yearday, &month, &day);
		printf("month_day (teller, %d, month, day): month:%d day:%d\n", yearday, month, day);
		printf("--------------------------------------------------------------------------------\n");
	}

	return 0;
}

/* dat_of_year: set dat of year from month & day */
int day_of_year(int year, int month, int day)
{
	int i, leap;

	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	for (i = 1; i < month; i++)
		day += daytab[leap][i];
	return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;

	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	for (i = 1; yearday > daytab[leap][i]; i++)
		yearday -= daytab[leap][i];
	*pmonth = i;
	*pday = yearday;
}

