#include <iostream>

using namespace std;

class Figuur {
	protected:
		char symbool;
	public:
		Figuur(char symbool = '*')
			: symbool(symbool) {
		}

		void setSymbool(char sym) {
			symbool = sym;
		}
};

class Rechthoek : public Figuur {
	private:
		int breedte, hoogte;
	public:
		Rechthoek(int breedte, int hoogte)
			: breedte(breedte), hoogte(hoogte) {
		}
		void teken() const;
};

class Driehoek : public Figuur {
	private:
		int grootte;
	public:
		Driehoek(int grootte)
			: grootte(grootte) {
		}
		void teken() const;
};

class Ruit : public Figuur {
	private:
		int grootte;
	public:
		Ruit(int grootte) : grootte(grootte) {
		}
		void teken() const;
};

int main(int argc, char *argv[])
{
	Rechthoek rh(14, 4);
	rh.teken();
	cout << endl << endl;

	Driehoek dh(7);
	dh.setSymbool('#');
	dh.teken();

	Ruit r(3);
	r.setSymbool('$');
	r.teken();
}

// Implementatie
void Rechthoek::teken() const {
	// Maak een regel met symbolen, gescheiden door een spatie
	// Bijvoorbeeld:
	// * * * * * * * * *
	string regel;
	for (int k = 0; k < breedte; ++k) {
		regel += symbool;
		regel += ' ';
	}
	// Zet de zojuist gemaakte regels onder elkaar
	for (int r = 0; r < hoogte; ++r)
		cout << regel << endl;
}

void Driehoek::teken() const {
	// Maak een regel bestaande uit een aantal spaties,
	// gevolgd door een symbool en een spatie, bijvoorbeeld:
	// _______* 	(spaties zijn hier weergeven met _)
	string regel;
	for (int k = 0; k < grootte; ++k)
		regel += ' ';
	regel += symbool;
	regel += ' ';
	// Zet een aantal regels onder elkaar
	for (int r = 0; r < grootte; ++r) {
		cout << regel << endl;
		// Verwijder het eerste karakter uit de regel
		regel.erase(0, 1);
		// Voeg aan het eind een symbool en een spatie toe
		regel += symbool;
		regel += ' ';
	}
}

void Ruit::teken() const {
	string regel;

	for (int k = 0; k < grootte; ++k)
		regel += ' ';
	regel += symbool;
	regel += ' ';
	// Zet een aantal regels onder elkaar
	for (int r = 0; r < grootte; ++r) {
		cout << regel << endl;
		// Verwijder het eerste karakter uit de regel
		regel.erase(0, 1);
		// Voeg aan het eind een symbool en een spatie toe
		regel += symbool;
		regel += ' ';
	}
	for (int r = 0; r < grootte; ++r) {
		cout << regel << endl;
		// Verwijder het eerste karakter uit de regel
		regel.insert(0, " ");
		// Voeg aan het eind een symbool en een spatie toe
		regel.erase(regel.size() - 1, regel.size());
		regel.erase(regel.size() - 1, regel.size());
	}
}
