/* Write a function any(s1, s2), which returns the first location in the string
 * s1 where any character from the string s2 occurs, or -1 if s1 contains no 
 * characters from s2. (The standard library function strpbrk does the same job
 * but returns a pointer to the location.)*/

#include <stdio.h>

int getinputline(char s[]);
int any(char s1[], char s2[]);

int main(int argc, const char *argv[])
{
	char line[1000];
	int lineLength;

	lineLength = 0;

	while ( (lineLength = getinputline(line)) > 0) {
		printf("%d\n", any(line, "hoi"));
	}
	return 0;
}

int any(char s1[], char s2[])
{
	int iout, iin;

	iout = iin = 0;

	for(; s1[iout] != '\0'; iout++)
		for(iin = 0; s2[iin] != '\0'; iin++)
			if(s1[iout] == s2[iin])
				return iout;
	return -1;
}

int getinputline(char s[])
{
	int i, c;

	i = c = 0;

	while( (c = s[i] = getchar()) != '\n' && c != EOF)
		i++;
	if(c == '\n')
		s[++i] = '\0';
	return i;
}
