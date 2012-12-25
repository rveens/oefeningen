
/* Write a function expand(s1, s2) that expands shorthand notations like a-z 
 * in the string s1 into the equivalent complete list abc...xyz in s2.
 * Allow for letters of either case and digits, and be prepared to handle cases
 * like a-b-c and a-z0-9 and -a-z. Arrange that a leading or trailing - is 
 * taken literaly. */

#include <stdio.h>

void expand2(char s1[], char s2[]);
int getinputline(char s[]);

//enum stage {foundnothing, mightberange, foundrangemark};
enum boolean {TRUE = 1, FALSE = 0};

int main(int argc, char *argv[])
{
	char line[1000];
	char lineoutput[1000];
	int linelength = 0;

	while((linelength = getinputline(line)) > 0) {
		expand2(line, lineoutput);
		printf("%s", lineoutput);
	}

	return 0;
}

int getinputline(char s[])
{
	int i, c;

	for(i = c = 0; (c = s[i] = getchar()) != '\n' && c != EOF; i++)
		;
	if(c == '\n')
		s[++i] = '\0';

	return i;
}

void expand2(char s1[], char s2[]) {
	int i;		// index for going through s2.
	int iw; 	// position to write in s2.
	int ir; 	// index used to write the range to s2.
	int c;		// Current character in the array.
	char lastChar;	// Last char that might have been the start of a range expression.
	enum boolean isRange = FALSE; // A boolean to check remember that the end of a range expression might be coming up.

	// a-b-z
	// Go through the s1 array.
	for(i = iw = c = 0; (c = s1[i]) != '\0' && c != EOF; i++)
		if (c >= 'a' && c <= 'z') { // Check if the c is between 'a' and 'z'.
			if(isRange) {	// If this char might be the end of a range expression.
				ir = (int)lastChar+1;
				while(ir <= c) {
					s2[iw++] = (char)ir; // TODO create range
					ir++;
				}
			}
			else
				s2[iw++] = s1[i]; // TODO write char to other array.
			lastChar = c; // Save the current char to lastChar. 
			isRange = FALSE; // Either done or it wasnt a range, we put it back.
		} else if (c == '-' && lastChar != '\0') { // If this char is '-' and lastChar is not null
			isRange = TRUE; // Set isRange to TRUE.
		} else { // Just a normal char, write it to the other array and put vars into normal situation.
			// TODO write char to other array, put everything to normal.
			s2[iw++] = s1[i];
			lastChar = '\0';
			isRange = FALSE;
		}	

	// put a null byte at the end of the s2 array.
	s2[iw] = '\0';
}

/* void expand(char s1[], char s2[]) */
/* { */
/* 	int i, iw, c; enum stage checkforrange = foundnothing; char firstrange 	= 0; */
/* 	int rangecounter 	= 0; */
/*  */
/* 	for(iw = i = c = 0; (c = s1[i]) != '\0' && c != EOF; i++ ) { */
/* 		if(c >= 'a' && c <= 'z')  { */
/* 			switch(checkforrange) { */
/* 				case foundnothing: // ooh, there might be a range coming up. */
/* 					checkforrange = mightberange; */
/* 					firstrange = c; // save the char, we might need it. */
/* 					s2[iw++] = c; */
/* 					break; */
				/* case mightberange: // nah its not, put it back */
				/* 	checkforrange = foundnothing; */
				/* 	break; */
/* 				case foundrangemark: // last one was '-', take action */
/* 					rangecounter = firstrange++; */
/* 					while(rangecounter <= c) */
/* 						s2[iw++] = (char)rangecounter++; */
/* 					// finished, put foundrangemark back. */
/* 					rangecounter = foundnothing; */
/* 					break; */
/* 			} */
/* 		} else if(c == '-') { */
/* 			checkforrange = foundrangemark; */
/* 		} else { // another not relevant char. */
/* 			s2[iw++] = c; */
/* 		} */
/* 	} */
/* 	s2[iw] = '\0'; */
/* } */
