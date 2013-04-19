/*
 * Exercise 5-7. Rewrite readlines to store lines in an array supplied by main,
 * rather than calling alloc to maintain storage. How much faster is the pro-
 * gram?
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000		/* max #lines to be sorted */
#define MAXLEN 1000 		/* max length of any input line */

char *lineptr[MAXLINES];	/* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort1(char *lineptr[], int left, int right);

int getline1(char *s, int);

/* sort input lines */
int main()
{
	int nlines;	/* numbers of input lines read */

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		qsort1(lineptr, 0, nlines-1);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
}


/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while ((len = getline1(line, MAXLEN)) > 0)
		if (nlines >= maxlines || ((p = malloc(len)) == NULL) )
			return -1;
		else {
			line[len-1] = '\0'; /* delete newline */
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}

/* wrotelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
	int i;

	for (i = 0; i < nlines; i++)
		printf("%s\n", lineptr[i]);
	/*while (nlines-- > 0)*/
		/*printf("%s\n", *lineptr++);*/
}

/* qsort1: sort v[left]...v[right] into increasing order  */
void qsort1(char *v[], int left, int right)
{
	int i, last;
	void swap(char *v[], int i, int j);

	if (left >= right) 	/* do nothing if array contains */
		return;		/* fewer than two elements */
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsort1(v, left, last-1);
	qsort1(v, last+1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
	char *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

int getline1(char s[] , int maxlen)
{
	int i, c;

	i = c = 0;

	while ( (s[i++] = c = getchar()) != EOF && c != '\0' && c != '\n' && i != maxlen - 1)
		;
	if (c != '\n')
		s[--i] = '\0';

	return i;
}
