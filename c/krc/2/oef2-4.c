/* Write an alternate version of squeeze(s1, s2) that deletes each character
 * in s1 that matches any character in the string s2.*/

#include <stdio.h>

int getinputline(char line[]);
void squeeze(char s1[], char s2[]);
void sqze(char s[], int c);

int main(int argc, const char *argv[])
{
	char line[1000];
	int lineLength;

	while( (lineLength = getinputline(line)) > 0) {
		squeeze(line, "test");
		printf("%s", line);
	}
	return 0;
}

/* Ga door string1.
 * Schrijf elk karakter naar s1 als:
 * 	- hij niet voorkomt in s2[].
 * */
void squeeze(char s1[], char s2[])
{
	int iout, iin, writepos, invalidchar; 

	writepos = 0;

	for(iout = 0; s1[iout] != '\0'; iout++){
		invalidchar = 0;
		for(iin = 0; s2[iin] != '\0'; iin++)
			if(s1[iout] == s2[iin])
				invalidchar = 1;
		s1[writepos] = s1[iout];
		if(!invalidchar)
			writepos++;
	}
	s1[writepos] = '\0';
}

/* squeeze: delete all c from s */ 
void sqze(char s[], int c)
{
	int i, j;

	for(i = j = 0; s[i] != '\0'; i++)
		if(s[i] != c)
			s[j++] = s[i];
	s[j] = '\0';
}

int getinputline(char line[])
{
	int i, c;

	for(i = c = 0; (line[i] = c = getchar()) != '\n' && c != EOF; i++)
		;
	if(line[i] == '\n')
		line[++i] = '\0';

	return i;
} 
