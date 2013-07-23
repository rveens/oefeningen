/* Exercise 7-1. Write a program that converts upper case to lower or lower case
 * to upper depending on the name it is invoked with, as found in argv[0]. */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

int isLowercase = 0;

int main(int argc, char *argv[])
{
	int c;

	if (strstr(argv[0], "lower"))
		isLowercase = 1;
	else if (strstr(argv[0], "upper"))
		isLowercase = 0;

	while ((c = getchar()) != EOF) {
		if (isLowercase)
			putchar(tolower(c));
		else
			putchar(toupper(c));
	}
	

	return 0;
}
