#include <iostream>
#include <string>

using namespace std;

const int MIN_BREEDTE = 1, MIN_HOOGTE = 1,
      MAX_BREEDTE = 25, MAX_HOOGTE = 25;

class Rechthoek {
	protected:
		int hoogte;
		int breedte;
	public:
		Rechthoek(int h = 5, int b = 5);
		void print() const;
};

Rechthoek::Rechthoek(int h, int b)
	: hoogte(h), breedte(b) {
}

void Rechthoek::print() const
{
	for (int r = 0; r < hoogte; r++) {
		for (int k = 0; k < breedte; k++)
			cout << "* ";
		cout << endl;
	}
	cout << endl;
}


class FlexRechthoek : public virtual Rechthoek {
	protected:
		char symbool;
	public:
		FlexRechthoek(int ht = 5, int br = 5, char sym = '*');
		void breder();
		void hoger();
		void print() const;
};

FlexRechthoek::FlexRechthoek(int ht, int br, char sym)
	: Rechthoek(ht, br), symbool(sym) {
}

void FlexRechthoek::breder()
{
	if (breedte < MAX_BREEDTE)
		breedte++;
}

void FlexRechthoek::hoger()
{
	if (hoogte < MAX_HOOGTE)
		hoogte++;
}

void FlexRechthoek::print() const
{
	for ( int r = 0; r < hoogte; r++) {
		for (int k = 0; k < breedte; k++)
			cout << symbool << ' ';
		cout << endl;
	}
	cout << endl;
}


class Venster : public virtual Rechthoek {
	public:
		Venster(int h = 1, int b = 1);
		void print() const;
};

Venster::Venster(int h, int b) :
	Rechthoek(h, b) {
}

void Venster::print() const
{
	for (int r = 0; r < hoogte; r++) {
		for (int k = 0; k < breedte; k++) {
			if (k == 0 || r == 0 || k == breedte-1 || r == hoogte-1)
				cout << "* ";
			else
				cout << "  ";
		}
		cout << endl;
	}
	cout << endl;
}

class VensterMetTitel : public Venster {
	protected:
		string titel;
	public:
		VensterMetTitel(int h = 1, int b = 1, string titel = "titel");
		void print() const;
};

VensterMetTitel::VensterMetTitel(int h, int b, string titel) :
	Venster(h, b), titel(titel) {
}

void VensterMetTitel::print() const
{
	int lengthBeforeTitle = ( (breedte - titel.length()) / 2);

	for (int r = 0; r < hoogte; r++) {
		for (int k = 0; k < breedte; k++) {
			if (r == 0 && breedte > titel.length() ) {
				if (k > lengthBeforeTitle &&
					k < (lengthBeforeTitle + titel.length()) )
					cout << titel.at((k - lengthBeforeTitle)) << " ";
				else
					cout << "* ";
			} else if (k == 0 || r == 0 || k == breedte-1 || r == hoogte-1)
				cout << "* ";
			else
				cout << "  ";
		}
		cout << endl;
	}
	cout << endl;
}

class VensterMetTitelFlex : public VensterMetTitel, public FlexRechthoek {
	public:
		VensterMetTitelFlex(int h = 5, int b = 5, string titel = "titel");
		void print() const;
};

VensterMetTitelFlex::VensterMetTitelFlex(int h, int b, string titel)
	: Rechthoek(h, b), VensterMetTitel(h, b, titel), FlexRechthoek(h, b, '*')
{

}

void VensterMetTitelFlex::print() const
{
	VensterMetTitel::print();
}

int main(int argc, char *argv[])
{
	VensterMetTitelFlex vmtf = VensterMetTitelFlex(12, 12, "test");
	vmtf.print();
	vmtf.hoger();
	vmtf.breder();
	vmtf.breder();
	vmtf.breder();
	vmtf.breder();
	vmtf.print();

	return 0;
}
