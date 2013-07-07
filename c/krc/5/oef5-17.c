/*
 * Exercise 5-17. Add a field-handling capabillity, so sorting may be done on
 * fields within lines, each field sorted according to an independent set of 
 * options. (The index for this book was sorted with -df for the index category
 * and -n for the page numbers.)
 * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <ctype.h>

#define MAXLINES 5000		/* max #lines to be sorted */
#define	MAXLEN	1000		/* max length of any input line */

/* options */
#define NUMERIC 1
#define REVERSE 2
#define FOLDING 4
#define DIRECTORY 8

char *lineptr[MAXLINES];	/* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines, int reverse);
int getline1(char *s, int max);

void qsort1(void *lineptr[], int left, int right,
		int (*comp)(void *, void *));
int numcmp(const void *p1, const void *p2);
void swap(void *v[], int, int);
int pstrcmp(const void *p1, const void *p2);
int pstrcasecmp(const void *p1, const void *p2);
int charcmp(char *s1, char * s2);

static char option = 0;
static int startpos = -1;
static int endpos = -1;

/* sort input lines */
int main(int argc, char *argv[])
{
	int nlines;		/* number of input lines read */
	int c;			/* temp char for arguments */

	while (--argc > 0 && ((c = (*++argv)[0]) == '-' || c == '+')) {
		if (c == '-' && !isdigit(*(argv[0]+1)))
			while (c = *++argv[0])
				switch (c) {
					case 'n':
						option |= NUMERIC;
						break;
					case 'r':
						option |= REVERSE;
						break;
					case 'f':
						option |= FOLDING;
						break;
					case 'd':
						option |= DIRECTORY;
						break;
				}
		else if (c == '-')
			endpos = atoi(argv[0]+1);
		else if ((startpos = atoi(argv[0]+1)) < 0)
			perror("Usage: sort -dfnr [+pos1] [+pos2]");
	}
	if (argc || startpos > endpos)
		perror("Usage: sort -dfnr [+pos1] [+pos2]");

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		int (*comp)(void*, void*); 	// comparison pointer

		if (option & NUMERIC)
			comp = numcmp;
		else if (option & FOLDING)
			comp = pstrcasecmp;
		else
			comp = pstrcmp;

		qsort((void **) lineptr, nlines, sizeof(*lineptr),
			(int (*)(void*,void*))(comp));
		putchar('\n');
		writelines(lineptr, nlines, option & REVERSE);
		return 0;
	} else {
		printf("input too big to sort\n");
		return 1;
	}
}

int pstrcmp(const void *p1, const void *p2)
{
	char * const *s1 = p1;
	char * const *s2 = p2;

	return strcmp(*s1, *s2);
}

int pstrcasecmp(const void *p1, const void *p2)
{
	char * const *s1 = p1;
	char * const *s2 = p2;

	return charcmp(*s1, *s2);
}

/* charcmp: return <0 if s1<s2, 0 if s1==s2, >0 if s>t
 * if directory is toggled only check on letters, numbers and blanks
 * */
int charcmp(char *s1, char *s2)
{
	int fold = option & FOLDING;
	int dir = option & DIRECTORY;
	char a, b; 	// temp comparison chars
	int startposcount = 0;

	/* skip startpos characters */
	while (*s1 && ++startposcount <= startpos)
		s1++;
	if (*s1 == '\0') // if we reach the end of the string, cancel
		return 0;
	/* again for s2 */
	startposcount = 0;
	while (*s2 && ++startposcount <= startpos)
		s2++;
	if (*s2 == '\0') // if we reach the end of the string, cancel
		return 0;

	do {
		/* skip all the non letters, non numbers and non blanks if dir is turned on */
		if (dir) {
			while (!isalnum(*s1) && *s1 != ' ' && *s1 != '\0')
				s1++;
			while (!isalnum(*s2) && *s2 != ' ' && *s2 != '\0')
				s2++;
		}
		/* use lowercase if folding is turned on */
		a = fold ? tolower(*s1) : *s1;
		s1++;
		b = fold ? tolower(*s2) : *s2;
		s2++;
		if (a == b && a == '\0')
			return 0;
		if (++startposcount == endpos)
			break;
	} while (a == b);
	return a - b;
}

/* qsort: sort v[left]...v[right] into increasing order*/
void qsort1(void *v[], int left, int right,
		int (*comp)(void *, void *))
{
	int i, last;

	if (left >= right) 	/* do nothing if array contains */
		return;		/* fewer than two elements */
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if ((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, right);
	qsort1(v, left, last-1, comp);
	qsort1(v, last+1, right, comp);
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(const void *p1, const void *p2)
{
	char * const *s1 = p1;
	char * const *s2 = p2;
	double v1, v2;
	int startposcount = 0;

	while (*s1 && ++startposcount <= startpos)
		s1++;
	if (*s1 == '\0')
		return 0;
	while (*s2 && ++startposcount <= startpos)
		s2++;
	if (*s2 == '\0')
		return 0;

	v1 = atof(*s1);
	v2 = atof(*s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else 
		return 0;
}

void swap(void *v[], int i, int j)
{
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while ((len = getline1(line, MAXLEN)) > 0)
		if (nlines >= maxlines || (p = malloc(len)) == NULL)
			return -1;
		else {
			line[len-1] = '\0'; /* delete newline */
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines, int reverse)
{
	int i;

	if (reverse)
		for (i = nlines-1; i >= 0; i--)
			printf("%s\n", lineptr[i]);
	else
		for (i = 0; i < nlines; i++)
			printf("%s\n", lineptr[i]);
}

int getline1(char *s, int maxlen)
{
	int c, i;

	for (i = 0; i < maxlen-1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';

	return i;
}
