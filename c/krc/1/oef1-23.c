
/* Write a program to remove all comments from a C program. don't forget to
 * quoted strings and characters constants properly. C comments do not nest. */

#include <stdio.h>

#define 	MAXINPUT	80
#define 	TRUE 		1
#define 	FALSE 		0

int getline1(char s[], int maxinput);
void removeComments(char s[]);
void removerange(char s[], int start, int end);

int main(int argc, const char *argv[])
{
	char line[MAXINPUT];
	int lineLength;
	
	lineLength = 0;

	while( (lineLength = getline1(line, MAXINPUT)) > 0 )
	{
		removeComments(line);
		printf("%s", line);
	}

	return 0;
}

void removeComments(char s[])
{
	int i, c, lastchar, startposition, commentFound;

	i = c = lastchar = startposition = commentFound = 0;

	while ( (c = s[i++]) != '\0' && c != EOF ){

		if (c == '/' && lastchar == '/') {
			commentFound = TRUE;
			startposition = i-2;
		}

		if(c == '*' && lastchar == '/') {
			commentFound = TRUE;
			startposition  = i-2;
		}
		
		if(c == '/' && lastchar == '*' && commentFound == TRUE) {
			removerange(s, startposition, i);
			i = i - startposition;
			commentFound = FALSE;	
		}

		if(c == '\n' && commentFound == TRUE) {
			removerange(s, startposition, i);
			i = i - startposition;
			commentFound = FALSE;
		}

		lastchar = c;
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

int getline1(char s[], int maxinput)
{
	int c, i;

	i = c = 0;

	while ( (c = s[i] = getchar()) != '\n' && c != EOF  )
		i++;
	if(s[i] == '\n')
		s[++i] = '\0';

	return i;
}
