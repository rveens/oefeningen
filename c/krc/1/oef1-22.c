
/* Write a program to fold long input lines into two or more shorter lines 
 * after the last non-blank character that occurs before the n-th column of 
 * input. Make sure your program does something intelligent with very long
 * lines, and if there are no blanks or tabs before the specified column.*/
#include <stdio.h>

#define		MAXINPUT	1000	
#define		LINELIMIT	30

int getline1(char s[], int lim);
void foldline(char s[], int lineSize);
void inschar(char original[],char add, int inspos);

int main(int argc, const char *argv[])
{
	char line[MAXINPUT];
	int lineSize;	
	
	while( (lineSize = getline1(line, MAXINPUT)) > 0)
	{
		foldline(line, lineSize);
		printf("%s", line);
	}

	return 0;
}

/* Fold the line into multiple lines. */
void foldline(char s[], int lineSize)
{
	int i, c, lli;
	c = i = lli = 0;
	
	while( (c = s[i++]) != '\0' && c != EOF)
	{
		// Limit reached, look for the last non blank character.
		if( ( (i+1) % LINELIMIT ) == 0)
		{
			lli = i; // Remember the last line limit index.
			while( (c = s[i]) != '\0' && c != ' ' && c != '\t')
				i--;
			if(c != '\0')
				inschar(s, '\n', i+1);
			i = lli; 
		}
	}
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
