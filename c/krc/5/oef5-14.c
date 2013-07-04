/*
 * Exercise 5-14. Modify the sort program to handle a -r flag, which indicates
 * sorting in reverse (decreasing) order. Be sure that -r works with -n.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>

#define MAXLINES 5000		/* max #lines to be sorted */
#define	MAXLEN	1000		/* max length of any input line */

char *lineptr[MAXLINES];	/* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines, int reverse);
int getline1(char *s, int max);

void qsort1(void *lineptr[], int left, int right,
		int (*comp)(void *, void *));
int numcmp(const void *p1, const void *p2);
void swap(void *v[], int, int);
int pstrcmp(const void *p1, const void *p2);

/* sort input lines */
int main(int argc, char *argv[])
{
	int nlines;		/* number of input lines read */
	int numeric = 0;	/* 1 if numeric sort */
	int reverse = 0;	/* 1 if reverse sort */
	int c;			/* temp char for arguments */

	while (--argc > 0 && (*++argv)[0] == '-') {
		while (c = *++argv[0]) {
			switch (c) {
				case 'n':
					numeric = 1;
					break;
				case 'r':
					reverse = 1;
					break;
			}
		};
	}

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		qsort((void **) lineptr, nlines, sizeof(*lineptr),
			(int (*)(void*,void*))(numeric ? numcmp : pstrcmp));
		putchar('\n');
		writelines(lineptr, nlines, reverse);
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
