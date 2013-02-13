
/* Exercise 5-1. As written, getint treats a + or - not followed by a digit as 
 * a valid representation of zero. Fix it to push such a character back on the
 * input.
 * */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define SIZE 	100

int getline1(char s[]);

int getch(void);
void ungetch(int);
int getint(int *pn);

char buf[SIZE];	/* buffer for ungetch */
int bufp = 0;		/* next free position in buf */

int main(int argc, const char *argv[])
{
	int n, array[SIZE], getint(int *);

	for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
		;

	return 0;
}

/* getint: get next integer from input into *pn */
int getint(int *pn)
{
	int c, sign, temp;

	while (isspace(c = getch()))
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);	/* it's not a number */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-') {
		temp = c;
		c = getch();
		if (!isdigit(c)) {
			ungetch(c);
			ungetch(temp);
			c = temp;
		}
	}
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

int getch(void) /* get a (possibly pushed back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
	if (bufp >= SIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

int getline1(char s[])
{
	int i, c;

	i = c = 0;

	while ( (s[i++] = c = getchar()) != EOF && c != '\0' && c != '\n')
		;
	if (c != '\n')
		s[--i] = '\0';

	return i;
}
