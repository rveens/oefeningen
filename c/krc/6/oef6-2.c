/* Exercise 6-2. Write a program that reads a C program and prints in alphabetic-
al order each group of variable names that are identical in the first 6 
characters, but diffrent somewhere thereafter. Don't count words within strings 
comments. Make 6 a parameter that can be set from the command line. */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXLEN 100

/* Add a node to the tree. */
struct node *treeadd(struct node *root, char *word);
/* allocate memory for a node in the heap and return a pointer to it */
struct node *talloc();
/* print the contents of the tree based on its order */
void treeprint(struct node *p);
/* stral: allocate some heap space and copy s into it */
char *stral(char *s);

int getch(void);
void ungetch(int c);
int comment(void);
int getword(char *word, int lim);

/* Struct representing a node. */
struct node {
	/* node data */
	int count;
	char *word;
	/* node internals */
	struct node *nleft;
	struct node *nright;
};

char *varname = NULL;

int main(int argc, char *argv[])
{
	char s[100];
	struct node *root = NULL;

	if (argc == 2 && strlen(argv[1]) <= 6)
		varname = argv[1];

	while (getword(s, MAXLEN) != EOF)
		if (varname == NULL || !strncmp(s, varname, strlen(varname)))
			root = treeadd(root, s);

	treeprint(root);

	return 0;
}

/* get the next token from the input */
int getword(char *word, int lim)
{
	int c, d;
	char *w = word;

	/* skip spaces */
	while (isspace(c = getch()))
		;
	if (c != EOF)
		*w++ = c;
	if (isalpha(c) || c == '_' || c == '#') {
		for ( ; --lim > 0; w++)
			if (!isalnum(*w = getch()) && *w != '_') {
				ungetch(*w);
				break;
			}
	} else if (c == '\'' || c == '"') {
		for (; --lim > 0; w++)
			if ((*w = getch()) == '\\')
				*++w = getch();
			else if (*w == c) {
				w++;
				break;
			} else if (*w == EOF)
				break;
	} else if (c == '/') {
		if ((d = getch()) == '*')
			c = comment();
		else
			ungetch(d);
	}
	*w = '\0';
	return c;
}

/* comment: skip over comment and return a character */
int comment(void)
{
	int c;
	while ((c = getch()) != EOF)
		if (c == '*') {
			if ((c = getch()) == '/')
				break;
			else
				ungetch(c);
		}
	return c;
}

/* treeadd: add a node to the tree */
struct node *treeadd(struct node *p, char *word)
{
	int cmpint;

	if (p == NULL) { // make a new node
		p = talloc();
		p->count = 1;
		p->nleft = p->nright = NULL;
		p->word = stral(word);
	} else if ( (cmpint = strcmp(p->word, word)) == 0) { // node already exists
		p->count++;
	} else if (cmpint < 0) { // add left
		p->nleft = treeadd(p->nleft, word);
	} else  // add right
		p->nright = treeadd(p->nright, word);

	return p; // return either a new node or the current p
}

/* print the contents of the tree based on its order */
void treeprint(struct node *p)
{
	if (p != NULL) {
		/* keep looking left, if left is null, print the data and look right */
		treeprint(p->nleft);
		printf("%s: %d\n", p->word, p->count);
		treeprint(p->nright);
	}
}

/* stral: allocate some heap space and copy s into it */
char *stral(char *s)
{
	char *n = (char *)malloc(strlen(s)+1);
	if (n != NULL)
		strcpy(n, s);

	return n;
}

/* allocate memory for a node in the heap and return a pointer to it */
struct node *talloc()
{
	return (struct node *)malloc(sizeof(struct node));
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
