
/* Exercise 4-2 Extend atof to handle scientific notation of the form
 * 	123.45e-6
 * where a floating-point number may be followed by e or E and an optionally
 * signed exponent. */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define 	MAXLINE		100

void reverse(char s[]);
void itoa(int n, char s[]);
double atofsn(char s[]);

int main(int argc, const char *argv[])
{
	double sum, atof(char []);
	char line[MAXLINE];
	int getinputline(char line[]);

	sum = 0;
	while (getinputline(line) > 0)
		printf("\t%g\n", atofsn(line));
	return 0;
}

/* atof: convert string s to double. Scientific notation is also supported. */
double atofsn(char s[])
{
	double val, power, eval, exponent;
	int i, sign, esign;

	for(i = 0; isspace(s[i]); i++) /* skip white spaces */
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for(val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if(s[i] == '.')
		i++;
	for(power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}

	if(s[i] == 'e' || s[i] == 'E')
		i++;
	esign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for(eval = 0.0; isdigit(s[i]); i++)
		eval = 10.0 * eval + (s[i] - '0');

	return pow( (sign * val / power), (esign * eval) );
}

/* atof: convert string s to double */
double atof(char s[])
{
	double val, power;
	int i, sign;

	for(i = 0; isspace(s[i]); i++) /* skip white spaces */
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for(val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if(s[i] == '.')
		i++;
	for(power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}
	return sign * val / power;
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

void reverse(char s[])
{
	int i, j, c;

	for (i = 0, j = strlen(s)-1;i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
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
