/* Exercise 6-3. Write a cross-referencer that prints a list of all words in a
 * document, and, for each word, a list of the line numbers on which it occurs.
 * Remove noise words like "the", "and", and so on.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXREF 100
#define MAXLINE 1000

struct node {
	/* binary tree internals */
	struct node *left;
	struct node *right;
	/* data */
	int lineref[100];
	int linerefcount;
	char *word;
};

struct node *talloc();
char *charalloc(char *s);
struct node *addtree(struct node *p, char *word, int linenum);
int getline1(char *s, int max);
int getword(char *s, int max);
void treeprint(struct node *p);

int getch(void);
void ungetch(int c);

int linenumber = 0;

int main(int argc, char *argv[])
{
	char s[MAXLINE];
	int linesize;
	struct node *root = NULL;

	while ((linesize = getword(s, MAXLINE)) > 0) {
		printf("linenum: %d: %s\n",linenumber, s);
		root = addtree(root, s, linenumber);
	}
	treeprint(root);

	return 0;
}

void treeprint(struct node *p)
{
	int i;

	if (p != NULL) {
		treeprint(p->left);
		printf("%s, ", p->word);
		for (i = 0; i <= p->linerefcount; i++) {
			putchar(p->lineref[i] + '0');
			if (i != p->linerefcount)
				putchar(' ');
		}
		putchar('\n');
		treeprint(p->right);
	}
}

int getword(char *s, int max)
{
	int c, i = 0;

	/* skip spaces, tabs */
	while ((c = getch()) == '\t' || c == ' ')
		;
	ungetch(c);
	/* keep saving chars. if we find a space we stop */
	while ((*s = c = getch()) != '\0' && c != EOF && c != ' ' && c != '\n')
		s++, i++;
	if (*s == '\n') {
		linenumber++;
	}
	*s = '\0';

	return i;
}

int getline1(char *s, int max)
{
	int c, i = 0;

	while ((*s = c = getchar()) != EOF && c != '\n' && i < max )
		s++, i++;

	if (*s == '\n')
		*s = '\0';

	return i;
}

/* Add a node to the tree, the node is returned */
struct node *addtree(struct node *p, char *word, int linenum)
{
	if (p == NULL) {
		p = talloc();
		p->left = p->right = NULL;
		p->word = charalloc(word);
		p->linerefcount = 0;
		p->lineref[p->linerefcount] = linenum;
	} else if (strcmp(word, p->word) > 0) {
		p->right = addtree(p->right, word, linenum);
	} else if (strcmp(word, p->word) < 0) {
		p->left = addtree(p->left, word, linenum);
	} else {
		p->lineref[++p->linerefcount] = linenum;
	}

	return p;
}

char *charalloc(char *s)
{
	char *n = (char *)malloc(strlen(s)+1);
	if (n != NULL)
		strcpy(n, s);

	return n;
}

/* Create a node in the heap and return a pointer */
struct node *talloc()
{
	return (struct node*) malloc(sizeof(struct node));
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

