#include <stdio.h>
#include <ctype.h>
#include <string.h>

int getch(void);
int ungetch(int);
void turn(char s[]);

int main(int argc, const char *argv[])
{
	char s[] = "kaaaaas";
	turn(s);
	printf("%s\n", s);
	return 0;
}

/* getint:  get next integer from input into *pn */
int getint(int *pn)
{
	int c, sign;

	while(isspace(c = getch()))	/* skip the white spaces  */
		;
	if(!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);	/* it's not a number */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if(c == '+' || c == '-')
		c = getch();
	for(*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

void turn(char s[])
{
	int i, j, temp;

	for(i = 0, j = strlen(s); j > i; i++, j--) {
		temp = s[i];
		s[i] = s[j];
		s[j] = temp;
	}

}
