#include <stdio.h>
#include <ctype.h>
#include <string.h>

int atoi1(char s[]);
void itoa(int n, char s[]);

int main(int argc, const char *argv[])
{
	char line[] = "   25";

	printf("%d", atoi1(line)+5);	
	return 0;
}

void itoa1(int n, char s[])
{
	int i, sign;

	if((sign = n) < 0) 	/* record sign */
		n = -n;		/* make n positive */
	i = 0;
	do {
		s[i++] = n % 10 + '0'; } while ((n /= 10) > 0);
	if(sign < 0)
		s[i++] = '-';
	s[i] = '0';
	reverse(s);
}

/* itoa: convert n to characters in s */
void itoa(int n, char s[])
{
	int i, sign;

	if ((sign = n) < 0) 	/* record sign */
		n = -n;		/* make n positive */
	i = 0;
	do {			/* generate digits in reverse order */
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0); /* delete it */ 
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

/* shellsort: sort v[0]...v[n-1] into increasing order */
void shellsort(int v[], int n)
{
	int gap, i, j, temp;

	for (gap = n/2; gap > 0; gap /= 2)
		for (i = gap; i < n; i++)
			for(j=i-gap; j>=0 && v[j]>v[j+gap]; j-=gap) {
				temp = v[j];
				v[j] = v[j+gap];
				v[j+gap] = temp;
			}
}

/* atoi: convert s to integer; version 2 */
int atoi1(char s[])
{
	int i, n, sign;

	for (i = 0; isspace(s[i]); i++) /* skip white space */
		;
	sign = (s[i] == '-') ? -1 : 1;
	if(s[i] == '+' || s[i] == '-') /* skip sign */
		i++;
	for(n = 0; isdigit(s[i]); i++)
		n = 10 * n + (s[i] - '0');
	return sign * n;
}
