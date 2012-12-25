
/* Write a function escape(s, t) that converts characters like newline and tab
 * into visible escape sequences like \n and \t as it copies the string to s.
 * Use a switch. Write a function for the other direction as well, converting
 * escape sequences into real characters. */

#include <stdio.h>

void escape(char s[], char t[]);
void unescape(char s[], char t[]);
int getinputline(char s[]);

int main(int argc, const char *argv[])
{
	char line[1000];
	char line2[1000];
	int linesize;

	while ( (linesize = getinputline(line)) > 0) {
		unescape(line, line2);
		printf("%s", line2);
	}
	return 0;
}

int getinputline(char s[])
{
	int i, c;

	i = c = 0;

	while( (s[i] = c = getchar()) != EOF && c != '\n')
		i++;
	if(c == '\n')
		s[++i] = '\0';
	return i;
}

void unescape(char s[], char t[])
{
	int i, ii, c, ec; /* ii insert-index, i index, c current char, ec escape check */

	ec = ii = i = c = 0;

	for(;(c = s[i]) != EOF && c != '\0'; ) {
		switch(c)
		{
			case '\\':
				ec = 1;
				t[ii++] = c;
				i++;
				break;
			case 'n':
				if(ec) {
					t[ii-1] = '\n';
					i++;
				}
				else  {
					t[ii++] = c;
					i++;
				}
				break;
			case 't':
				if(ec) {
					t[ii-1] = '\t';
					i++;
				}
				else  {
					t[ii++] = c;
					i++;
				}
				break;
			default:
				if(ec)
					ec = 0;
				t[ii++] = c;
				i++;
				break;
		}
	}
	t[ii] = '\0';
}

void escape(char s[], char t[])
{
	int i, ii, c; /* ii insert index, i index, c current char. */

	ii = i = c = 0;

	for(; (c = s[i]) != EOF && c != '\0'; ) {
		switch(c) {
			case '\t':
				t[ii++]	= '\\';
				t[ii++]	= 't';
				i++;
				break;
			case '\n':
				t[ii++]	= '\\';
				t[ii++]	= 'n';
				i++;
				break;
			default:
				t[ii++] = c;
				i++;
				break;
		}
	}
	t[ii] = '\0';
}
