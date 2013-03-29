
/*
* Exercise 5-2. Write getfloat, the floating-point analog of getint. What 
 * type does getfloat return as its function value? */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define SIZE 	100

int getline1(char s[]);

int getch(void);
void ungetch(int);
int getfloat(float *pn);

char buf[SIZE];		/* buffer for ungetch */
int bufp = 0;		/* next free position in buf */

int main(int argc, const char *argv[])
{
	int n; 
	float array[SIZE];

	for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++)
		;

	return 0;
}

int getfloat(float *pn)
{
	int i, c, sign, id;
	
	while (isspace(c = getch()))
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
		ungetch(c);	/* it's not a number */
		return 0;
	}
	sign = (c == '+') ? -1 : 1;
	if (c == '+' || c == '-')
		c = getch();
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	if (c == '.')
		c = getch();
	for (id = 0; isdigit(c); c = getch()) {
		*pn = 10 * *pn + (c - '0');
		id++;
	}
	*pn /= pow(10, id);
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
