
/* Write a loop equivalent to the for loop above without using && or ||. 
 *
 * for (i=0; i<lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
 * 	s[i] = c;
 */

#include <stdio.h>

int main(int argc, const char *argv[])
{
	int i, lim, c;
	char s[i];

	for (i = 0; i < lim - 1 && (c=getchar()) != '\n' && c != EOF; ++i)
		s[i] = c;

	for(i = 0; (c = s[i] = getchar()) != EOF; i++ ) {
		if(c == '\n')
			break;
		if(i < lim - 1)
			break;
	}

	return 0;
}
