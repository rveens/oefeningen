/*
 * Exercise 5-5. Write versions of the library functions strncpy, strncat and 
 * strncmp, which operate on at most the first n characters of their argument strings. For 
 * example, strncpy(s, t, n) copies at most n characters of t to s.
 * Full descriptions are in Appendix B.
 */
#include <stdio.h>

char *strncpy1(char *s, char *t, int n);
char *strncat1(char *s, char *t, int n);
int strncmp1(char *s, char *t, int n);

int main(int argc, const char *argv[])
{
	char s[50] = "kaas";
	char t[50] = "kaas1";

	/*strncat1(s, t, 5);*/
	printf("'%d'", strncmp1(s, t, 4));

	return 0;
}

/*copies at most n characters of the argument s to t.*/
char *strncpy1(char *s, char *t, int n)
{
	while ( n-- && (*t++ = *s++) )
		;
	*t = '\0';
	return t;
}

/*copies at most n characters of s to the end of t.*/
char *strncat1(char *s, char *t, int n)
{
	while (*t)
		++t;
	while ( n-- && (*t++ = *s++) )
		;
	*s = '\0';
	return t;
}

int strncmp1(char *s, char *t, int n)
{
	while ( n-- && (*t++ == *s++) )
		if (*t == '\0')
			return 0;
	return *t - *s;
}
