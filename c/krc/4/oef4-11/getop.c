#include <stdio.h>
#include <ctype.h>
#include "calc.h"

/* getop: get next operator or numeric operand */
int getop(char s[])
{
	int i;			// Index for putting characters into s.
	int c;			// The current character.
	static int temp;	// The last character.

	i = 0;
	// Skip spaces at the start.
	while ((s[0] = c = temp = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if(c == '=') {
		c = s[++i] = getch();
		if(!isalpha(c))
			s[--i] = c = temp;
	}
	if(isalpha(c)) { // Found alfanumeric.
		while (isalpha(s[++i] = temp = c = getch()))
			;
		s[i] = '\0';
		return ALPHANUMERIC;
	}
	if (!isdigit(c) && c != '.' && c != '-') 
		return c;

	if(c == '-') {
		if( !isdigit( (c = getch()) ) )
			return c = temp; // return '-'
		else
			s[++i] = c; // Save the current character in the array.
	}

	if (isdigit(c)) 	/* collect integer part */
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')		/* collect fraction part */
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		c = temp;
	return NUMBER;
}
