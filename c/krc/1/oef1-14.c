#include <stdio.h>

#define MAX 128

/* Write a program to print a histogram of the lengths of words in its input. 
 * It is easy to draw the histogram with the bars horizontal; a vertical orientation is more challenging */
main()
{
	int c;
	int ndigit[MAX];

	int i = 0;
	for(i = 0; i < MAX; i++)
		ndigit[i] = 0;

	while((c = getchar()) != EOF)
	{		
		++ndigit[c];
	}


	// Determine the biggest amount of numbers.
	int largestAmount = 0;
	for(i = 0; i < MAX; i++)
		if (ndigit[i] > largestAmount)
			largestAmount = ndigit[i];

	printf("Hoogste nummer is: %d\n", largestAmount);

	// For each amount look if there is an position in the array. That can be printed.
	int x;
	for(i = largestAmount; i >= 0; i--) // For every row of size.
	{
		int sign = 'o';
		for(x = 0; x < MAX; x++) // Look if there is a digit with a size equal of lower and print a sign.
		{
			if (ndigit[x] <= i )
			{
				sign = '*';
			}
			printf("%c", sign);
			sign = 'o';
		}
		printf("\n");
	}
}
