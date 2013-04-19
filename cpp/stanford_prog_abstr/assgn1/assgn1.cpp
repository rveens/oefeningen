/*
 * Assignment 1.1. Write a predicate function IsPerfect that takes an integer 
 * n and returns true if n is perfect, and false otherwise. 
 *
 * Test your implementation by writing a main program that uses the
 * IsPerfect function to check for perfect numbers in the range 1 to 10000 by 
 * testing each number in turn. 
 *
 * When a perfect number is found, your program should print it. The first two 
 * perfect numbers are 6 and 28, there are two others in the range to 10000.
 */

#include <iostream>

using namespace std;

bool IsPerfect(int n);

#define 	 MAXTEST 	10000

int main(int argc, const char *argv[])
{
	int i;

	for (i = 1; i < MAXTEST; i++)
		if (IsPerfect(i))
			cout << i << "\n";

	return 0;
}

/* 
 * Write a predicate function IsPerfect that takes an integer n and returns true
 * if n is perfect, and false otherwise.
 */
bool IsPerfect(int n)
{
	int i, p = 0;

	for (i = 1; i < n; i++)
		if (n % i == 0)
			p += i;

	return p == n; 
}
