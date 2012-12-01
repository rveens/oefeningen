

/* Exercise 1-20 Write a program 'detab' that replaces tabs in the input 
with the proper number of blanks to space to the next tab stop. 
Assume a fixed set of tab stops, say every n columns. 
Should n be a variable or a symbolic parameter? */

#include <stdio.h>

#define 	MAXINPUT	80
#define 	TABSTOP		5

int getline1(char s[], int lim);
void detab1(char s[]);
void insstr(char original[],char add[], int inspos);
void removechar1(char s[], int pos);
void makewhitespaces(char s[], int size);

main()
{
	char line[MAXINPUT];
	int linelength = 0;

	while((linelength = getline1(line, MAXINPUT) > 0))
	{
		detab1(line);
		printf("%s", line);
	}
}

// 1 Read the line, look for a tab character.
// 2 Determine how many spaces should be added. 
// 	tabstop - ( (currentposition + 1) % tabstop).
// 3 Remove the tab character.
// 4 Insert spaces using insstr.
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
