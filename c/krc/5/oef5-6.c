/*
 * Exercise 5-6. Rewrite appropriate programs from earlier chapters and 
 * exercises with pointers instead of array indexing. Good possibilities include
 * getline (Chapters 1 and 4), atoi, itoa, and their variants (Chapters 2, 3, and 4),
 * reverse (Chapter 3), and strindex and getop (Chapter 4).
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int getline1(char *s);
int atoi2(char *s);
void reverse(char *s);
int strindex(char *s, char *t);
int getop(char *s);

int main(int argc, const char *argv[])
{
	char s[] = "test12345";
	/* getline */
	//int length = getline1(s);

	/* reverse test */
	//reverse(s);
	//printf("'%s' length='%d'\n", s, length);

	/* atoi2 */
	//printf("'%d'Appelflappenbakker\n", atoi2(s) + 10);
	
	char s1[] = "12345";
	printf("retval: %d\n", strindex(s, s1));

	return 0;
}

/*pointer version of getline page ch4 p69*/
int getline1(char *s)
{
	int c;
	char *b = s;

	while ( (c = *s++ = getchar()) && c != EOF && c != '\n')
		;
	*s = '\0';

	return (s - b);
}

/*atoi: convert s to integer. Version 2 ch3 p61 */
int atoi2(char *s)
{
	int n, sign;

	while (isspace(*s)) /*remove spaces */
		*s++;
	sign = (*s == '-') ? -1 : 1;
	if (*s == '+' || *s == '-') /* skip sign */
		*s++;
	for (n = 0; isdigit(*s); )
		n = 10 * n + (*s++ - '0');
	return sign * n;
}

void itoa(int n, char s[])
{
	int sign;

	if ((sign = n) < 0) 	/* record sign */
		n = -n;		/* make n positive */
	do {
		*s++ = n % 10 + '0';
	} while ((n /= 10) > 0);
	if (sign < 0)
		*s++ = '-';
	*s = '\0';
	reverse(s);
}

void reverse(char *s)
{
	char *e = s;
	char t;

	while (*e++)
		;
	e -= 2; /* Swapping null byte results in an empty string. */ 
	while (s < e) {
		t = *s;
		*s = *e;
		*e = t;

		*++s, *--e;
	}
}

/* strindex: return index of t in s, -1 if none */
int strindex(char *s, char *t)
{
	char *k;	/* used to compare s relatively */
       	char *n = s;	/* a copy of s to compute the position */
       	char *j = t;	/* used to reset the pointer t to the start */

	/* go through the s array */
	while (*s++) {
		k = s; /* used to compare the strings s and t */
		t = j; /* reset t pointer to start */

		/* compare the t array to s from now on */
		while (*t++ == *k++ && *k )
			;
		if ( !(*k) && (k - s) > 0 )
			return s - n;
	}
	return -1;
}

/* begin of stuff needed for getop */
char buf[100];
int bufp = 0;

int getch(void);
void ungetch(int);

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= 100)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
/* end of stuff needed for getop */

/* getop: get next operator or numeric operand */
int getop(char *s)
{
	
}
