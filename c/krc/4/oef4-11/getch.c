#include <stdio.h>
#include "calc.h"
#define BUFSIZE 	100

static char buf[BUFSIZE];		/* buffer for ungetch */
static int curbufsize = 0;		/* Current position in the buffer */
static int curtotalbufsize = 0;	/* Total buffer size */

int getch(void) /* get a (possibly pushed back) character */
{
	if(curbufsize >= curtotalbufsize) {
		curtotalbufsize = getline1(buf);
		curbufsize = 0;
	}
	return buf[curbufsize++];
}

void ungetch(int c) /* push character back on input */
{
	if (curbufsize >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else if(curbufsize > 0)
		--curbufsize;
}

static int getline1(char s[])
{
	int i, c;

	i = c = 0;

	while( (s[i] = c = getchar()) != '\n' && c != EOF)
		i++;
	if(c == '\n')
		s[++i] = '\0';
	return i;
}
