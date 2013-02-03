
/*
* Exercise 4-14. Define a macro swap(t, x, y) that interchanges two arguments
* of type t. (Block structure will help)
*/
#include <stdio.h>

#define	swap(t, x, y)	do{t z=x; x=y; y=z;}while(0)

int main(int argc, const char *argv[])
{
	double test 	= 50.78;
	int test2 	= 20;

	swap(int, test, test2);

	printf("%d", test2);
	return 0;
}
