
/* Write a function htoi(s) which converts a string of hexadecimal digits 
 * (including an optional 0x or 0X) into its equivalent integer value.
 * The allowable digits are 0 through 9, a through f and A through F.
 */

#include <stdio.h>

int htoi(char s[]);
int getinputline(char s[]);

int main(int argc, const char *argv[])
{
	int i, c, size;
	char line[1000];

	while( (size = getinputline(line)) > 0) {
		printf("%d\n", htoi(line));
	}
	return 0;
}

int htoi(char s[])
{
	int i, lastPos, c, total;

	c = total = lastPos = 0;

	for(i = 0; (c = s[i]) != '\0' && c != EOF;)
		i++;

	lastPos = i-1;

	for(i = 0; (c = s[lastPos-i]) && i >= 0; i++ ) {
		if(c == 'x' || c == 'X')
			break;
		if (c >= 0 && c <= 9)
			total += (c^i);
		if (c >= 'a' && c <= 'f')
			total += ( (c - (('a' - '0')+7) )^i );
		if(c >= 'A' && c <= 'F')
			total += ( (c - (('A' - '0')+7) )^i );
	}
	return total;
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
