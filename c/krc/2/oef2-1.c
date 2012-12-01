/* Write a program to determine the ranges of char, short, int and long values,
 * both signed and unsigned, by printing appropriate values from standard 
 * headers and by direct computation. Harder if you compute them: determine
 * the ranges of various floating-point types. */

#include <stdio.h>

int main(int argc, const char *argv[])
{
	char 		karakter;
	unsigned char	nietGetekendKarakter;
	int 		integer;
	unsigned int 	nietGetekendInteger;
	long 		longInt;
	unsigned long 	nietGetekendLongInt;
	short 	 	shortInt;
	unsigned short 	nietGetekendShortInt;

	nietGetekendShortInt = nietGetekendLongInt = nietGetekendInteger = karakter = integer = longInt = shortInt = nietGetekendKarakter = 1;

	// Char
	int temp = 0;
	while(karakter > 0)
		karakter++;
	temp = --karakter;
	while (karakter < 0)
		karakter--;
	karakter++;

	printf("char: %d tot %d\n", karakter, temp);

	// int
	temp = 0;
	while (integer > 0)
		integer++;
	temp = --integer;

	while (integer < 0)
		integer--;
	integer++;

	printf("int: %d tot %d\n", integer, temp);

	// long int
	long temp1 = 0;

	while(longInt > 0)
		longInt++;
	temp1 = --longInt;

	while(longInt < 0)
		longInt--;
	longInt++;

	printf("long int: %ld tot %ld\n", longInt, temp1);

	// short int
	short temp2 = 0;

	while(shortInt > 0)
		shortInt++;
	temp2 = --shortInt;

	while(shortInt < 0)
		shortInt--;
	shortInt++;

	printf("short int: %hd tot %hd\n", shortInt, temp2);

	// unsigned char
	temp = 0U;
	while(nietGetekendKarakter != 0)
		nietGetekendKarakter++;
	nietGetekendKarakter--; 

	printf("Unsignedchar: 0 tot %d\n", nietGetekendKarakter);


	// unsigned int
	temp = 0;
	while (nietGetekendInteger != 0)
		nietGetekendInteger++;
 	nietGetekendInteger--;

	printf("unsigned int: 0 tot %d\n", nietGetekendInteger);

	// unsigned long int
	temp1 = 0U;

	while(nietGetekendLongInt != 0U)
		nietGetekendLongInt++;
	nietGetekendLongInt--; 

	printf("unsigned long int: 0 tot %ld\n", nietGetekendLongInt);

	// unsigned short int
	temp2 = 0U;

	while(nietGetekendShortInt !=  0U)
		nietGetekendShortInt++;
	nietGetekendShortInt--; 

	printf("unsigned short int: 0 tot %d\n", nietGetekendShortInt);

	return 0;
}
