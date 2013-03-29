
/* Exercise 5-3: Write a pointer version of the function strcat that we showed in Chapter
 * 2: strcat(s,t) copies the string t to the end of s. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void strcat1(char *s, char *t);

int main(int argc, const char *argv[])
{
	char s[50] = "kaas";
	char t[50] = "stengels";

	strcat1(s, t);
	printf("%s", s);

	return 0;
}

void strcat1(char *s, char *t)
{
	while (*s++)
		;
	s--;
	while (*s++ = *t++)
		;
}
