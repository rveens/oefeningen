/* Write a program to check a C program for rudimentary syntax errors like un-
 * balanced parentheses, brackets and braces. Don't forget about quotes, both
 * single and double, escape sequences and comments. (This program is hard if 
 * you do it in full generality */

#include <stdio.h>

#define 	MAXINPUT	1000

int checkValidity(char c, char stackchar);
void checkSyntax(char s[]);
int relevantCharacterCheck(char c);
int strContains(char s[], char character);
int getinput(char s[], int maxinput);

char left[] = "({[\'\"";
char right[] = ")}]\'\"";

int main(int argc, const char *argv[])
{
	char line[MAXINPUT];
	int lineLength;

	lineLength = 0;

	checkSyntax(line);

	return 0;
}

void checkSyntax(char s[])
{
	char stack[MAXINPUT];
	int i, c, si;

	i = c = si = 0;

	while ( (c = s[i] = getchar()) != EOF) {
		printf("%c", c);
		if(relevantCharacterCheck(c))
		{
			if(strContains(left, c) && strContains(right, c))
				;
			else if(strContains(left, c)) {
				stack[si++] = c;
				stack[si] = '\0';
			} else if(strContains(right, c)) { 
				// Something is wrong! HALT! 
				if (!checkValidity(c, stack[si-1])) {
					printf("INVALID!\n");
					return;
				} else {
					// Remove the character from the stack.
					stack[si--] = '\0';
				}
			}
		}
		i++;
	}
	// Everything went fine!
	printf("VALID!\n");
}

int strContains(char s[], char character)
{
	int i, c;

	i = c = 0;

	for(i = 0; (c = s[i]) != '\0'; i++)
		if(c == character)
			return 1;
	return 0;
}

int checkValidity(char c, char stackchar)
{
	if(stackchar == '(' && c == ')')
		return 1;
	else if(stackchar == '{' && c == '}')
		return 1;
	else if(stackchar == '[' && c == ']')
		return 1;
	else if(stackchar == '\"' && c == '\"')
		return 1;
	else if(stackchar == '\'' && c == '\'')
		return 1;
	else
		return 0;
}

int relevantCharacterCheck(char c)
{
	switch(c) {
		case '(':
		case ')':
		case '{':
		case '}':
		case '[':
		case ']':
		case '\'':
		case '\"':
			return 1;
		default:
			return 0;
	}
}


int getinput(char s[], int maxinput)
{
	int i, c;

	i = c = 0;

	while ( (c = s[i] = getchar()) != EOF && c != '\n' )	
		i++;

	if(s[i] == '\n')
		s[++i] = '\0';

	return i; // i is the size of the array
}
