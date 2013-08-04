#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Voertuig {
	protected:
		int aantalWielen;
	public:
		Voertuig();
		Voertuig(int aw);
		string toString() const;
};

class Fiets : public Voertuig {
	private:
		int framenummer;
	public:
		Fiets();
		Fiets(int framenr);
		string toString() const;
};

Voertuig::Voertuig()
{
	this->aantalWielen = 4;
}

Voertuig::Voertuig(int aw)
{
	this->aantalWielen = aw;
}

string Voertuig::toString() const
{
	ostringstream os;

	os << "Dit voertuig heeft " << aantalWielen << " wielen." << endl;

	return os.str();
}

Fiets::Fiets()
{
	this->aantalWielen = 2;
}

Fiets::Fiets(int aw): Voertuig(aw)
{
}

string Fiets::toString() const
{
	ostringstream os;

	os << "Dit is een fiets." << endl;
	os << Voertuig::toString();
	
	return os.str();
}

int main(int argc, char *argv[])
{
	Voertuig automobiel = Voertuig();
	Voertuig vrachtwagen = Voertuig(8);

	Fiets batavus = Fiets();
	Fiets tandem = Fiets();

	cout << automobiel.toString();
	cout << vrachtwagen.toString();
	cout << batavus.toString();
	cout << tandem.toString();

	return 0;
}
