/*
 * Assignment 1.2. 
 * */
#include <iostream>

using namespace std;

double deterrperc(int v, double spc, double pc);

int main(int argc, const char *argv[])
{
	cout << deterrperc(10000, 0.005, 0.15) << '\n';
	return 0;
}

/* determine the error percentage of an election */
double deterrperc(int v, double spc, double pc)
{
	int ninv;

	// totaal aantal foute votes
	ninv = v * (pc * spc);

	return (ninv / v) * 100.00;
}
