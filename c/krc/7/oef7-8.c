/* Exercise 7-8. Write a program to print a set of files, starting each new one
 * on a new page, with a title and a running page count for each file. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXARG 5
#define PAGESIZE 100
#define MAXLEN 1000

int page = 1, linecounter = 0;

void printpage(FILE *f, char *name)
{
	char *line = malloc(sizeof(char) * MAXLEN);

	while (fgets(line, MAXLEN, f) != NULL) {
		if ( (linecounter % PAGESIZE) == 0) {
			printf("page %d\n", page++);
			printf("File: %s\n", name);
		}

		printf("%s", line);
		linecounter++;
	}
}

int main(int argc, char *argv[])
{
	FILE *f;
	int i = 1;

	while (--argc > 0) {
		f = fopen(argv[i], "r");
		if (f == NULL)
			printf("Unable to open file %s\n", argv[i]);
		printpage(f, argv[i]);
		fclose(f);

		i++;
	}

	return 0;
}
