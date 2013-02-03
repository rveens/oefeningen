
/* Exercise 4-12
 *  Adapt the ideas of printd to write a recursive version of itoa; that is,
 *  convert an integer into a string by calling a recursive routine.
 */
#include <stdio.h>
#include <string.h>

void printd(int n);
int ritoa(int n, char s[], int i);
void itoa(int n, char s[]);
void reverse(char s[]);

int main(int argc, const char *argv[])
{
	char s[1000];
	ritoa(124, s, 0);
	
	printf("%s", s);
	return 0;
}

/* printd: print n in decimal */
void printd(int n)
{
	if (n < 0) {
		putchar('-');
		n = -n;
	}
	if(n / 10)
		printd(n / 10);
	putchar(n % 10 + '0');
}

int ritoa(int n, char s[], int i)
{
	if(n < 0) { 			// record sign
		n = -n;			// make n positive
		s[i++] = '-';
	}

	if(n / 10)
		i = ritoa(n / 10, s, i);
	s[i++] = n % 10 + '0';
	return i;
}

/* itoa: convert n to characters in s */
void itoa(int n, char s[])
{
	int i, sign;

	if ((sign = n) < 0) 	/* record sign */
		n = -n;		/* make n positive */
	i = 0;
	do {			/* generate digits in reverse order */
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0); /* delete it */ 
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s); 		// Dit moeten we voorkomen m.b.v. recursie.
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
