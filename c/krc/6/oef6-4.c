/* Exercise 6-4. Write a program that prints the distinct words in its input 
 * sorted into decreasing order of frequency of occurrence. Precede each word 
 * by its count. */

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
	char *word;
	int count;
};

struct node *talloc();
char *charalloc(char *s);
struct node *addtree(struct node *p, char *word);
int getline1(char *s, int max);
int getword(char *s, int max);
void treeprint(struct node *p);
void treegrabpointer(struct node *p);

int getch(void);
void ungetch(int c);
int comparefunc(struct node *first, struct node *second);

int linenumber = 0;
struct node *sortlist[20];
int sortlistcounter = 0;
int wordcount = 0;

int main(int argc, char *argv[])
{
	char s[MAXLINE];
	int linesize;
	struct node *root = NULL;

	while ((linesize = getword(s, MAXLINE)) > 0) {
		printf("linenum: %d: %s\n",linenumber, s);
		root = addtree(root, s);
	}
	/* Create a list that will fit pointers to all structs, and sort this */
	/* Search the tree and fill the list with pointers */
	treegrabpointer(root);
	qsort(sortlist, wordcount, sizeof *sortlist, comparefunc);

	int i;
	for (i = 0; i < wordcount; i++)
		printf("%d: %s\n", sortlist[i]->count + 1, sortlist[i]->word);

	return 0;
}

int comparefunc(struct node *first, struct node *second)
{
	if (first == NULL || second == NULL)
		printf("error!\n");
	printf("vergelijking: %d en %d\n", first->count, second->count);
	if (first->count == second->count)
		return 0;
	else if (first->count > second->count)
		return 1;
	else
		return -1;
}

void treegrabpointer(struct node *p)
{
	if (p != NULL) {
		treegrabpointer(p->left);
		sortlist[sortlistcounter++] = p;

		treegrabpointer(p->right);
	}
}

void treeprint(struct node *p)
{
	if (p != NULL) {
		treeprint(p->left);
		printf("%s, ", p->word);

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
struct node *addtree(struct node *p, char *word)
{
	if (p == NULL) {
		p = talloc();
		p->left = p->right = NULL;
		p->word = charalloc(word);
		p->count = 0;
		wordcount++;
	} else if (strcmp(word, p->word) > 0) {
		p->right = addtree(p->right, word);
	} else if (strcmp(word, p->word) < 0) {
		p->left = addtree(p->left, word);
	} else
		p->count++;

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


