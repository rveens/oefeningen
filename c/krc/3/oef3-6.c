
/* Exercise 3-6 Write a version of itoa that accepts three arguments instead 
 * of two. The third argument is a minimum field width; the converted number 
 * must be padded with blanks on the left if necessary to make it wide enough.*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse(char s[]);
void itoa(int n, char s[]);
void itoma(int n, char s[], int minfield);

int main(int argc, const char *argv[])
{
	char line[1000];
	itoma(45, line, 3);
	printf("%s", line);
	return 0;
}

void itoma(int n, char s[], int minfield)
{
	int i, sign;
	int cntr, iadd;
	char spacing[1000];
	
	if ((sign = n) < 0) 	/* record sign */
		n = -n;		/* make n positive */
	i = 0;
	do {			/* generate digits in reverse order */
		s[i++] = abs(n % 10) + '0';
	} while ((n /= 10)); 	/* delete it */ 
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
	
	if(i < minfield) {
		/* 1- move all the chars to the right
		 * 2- add the char at the first position
		 */
		// count the amount of white spaces to add.
		for(cntr = 0; cntr < (minfield - i); cntr++) 
			;
		// for every space that is to be added at the start.
		for(i = 0; i < cntr; i++) {
			// Shift all the characters to the right.
			for(iadd = cntr+1; iadd >= 0; iadd--)
				s[iadd+1] = s[iadd];
			// And add a white space at the start.
			s[0] = ' ';
		}
	}
}

/* itoa: convert n to characters in s */
void itoa(int n, char s[])
{
	int i, sign;
	
	if ((sign = n) < 0) 	/* record sign */
		n = -n;		/* make n positive */
	i = 0;
	do {			/* generate digits in reverse order */
		s[i++] = abs(n % 10) + '0';
	} while ((n /= 10)); 	/* delete it */ 
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
	
}

void reverse(char s[])
{
	int i, j, c;

	for (i = 0, j = strlen(s)-1;i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
