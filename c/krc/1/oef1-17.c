#include <stdio.h>

#define 	LINEMAX 	10
#define 	MAXINPUT 	1000

int getline1(char s[], int max);
int stradd(char from[], char to[], int tosize);

main()
{
	char  	linebuffer[MAXINPUT];
	int  	linebuffersize = 0;
	char  	line[MAXINPUT];
	int  	linesize = 0;


	while( (linesize = getline1(line, MAXINPUT)) > 0 )
		if(linesize > LINEMAX)
			linebuffersize = stradd(line, linebuffer, linebuffersize);
	printf("%s", linebuffer);
}

int getline1(char s[], int max)
{
	int index = 0; 	// Amount of lines.
	int c = 0;  	// Current character.

	while( (c = getchar()) != EOF && index < (max - 1) && c != '\n' )
	{
		s[index] = c;
		index++;
	}
	if(c == '\n')
	{
		s[index] = c;
		index++;
	}
	s[index] = '\0';
	return index;
}

int stradd(char from[], char to[], int tosize)
{
	int fromindex, toindex;
	fromindex = toindex = 0;

	// We gaan er van uit dat de laatste waarde een '\0' is.
	if (tosize-2 > 0 && to[tosize-1] == '\0')
		toindex = tosize - 1;

	while( (to[toindex] = from[fromindex]) != '\0' )
	{
		toindex++;
		fromindex++;
	}
	toindex++;
	to[toindex] = '\0';

	return toindex;
}
