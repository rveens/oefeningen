#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
	// Maak een bestand met wat getallen
	string filenaam = "bestand3.txt";
	ofstream uitvoer(filenaam.c_str());
	for (int i = 0; i < 100; i += 7)
		uitvoer << i * i << endl;

	// Sluit het bestand
	uitvoer.close();

	// Open het bestand voor invoer
	ifstream invoer(filenaam.c_str());

	// Ga na of alles in orde is:
	if (invoer.fail()) {
		cerr << "Bestand niet gevonden";
		cin.get();
		return 1;
	}

	// Lees het eerste getal
	int getal;
	invoer >> getal;
	if (invoer.fail()) {
		cerr << "Verkeerde informatie in het bestand";
		cin.get();
		return 2;
	}

	// Lees de volgende getallen
	while (invoer.good()) {
		cout << getal << endl;
		invoer >> getal;
	}
	invoer.close();
}
