/*
 * Exercise 5.8. There is no error checking in day_of_year or month_day.
 * Remedy this defect.
 */
#include <stdio.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *day);

#define TESTLIMIT 	100
#define DAYTAB_WIDTH	13

static char daytab[2][DAYTAB_WIDTH] = {
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
	printf("day_of_year (teller, teller, teller): %d\n", yearday = day_of_year(1992, 10, 19));

	return 0;
}

/* day_of_year: set dat of year from month & day */
int day_of_year(int year, int month, int day)
{
	int i, leap;

	if (year < 0 || month < 0 || month > 12 || day > 356 || day < 0)
		return;

	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

	if (leap < 0 || leap > DAYTAB_WIDTH-1)
		return;
	for (i = 1; i < month; i++)
		day += daytab[leap][i];
	return day;
}

/* DAYTAB_WIDTH month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
	long int i, leap;

	if (year < 0 || *pmonth < 0 || *pmonth > 12 || *pday > 356 || *pday < 0)
		;

	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

	if (leap < 0 || leap > DAYTAB_WIDTH-1)
		return;
	for (i = 1; yearday > daytab[leap][i]; i++) {
		yearday -= daytab[leap][i];
		if (i > DAYTAB_WIDTH-1)
			return;
	}
	*pmonth = i;
	*pday = yearday;
}

