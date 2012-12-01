#include <stdio.h>

#define 	MAXINPUT 	1000 // input limit

int getinput(char s[], int lim); // Get a line of input and store it in s.
void strreverse(char s[], int slength); // Reverse string s.

main() // Main method, program starts here
{
	char 	line[MAXINPUT]; // The last input line.
	int	linelength = 0; // The length of the last input line,


	while( (linelength = getinput(line, MAXINPUT)) > 0) // While there is an input line that has a length larger than zero,
	{
		strreverse(line, linelength);
		printf("%s\n", line);
	}
}

int getinput(char s[], int lim) // This method is used for getting input.
{
	int i, c; // The index used for putting characters in the s array. The int used for storing characters.

	i = 0;
	c = 0;

	while( (s[i] = (c = getchar()) ) != EOF && i < (lim-1) && c != '\n' ) // Get a character with getchar() from the input stream, and assign it to c and put it into the string array at position i. If the size of the array is less than the given limit and the character is not null, keep increasing i. 
		i++;
//	if(c == '\n') // If the last character is not a newline character there is somethign wrong, we need to remove the last character to make space for the null character in the array.
//		--i;
	s[i] = '\0';

	return i;
}

void strreverse(char s[], int slength)
{
	int start, end, ctemp; // Start and end indexes. Save current character.

	ctemp = 0;
	start = 0;
	end = slength - 1;

	while(start <= end)
	{
		ctemp = s[start];
		s[start] = s[end];
		s[end] = ctemp;
		end--;
		start++;
	}
}
