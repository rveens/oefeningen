
/* Exercise 1-21 Write a program entab that replaces strings of blanks by 
 * the minimum number of tabs and blanks to achieve the same spacing. Use the 
 * same tab stops as for detab. When either a tab or a single blank
 * would suffice to reach a tab stop, which should be given the preference?*/

#include <stdio.h>

#define 	MAXINPUT	80
#define 	TABSTOP		5
#define 	TRUE 		1
#define		FALSE		0

int getline1(char s[], int lim);
void inschar(char original[],char add, int inspos);
void removerange(char s[], int start, int end);
void entab1(char s[]);

main()
{
	char line[MAXINPUT];
	int linelength = 0;

	while((linelength = getline1(line, MAXINPUT) > 0))
	{
		entab1(line);
		printf("%s", line);
	}
}

/* 1 For each character
 * 	- start counting if it is a space
 * 	- stop counting if it isnt a space and set the amount of spaces to 0.
 * 	- if the amount reaches 5, replace the last TABSTOP characters with a 
 * 	tab ('\t') */
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
