/* Exercise 4-13
 * Write a recursive version of function reverse(s), which reverses the string
 * s in place. */
#include <stdio.h>
#include <string.h>

void recreverse(char s[]);
void reverse(char s[]);
void reverse1(char s[]);
void swap(char v[], int i, int j);

int main(int argc, const char *argv[])
{
	char s[] = "appelflap";

	recreverse(s);
	//reverse1(s);
	printf("%s\n", s);

	return 0;
}

/*reverse the given string in place. Use recursion*/
void recreverse(char s[])
{
	static int iw = 0, ir = 0;
	int c = s[ir];

	if(c) {
		ir++;
		recreverse(s);
		s[iw++] = c;
	}
}

void reverse1(char s[])
{
	static int i = 0, n;
	int c = s[i];

	if (c) {
		i++;
		reverse(s);
		s[n-i] = c;
		i--;
	} else {
		n = i;
	}
}

/*
 *[>reverse the given string in place. Use recursion<]
 *void recreverse(char s[], int ir)
 *{
 *        static int iw = 0;	// index write
 *
 *        // we weten dat de volgende /0 is, maar we gaan nog 1 keer door = fout
 *        if(s[ir+1] != '\0')
 *                recreverse(s, ++ir);
 *        swap(s, iw++, ir);
 *        if(ir == 1)
 *                s[iw] = '\0';
 *}
 */

void swap(char v[], int i, int j)
{
	int temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
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
