/*
 * Assignment 1.2. Write a program that prompts the user to enter the voting
 * parameters (number of votes, percentage spread between candidates, voting 
 * error percentage), then performs 500 simulation trials and reports the ratio 
 * calculated with (number of invalid trials/total number of trials) * 100.
 *
 * The program should take care to verify the user's chosen simulation paramters 
 * are within range. If necessary it has to reprompt.
 * Because of the randomness the results will vary from run to run.
 * */
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <math.h>
#include <limits>

using namespace std;

double DetermineVotingInvalidRatio(double votes, double spreadPercentage, double failurePercentage);
bool DoElectionTest(double votes, double spreadPercentage, double failurePercentage);
bool GetVoteChance(double percentage);

#define 	MAX_TRIALS	500.0

int main(int argc, const char *argv[])
{
	srand(time(NULL));

	double nvoters, pspread, vperr;

	nvoters = pspread = vperr = 0.0;

	while (true) {
		cout << "Please enter the number of votes: ";
		cin >> nvoters;
		if (nvoters > 0 ) break;
		if (cin.fail()) {
			cout << "data entered is not of double type\n";
			cin.clear();
			cin.ignore( numeric_limits< streamsize >::max(), '\n');
		} else
			cout << "Error: must be positive\n";
	}

	while (true) {
		cout << "Please enter the spread percentage: ";
		cin >> pspread;
		if (pspread > 0 ) break;
		if (cin.fail()) {
			cout << "data entered is not of double type\n";
			cin.clear();
			cin.ignore( numeric_limits< streamsize >::max(), '\n');
		} else
			cout << "Error: must be positive\n";
	}

	while (true) {
		cout << "Please enter the error percentage: ";
		cin >> vperr;
		if (vperr > 0) break;
		if (cin.fail()) {
			cout << "data entered is not of double type\n";
			cin.clear();
			cin.ignore( numeric_limits< streamsize >::max(), '\n');
		} else
			cout << "Error: must be positive\n";
	}

	cout << DetermineVotingInvalidRatio(nvoters, pspread, vperr) << '\n';
	return 0;
}

double DetermineVotingInvalidRatio(double votes, double spreadPercentage, double failurePercentage)
{
	// 500 keer test draaien
	// aantal keer fout tellen
	// aantal keer fout delen door totaal (500) en dan keer 100
	//
	// Test draaien:
	// aantal personen die waarbij de kans niet eerlijk verdeeld is:
	// fout_personen = spreadPercentage * votes  
	// partij1: fout_personen * (rand() % (100 / failurePercentage)) + 1
	// partij2: fout_personen * (rand() % (100 / failurePercentage)) + 1
	
	double i, amountInError = 0;

	cout << "amountinError: " << amountInError;
	for (i = 0; i < MAX_TRIALS; i++)
		if (DoElectionTest(votes, spreadPercentage, failurePercentage))
			amountInError++;

	cout << "amountinError: " << amountInError << '\n';

	return (amountInError / MAX_TRIALS) * 100;
}

bool DoElectionTest(double votes, double spreadPercentage, double failurePercentage)
{
	double fout_personen = spreadPercentage * votes;
	double partij1_fout_votes, partij2_fout_votes;
	int i;

	partij1_fout_votes = partij2_fout_votes = 0;

	for (i = 0; i < fout_personen; i++)
		if (GetVoteChance(failurePercentage * 100))
			partij1_fout_votes++;
	for (i = 0; i < fout_personen; i++)
		if (GetVoteChance(failurePercentage * 100))
			partij2_fout_votes++;

	cout << "kans: " << failurePercentage * 100 << " partij1: " << partij1_fout_votes << " partij2: " << partij2_fout_votes << '\n';

	return partij1_fout_votes > partij2_fout_votes;
}

bool GetVoteChance(double percentage)
{
	return fmod(rand(), 100) < percentage;
}
