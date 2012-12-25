#include <stdio.h>
#include <time.h>

int binsearch(int x, int v[], int n);
int binsearchrevised(int x, int v[], int n);

int main(int argc, const char *argv[])
{
	clock_t start, end;
	double cpu_time_used;

	int test[1000];
	int i;

	for (i = 0; i < 1000; i++)
		test[i] = i+1;

	start = clock();

	for(i = 0; i < 1000000000; i++) {
		printf("%d\n", binsearchrevised(-1, test, 1000));
		//printf("%d\n", binsearch(-1, test, 1000));
	}
	
	end = clock();

	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

	printf("Time used: %f", cpu_time_used);
	return 0;
}

int binsearchrevised(int x, int v[], int n)
{
	int low, high, mid;
	
	low = 0;
	high = n - 1;

	while(low <= high && x != v[mid]) {
		mid = (low+high) / 2;

		if(x < v[mid])
			high = mid - 1;
		else
			low = mid + 1;
	}
	
	if(x == v[mid]) // found
		return mid;
	else 		// not found
		return -1;
}

/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] 
 * array must be sorted.*/
int binsearch(int x, int v[], int n)
{
	int low, high, mid; /* Numbers that represent the range and the middle 
				of that range.*/
	// The range decreases depending on the value of the 'mid' position

	low = 0; 	// low is the first part of the array.
	high = n - 1;	// high is the last position of the array.

	while(low <= high) // while low is less than high.
       	{
		mid = (low+high) / 2; 	// Put mid at the center of the range.
		if(x < v[mid])		// x is below mid.	
			high = mid - 1;  
		else if(x > v[mid]) 	// x is above mid.
			low = mid + 1;
		else /* found match */
			return mid;
	}
	return -1;
}
