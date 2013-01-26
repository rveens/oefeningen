/* Exercise 4-13
 * Write a recursive version of function reverse(s), which reverses the string
 * s in place. */
#include <stdio.h>
#include <string.h>

void recreverse(char s[], int i);
void reverse(char s[]);

int main(int argc, const char *argv[])
{
	char s[] = "appelflap";

	recreverse(s, -1);
	//printf("%s\n", s);

	return 0;
}

void recreverse(char s[], int i)
{
	if(s[i] != '\0')
		recreverse(s, ++i);
	putchar(s[i]);
	if(i == 1)
		s[i] = '\0';
}

void reverse(char s[])
{
	int i, j, c;

	for (i = 0, j = strlen(s)-1;i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
