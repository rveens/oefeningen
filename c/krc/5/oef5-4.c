
/* Exercise 5-4. Write a function strend(s, t), which returns 1 if the string t
 * occurs at the end of string s, and zero otherwise.*/

#include <stdio.h>
#include <string.h>

int strend(char *s, char *t);

int main(int argc, const char *argv[])
{
	char s[50] = "test123";
	char t[50] = "123";

	printf("retval: %d", strend(s, t));

	return 0;
}

/*save length of t, go back and count. same? succes */
int strend(char *s, char *t)
{
	char *p = t;
	/*find out what the end is.*/
	while (*t)
		*t++;
	while (*s)
		*s++;
	/*point to the last char, not the null value*/
	*s--;
	*t--;
	/*go back from the end, as long as the are the same*/
	while (*s == *t) {
		if (*s == *p)
			return 1;
		*s--;
		*t--;
	}
	return 0;
}
