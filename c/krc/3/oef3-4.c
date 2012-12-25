
/* Exercise 3-4: In a two's complement number representation, our version of itoa
 * does not handle the largest negative number, that is, the value of
 * n equal to -(2^wordsize-1). Explain why not. Modify it to print that
 * value correctly regardless of the machine on which it runs.*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse(char string[]);
void itoa(int n, char s[]);

int main(int argc, const char *argv[])
{
	char string[1000];
	itoa(128, string);
	strcat(string, "test");
	printf("%s\n", string);
	return 0;
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
