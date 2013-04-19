/*
 * Exercise 5-7. Rewrite readlines to store lines in an array supplied by main,
 * rather than calling alloc to maintain storage. How much faster is the pro-
 * gram?
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>

#define MAXLINES 5000		/* max #lines to be sorted */
#define MAXLEN 1000 		/* max length of any input line */

/*char *lineptr[MAXLINES];	[> pointers to text lines <]*/
char list[MAXLINES][MAXLEN];

int readlines(char lijst[MAXLINES][MAXLEN], int nlines);
void writelines(char l[MAXLINES][MAXLEN], int nlines);

void qsort1(char v[][MAXLEN], int left, int right);

int getline1(char *s, int);

/* sort input lines */
int main()
{
	int nlines;	/* numbers of input lines read */

	if ((nlines = readlines(list, MAXLINES)) >= 0) {
		clock_t start, finish;
	       	start = clock();
		qsort1(list, 0, nlines-1);
		writelines(list, nlines);
		finish = clock();
		printf("Tijd: %f", ( (double)finish - start )  );
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
}

double now(void)
{
   struct timeval tv;
   double retval=0;
   gettimeofday(&tv, NULL);
   retval=tv.tv_usec;
   retval+= (double)tv.tv_usecs / 1000000.;
   return retval;
}

/* readlines: read input lines */
int readlines(char lijst[MAXLINES][MAXLEN], int maxlines)
{
	int len, nlines;

	nlines = 0;
	while ((len = getline1(lijst[nlines], MAXLEN)) > 0)
		if (nlines >= maxlines)
			return -1;
		else
			lijst[nlines++][len-1] = '\0';
	return nlines;
}

/* wrotelines: write output lines */
void writelines(char l[MAXLINES][MAXLEN], int nlines)
{
	int i;

	for (i = 0; i < nlines; i++)
		printf("%s\n", l[i]);
	/*while (nlines-- > 0)*/
		/*printf("%s\n", *lineptr++);*/
}

/* qsort1: sort v[left]...v[right] into increasing order  */
void qsort1(char v[][MAXLEN], int left, int right)
{
	int i, last;
	void swap(char v[][MAXLEN], int i, int j);

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
void swap(char v[][MAXLEN], int i, int j)
{
	char temp[MAXLEN];

	strcpy(temp, v[i]);
	strcpy(v[i], v[j]);
	strcpy(v[j], temp);
}

int getline1(char s[] , int maxlen)
{
	int i, c;

	i = c = 0;

	while ( (s[i++] = c = getchar()) != EOF && c != '\0' && c != '\n' && i < maxlen - 1)
		;
	if (c != '\n')
		s[--i] = '\0';

	return i;
}
