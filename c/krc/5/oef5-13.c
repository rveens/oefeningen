/* Exercise 5-13. Write the program tail, which prints the last n lines of its
 * input. By default, n is 10, let us say, but it can be changed by an optional
 * argument, so that
 * 	tail -n
 * prints the last n lines. The program should behave rationally no matter how
 * unreasonable the input or the value of n. Write the program so it makes the 
 * best use of available storage; lines should be stored as in the sorting 
 * program of Section 5.6, not in a two-dimensional array of fixed size. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MAXLEN
#define MAXLEN 1000
#endif

int getinput(char s[]);
int lastlines = 10; // default is 10, as ordered

int main(int argc, char const *argv[])
{
	char **p;
	char **pstart;
	int amountOfLines = 0;
	char *line = malloc(sizeof(char) * MAXLEN);

	/* read lastline var from command line parameter */
	while (--argc > 0 && (*++argv)[0] == '-')
		lastlines = (++*argv)[0] - '0';
	p = pstart = malloc(sizeof(char *));
	/* store the input */
	while (getinput(line)) {
		amountOfLines++;
		pstart = realloc(pstart, sizeof(char *) * amountOfLines );
		*p = malloc(sizeof(char) * MAXLEN);
		strcpy(*p++, line);
	}
	printf("------------\n");
	/* print last x lines */
	char **e = p - lastlines;
	while (e < p)
		printf("%s", *e++);

	char **t = pstart; // for cleaning up
	/* free memory */
	while (t < p)
		free(*t++);
	free(pstart);

	return 0;
}

int getinput(char s[])
{
	int i, c;

	i = c = 0;

	while( (s[i] = c = getchar()) != '\n' && c != EOF)
		i++;
	if(c == '\n')
		s[++i] = '\0';
	return i;
}
