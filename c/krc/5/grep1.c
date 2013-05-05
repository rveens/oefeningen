#include <stdio.h>
#include <string.h>
#define	MAXLINE	1000

int getline1(char *line, int max);

/* find: print lines that match pattern from 1st arg */
int main(int argc, const char *argv[])
{
	char line[MAXLINE];
	int found = 0;

	if (argc != 2)
		printf("Usage: find pattern\n");
	else
		while (getline1(line, MAXLINE) > 0)
			if (strstr(line, argv[1]) != NULL) {
				printf("%s", line);
				found++;
			}

	return 0;
}

int getline1(char *line, int max)
{
	int c;
	char *p = line;

	while ( (*line = c = getchar()) && c != EOF && c != '\n' && strlen(line) < max)
		line++;
	if (*line == '\n')
		*line = '\0';

	return line - p;
}
