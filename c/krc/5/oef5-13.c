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

int getinput(char *line);
int lastlines = 10; // default is 10, as ordered

int main(int argc, char const *argv[])
{
	char **p;
	char **pstart;
	char *line = malloc(sizeof(char *) * MAXLEN);

	/* read lastline var from command line parameter */
	while (--argc > 0 && (*++argv)[0] == '-')
		lastlines = (++*argv)[0] - '0';
	/* store the input */
	while (getinput(line)) {
		p = realloc(p, sizeof(char *) * ((p - pstart) + 1) );
		*p = malloc(sizeof(char *) * MAXLEN);
		strcpy(*p, line);
	}
	/* print last x lines */
	char **e = p - lastlines;
	while (*e) {
		printf("%s", *e);
		*e++;
	}

	/* free memory */
	while (p > pstart)
		free(*p--);
	free(p);

	return 0;
}

int getinput(char *line)
{
	char *s = line;

	while ( (*line = getchar() != EOF) && *line != '\n' )
		line++;
	if (*line != '\n')
		line--;
	*line = '\0';

	return line - s;
}
