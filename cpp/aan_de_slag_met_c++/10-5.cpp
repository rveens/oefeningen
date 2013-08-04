#include <iostream>
#include <sstream>
#include <array>

using namespace std;

class Maand {
	private:
		const int eenJanuari1980 = 1; // dinsdag
		int maandgetal;
		int jaartal;
		bool isSchrikkeljaar(int jaar);
		int getAantalDagen(int maandnummer, int jaar);
	public:
		Maand(int maandnummer, int jaar) {

		}
		string toString() const;
};

bool Maand::isSchrikkeljaar(int jaar)
{
	return jaar % 4 == 0 && 
		jaar % 100 != 0 ||
		jaar % 400 == 0;
}

int Maand::getAantalDagen(int maand, int jaar)
{
	switch(maand) {
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12: return 31;

		case 4:
		case 6:
		case 9:
		case 11: return 30;

		case 2: if(isSchrikkeljaar(jaar))
				return 29;
			else
				return 28;
	}
	return 0;
}

string Maand::toString() const
{
	ostringstream os;

	os << __;

	return os.str();
}


int main(int argc, char *argv[])
{
	/* code */
	return 0;
}
