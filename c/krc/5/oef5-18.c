#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

void dc1(void);
void dirdc1(void);

int gettoken(void);
int tokentype;			/* type of last token */
char token[MAXTOKEN];		/* last token of string */
char name[MAXTOKEN];		/* identifier name */
char datatype[MAXTOKEN];	/* data type = char, int , etc. */
char out[1000];			/* output string */


int main(int argc, char const *argv[])
{
	while (gettoken() != EOF) {		/* 1st token on line */
		strcpy(datatype, token);	/* is the datatype */
		out[0] = '\0'; // zet output naar niks
		dc1();		/* parse rest of line */
		if (tokentype != '\n')
			printf("syntax error\n");
		printf("%s: %s %s\n", name, out, datatype);
	}
	return 0;
}

/* dc1: parse a declarator */
void dc1(void)
{
	int ns; // aantal stars

	for (ns = 0; gettoken() == '*'; ) /* count *`s */
		ns++;
	dirdc1();
	while (ns-- > 0)
		strcat(out, " pointer to");
}

/* dirdc1: parse a direct declarator */
void dirdc1(void)
{
	int type;			/* ( dc1 ) */

	if (tokentype == '(') {
		dc1();
		if (tokentype != ')')
			printf("error: missing )\n");
	} else if (tokentype == NAME) 	/* variable name */
		strcpy(name, token);
	else
		printf("error: expected name or (dc1)\n");
	while ((type=gettoken()) == PARENS || type == BRACKETS)
		if (type == PARENS)
			strcat(out, " function returning");
		else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
}

int gettoken(void) /* return next token */
{
	int c, getch(void);
	void ungetch();
	char *p = token;

	while ((c = getch()) == ' ' || c == '\t') /* skip spaces */
		;
	if (c == '(') { /* check for parenthesis token. if they are not immediatly closed return '(' as last token */
		if ((c = getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		} else {
			ungetch(c);
			return tokentype = '(';
		}
	} else if (c == '[') { /* check for bracket token */
		for (*p++ = c; (*p++ = getch()) != ']'; )
			;
		*p = '\0';
		return tokentype = BRACKETS;
	} else if (isalpha(c)) { /* last, check for name */
		for (*p++ = c; isalnum(c = getch()); )
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	} else /* return last character as token if all else fails */
		return tokentype = c;
}

/* getch and ungetch from chapter 4 */
#define BUFSIZE 100

char buf[BUFSIZE];	/* buffer for ungetch */
int bufp = 0;		/* next free position in buf */

int getch(void) /* get a (possibly pushed back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
