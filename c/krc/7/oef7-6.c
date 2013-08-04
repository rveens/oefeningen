/* Exercise 7-6. Write a program to compare two files, printng the first line 
 * where they differ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1000

int main(int argc, char *argv[])
{
	FILE *f1, *f2;
	char *s1 = malloc(sizeof(char) * MAXLEN);
	char *s2 = malloc(sizeof(char) * MAXLEN);

	*s1 = *s2 = '\0';

	if (argc != 3)
		printf("Usage: a.out: file1 file2\n");
	else {
		// open files
		f1 = fopen(argv[1], "r");
		f2 = fopen(argv[2], "r");

		if (f1 == NULL || f2 == NULL)
			printf("error opening files\n");

		do {
			fgets(s1, MAXLEN, f1);
			fgets(s2, MAXLEN, f2);
		} while (strcmp(s1, s2) == 0);

		printf("file1: %s", s1);
		printf("file2: %s", s2);
	}

	free(s1);
	free(s2);

	return 0;
}
