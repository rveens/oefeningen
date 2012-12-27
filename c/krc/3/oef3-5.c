
/* Exercise 3-5 Write the function itob(n, s, b) that converts the integer n
 * into a base b character representation in the string s. In particular, 
 * itob(n, s, 16) formats n as a hexadecimal integer in s. */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void itob(int n, char s[], int b);
void itoa(int n, char s[]);
void reverse(char s[]);

int main(int argc, const char *argv[])
{
	char line[1000];

	itob(76, line, 16);
	/* itoa(32, line); */
	printf("%s", line);
	return 0;
}

/* Convert int n to s. Int b will be the base for character representation. */
void itob(int n, char s[], int b)
{
	int i, sign;

	if((sign = n) < 0)
		n = -n;
	i = 0;
	do {
		if( (abs(n % b)) <= 9 )
			s[i++] = abs(n % b) + '0';
		else
			s[i++] = (abs(n % b) -10) + 'A';
	} while ((n /= b));
	if(sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
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
	} while ((n /= 10)); /* delete it */ 
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
