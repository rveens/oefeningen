/* Exercise 7-2. Write a program that will print arbitrary output in a sensible
 * way. As a minimum, it should print non-graphic characters in octal or 
 * hexadecimal according to local custom, and break long text lines. */

#include <stdio.h>
#include <ctype.h>

#define MAXLINELEN 100

int main(int argc, char *argv[])
{
	int c, charcount = 0;

	while ( (c = getchar()) != EOF) {
		charcount++;
		if (iscntrl(c) || c == ' ') { // if non graphic character
			printf("%X", c);
		} else {
			putchar(c);
		}
		if (charcount % MAXLINELEN == 0)
			putchar('\n');
	}

	return 0;
}
