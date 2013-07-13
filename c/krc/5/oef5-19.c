/* Exercise 5.19. Modify undc1 so that it does not add redundant parentheses to
 * declarations. */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };
enum { NO, YES };

int gettoken(void);
int tokentype;			/* type of last token */
char token[MAXTOKEN];		/* last token of string */
char name[MAXTOKEN];		/* identifier name */
char datatype[MAXTOKEN];	/* data type = char, int , etc. */
char out[1000];			/* output string */

int nexttoken(void);
int prevtoken = NO;

/* undc1: convert word description to declaration */
int main()
{
	int type;
	char temp[MAXTOKEN];
	
	while (gettoken() != EOF) {
		strcpy(out, token);
		while ((type = gettoken()) != '\n') { // uiteindelijk de newline 
			if (type == PARENS || type == BRACKETS) {
				strcat(out, token);
			} else if (type == '*') {
				if ((type = nexttoken()) == PARENS || type == BRACKETS)
					sprintf(temp, "(*%s)", out);
				else
					sprintf(temp, "*%s", out);
				strcpy(out, temp);
			} else if (type == NAME) {
				sprintf(temp, "%s %s", token, out);
				strcpy(out, temp);
			} else
				printf("invalid input at %s\n", token);
			printf("%s\n", out);
		}
	}
	return 0;
}

int nexttoken(void)
{
	int type;
	extern int prevtoken;

	type = gettoken();
	prevtoken = YES;
	return type;
}

int gettoken(void) /* return next token */
{
	int c, getch(void);
	void ungetch();
	char *p = token;

	if (prevtoken == YES) {
		prevtoken = NO;
		return tokentype;
	}
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
			if (!isdigit(*(p-1)))
				printf("array size is not numeric\n");
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

