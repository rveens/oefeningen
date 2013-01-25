
/* Exercise 4-1 Write a function strrindex(s,t), which returns the position
 * of the rightmost occurence of t in s, or -1 if there is none. */

#include <stdio.h>
#include <string.h>

int strindex(char s[], char t[]);
int strrindex(char s[], char t[]);
int getinputline(char s[]);

int main(int argc, const char *argv[])
{
	char line[1000];
	int linelength;

	while( (linelength = getinputline(line)) > 0) {
		printf("%d\n", strrindex(line, "test"));
	}

	return 0;
}

/* find the first occurence of a word. And return the index where the word starts. */
int strindex(char s[], char t[])
{
	int i; 	// Index for s
	int j;	// Index for s, starting at i
	int k; 	// Index for t

	/* for each char in s */
	for(i = 0; i < strlen(s); i++) {
		/* go through the t string */
		for(j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
			;
		/* if the we found the full length of string t in s */
		if(t[k] == '\0') // at the end of the string t
			return i; // return the start position, we found the word.
	}
	return -1;
}

/* find the last occurence of a word. And return the index where the word starts. */
int strrindex(char s[], char t[])
{
	int i; 	// Index for s
	int j;	// Index for s, starting at i
	int k; 	// Index for t
	int li;	// Last index of found word.

	li = 0;

	/* for each char in s */
	for(i = 0; i < strlen(s); i++) {
		/* go through the t string */
		for(j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
			;
		/* if the we found the full length of string t in s */
		if(t[k] == '\0') // at the end of the string t
			li = i; // return the start position, we found the word.
	}
	if(li)
		return li;
	else
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
