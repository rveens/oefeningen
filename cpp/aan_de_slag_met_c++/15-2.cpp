#include <iostream>
#include <list>

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
		virtual void teken() const = 0;
};

class Driehoek : Figuur {
	private:
		int grootte;
	public:
		Driehoek(int grootte) : grootte(grootte) {
		}
		void teken() const {
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
};

class Rechthoek : public Figuur {
	protected:
		int breedte, hoogte;
	public:
		Rechthoek(int breedte, int hoogte) : breedte(breedte), hoogte(hoogte) {
		}
		virtual void teken() const {
			for (int i = 0; i < hoogte; ++i) {
				for (int r = 0; r < breedte; ++r)
					cout << symbool;
				cout << endl;
			}
		}
};

class OpenRechthoek : public Rechthoek {
	public:
		OpenRechthoek(int breedte, int hoogte) : Rechthoek(breedte, hoogte) {
		}
		void teken() const {
			for (int i = 0; i < hoogte; ++i)
			{
				for (int r = 0; r < breedte; ++r) {
					if (r == 0 || r == breedte-1 || i == 0 || i == hoogte-1)
						cout << symbool;
					else
						cout << ' ';
				}
				cout << endl;
			}
		}
};

int main(int argc, char *argv[])
{
	list<Figuur*> *a = new list<Figuur*>();
	
	a->push_back(new OpenRechthoek(5, 6));
	a->push_back(new OpenRechthoek(6, 6));
	a->push_back(new Rechthoek(7, 6));
	a->push_back(new OpenRechthoek(8, 6));

	list<Figuur*>::iterator 	pos = a->begin(),
						end;

	for (end = a->end(); pos != end; ++pos)
		(*pos)->teken();
		;
	return 0;
}
