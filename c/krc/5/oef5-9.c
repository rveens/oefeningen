/* Exercise 5-9. Rewrite the routines day_of_year and month_day with pointers 
 * instead of indexing. */

#include <stdio.h>

#define DAYTAB_WIDTH	13
#define TESTLIMIT 	100

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *day);

static char daytab1[2][DAYTAB_WIDTH] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

static int (*daytab2)[DAYTAB_WIDTH] = (int [][DAYTAB_WIDTH]) {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

static int (*daytab)[DAYTAB_WIDTH];

int main(int argc, const char *argv[])
{
	int month, day, yearday;

	int teller;

	daytab = (int (*)[]) malloc(2 * sizeof(*daytab2));

	printf("--------------------------------------------------------------------------------\n");
	printf("day_of_year: %d\n", yearday = day_of_year(1992, 10, 19));
	month = 10, day = 19;
	month_day(1992, yearday, &month, &day);
	printf("month_day (%d, %d, month, day): month:%d day:%d\n", 1992, yearday, month, day);
	printf("--------------------------------------------------------------------------------\n");

	return 0;
}

/* day_of_year: set dat of year from month & day */
int day_of_year(int year, int month, int day)
{
	int i, leap;

	if (year < 0 || month < 0 || month > 12 || day > 356 || day < 0)
	return -1;

	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

	if (leap < 0 || leap > DAYTAB_WIDTH-1)
		return -1;
	for (i = 1; i < month; i++)
		day += daytab1[leap][i];
	return day;
}

/* DAYTAB_WIDTH month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;

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

