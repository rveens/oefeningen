#include <stdio.h>

#define 	LINEMAX 	1
#define 	MAXINPUT 	1000

int getline1(char s[], int max);
int stradd(char from[], char to[], int tosize);
int validateline(char line[], int linesize);

main()
{
	char  	linebuffer[MAXINPUT];
	int  	linebuffersize = 0;
	char  	line[MAXINPUT];
	int  	linesize = 0;


	while( (linesize = getline1(line, MAXINPUT)) > 0 )
	{
		if(linesize > LINEMAX)
		{
			linesize = validateline(line, linesize);
			linebuffersize = stradd(line, linebuffer, linebuffersize);
		}
	}
	printf("%sBuffer=%d\n", linebuffer, linebuffersize);
}

int validateline(char line[], int linesize) 
{
	int i, c;

	if (line[0] == '\n')
	{
		line[0] = '\0';
		printf("[%s]", line);
	}

	i = linesize - 1;

	c = line[i];
	while(c == '\t' || c == ' ' || c == '\0' || c == '\n')
	{
		c = line[i];
		i--;
	}
	i = i + 2;
	if(line[i-1] != '\n')
		line[i] = '\n';
	line[++i] = '\0';
	return i;
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
