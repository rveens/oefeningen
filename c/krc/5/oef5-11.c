/*
 * Exercise 5-11. Modify the programs entab and detab (written as exercises in
 * Chapter 1) to accept a list of tab stops as arguments. Use the default tab 
 * settings if there are no arguments.*/

#include <stdio.h>
#include <stdlib.h>

#define TRUE		1
#define FALSE		0
#define TABSTOP		5
#define MAXINPUT	80
#define MAXLEN		1000

void insstr(char original[],char add[], int inspos);
void removechar1(char s[], int pos);
void makewhitespaces(char s[], int size);
void detab1(char s[]);

void inschar(char original[],char add, int inspos);
void removerange(char s[], int start, int end);
void entab1(char s[]);

int getline1(char s[], int lim);

int main(int argc, const char *argv[])
{
	char line[MAXLEN];
	int linelength, c;

	char *p = malloc(sizeof(char) * MAXLEN);
	char *o = p;

	argv++; // skip the first one 
	while (--argc > 0 ) // the first one must be skipped, first char of the word of the pointer
		while (c = *++argv[0]) { // pointer to pointer is increased
			*p++ = c;
			printf("toegevoegd: %c\n", c);
		}

	*p++ = '\n';
	printf("totaal: %s\n", o);

	entab1(o);
	printf("getabbed: %s\n", o);

	free(o);
}

void entab1(char s[])
{
	int i, c, strc, counting;

	i = c = strc = counting = 0;

	while ((c = s[i++]) != '\0' && c != EOF)
	{
		counting = c == ' ';

		if (counting == TRUE)
			strc++;
		else
			strc = 0;

		if (strc >= TABSTOP && (i % TABSTOP) == 0)
		{
			removerange(s, i - TABSTOP, i);
			i = i - TABSTOP;
			inschar(s, '\t', i);
			strc = 0;
		}
	}
}

void detab1(char s[])
{
	int i, c, spcs;
	char whitespaces[MAXINPUT];

	i = c = spcs = 0;

	while ( (c = s[i]) != '\0')
	{
		if(c == '\t')
		{
			spcs = TABSTOP - ( i % TABSTOP);
			printf("%d", spcs);
			removechar1(s, i);
			makewhitespaces(whitespaces, spcs);
			insstr(s, whitespaces, i);
		}
		i++;
	}
}

void makewhitespaces(char s[], int size)
{
	int i;
	i = 0;

	while(i < size)
		s[i++] = ' ';
	s[i] = '\0';
}

void removechar1(char s[], int pos)
{
	int i, c = 0;

	i = pos;

	while ( (s[i] = s[i+1]) != '\0')
		i++;
}

// 1 save 'postion to end' string in a temp value.
// 2 add the 'add' variable to the string.
// 3 add the saved 'position to end' variable to the string.
void insstr(char original[],char add[], int inspos)
{
	int i;
	int c;
	char posToEnd[MAXINPUT];

       	i = 0;
	c = 0;
	
	// Save insertposition -- end.
	while((posToEnd[i] = c = original[i+inspos]) != '\0' && c != EOF) 
		i++;
	
	i = 0;
	c = 0;
 
	// Add add[] to original.
	while((original[i+inspos] = c = add[i]) != '\0' && c != EOF)
		i++;

	int x;
	x = i+inspos;
	i = 0;
	c = 0;

	// Add the posToEnd to the original string.
	while((c = original[x+i] = posToEnd[i]) != '\0' && c != EOF) 		
		i++;
}

int getline1(char s[], int lim)
{
	int c, i = 0;

	while ( (s[i] = c = getchar()) != EOF && c != '\n')
		i++;
	if(s[i] != '\n')
		i--;
	s[++i] = '\0';

	return i;
}

void removerange(char s[], int start, int end)
{
	int i, c; char lastbit[MAXINPUT];
	i = c = 0;

	// Save 'end' -- end of string as 'lastbit'
	while ( (lastbit[i] = c = s[end+i]) != '\0' && c != EOF)
		i++;
	// Add 'lastbit' after the start range
	i = 0;
	while( (s[start+i] = c = lastbit[i]) != '\0' && c != EOF)
		i++;
}

// 1 save 'postion to end' string in a temp value.
// 2 add the 'add' variable to the string.
// 3 add the saved 'position to end' variable to the string.
void inschar(char original[],char add, int inspos)
{
	int i;
	int c;
	char posToEnd[MAXINPUT];

       	i = 0;
	c = 0;
	
	// Save insertposition -- end.
	while((posToEnd[i] = c = original[i+inspos]) != '\0' && c != EOF) 
		i++;
	
	i = 0;
	c = 0;
 
	// Add add to original.
	original[i+inspos] = add;
	i++;

	int x;
	x = i+inspos;
	i = 0;
	c = 0;

	// Add the posToEnd to the original string.
	while((c = original[x+i] = posToEnd[i]) != '\0' && c != EOF) 		
		i++;
}
