#include <iostream>
#include <string>

using namespace std;

class Uitgave {
	protected:
		int prijs;
		string titel;
	public:
		Uitgave(int p = 0, string t = "geen naam");
		void toScreen() const;
		void inPutVales();
};

Uitgave::Uitgave(int p, string t)
	: prijs(p), titel(t) {
}

void Uitgave::toScreen() const
{
	cout << "Deze uitgave draagt de naam " << titel << endl;
	cout << "De prijs van deze uitgave is " << prijs << endl;
}

void Uitgave::inPutVales()
{
	cout << "Geef de naam van de titel" << endl;
	getline(cin, titel);
	cout << "Geef de prijs op" << endl;
	cin >> prijs;
	cout << "U gaf " << titel << " op als titel en, " << endl;
	cout << prijs << " op als prijs." << endl;
}


class Tijdschrift : public Uitgave {
	private:
		string uitgaveMaand;
	public:
		Tijdschrift(int p = 0, string t = "geenTitel", string um = "Januari");
		void inPutVales();
		void toScreen() const;
};

Tijdschrift::Tijdschrift(int p, string t, string um)
	: Uitgave(p, t), uitgaveMaand(um) {
}

void Tijdschrift::toScreen() const
{
	Uitgave::toScreen();
	cout << "De maand van uitgave is " << uitgaveMaand << endl;
}

void Tijdschrift::inPutVales() {
	Uitgave::inPutVales();
	cout << "Geef de naam van de maand" << endl;
	getline(cin, uitgaveMaand);

	cout << "U gaf " << uitgaveMaand << " op als maand van uitgave." << endl;
}

class Boek : public Uitgave {
	private:
		int aantalBladzijden;
	public:
		Boek(int p = 0, string t = "geenTitel", int ab = 0);
		void toScreen() const;
		void inPutVales();
};

Boek::Boek(int p, string t, int ab)
	: Uitgave(p, t), aantalBladzijden(ab) {
}

void Boek::toScreen() const
{
	Uitgave::toScreen();
	cout << "Het aantal bladzijden van dit boek is " << aantalBladzijden << endl;
}

void Boek::inPutVales()
{
	Uitgave::inPutVales();
	cout << "Geef het aantal bladzijden op" << endl;
	cin >> aantalBladzijden;
	cout << "U gaf " << aantalBladzijden << " op als aantalBladzijden" << endl;
}

class CD : Uitgave {
	private:
		int minSpeeltijd;
	public:
		CD(int p = 0, string t = "geenTitel", int ms = 0);
		void toScreen() const;
		void inPutVales();
};

CD::CD(int p, string t, int ms)
	: Uitgave(p, t), minSpeeltijd(ms) {
}

void CD::toScreen() const
{
	Uitgave::toScreen();
	cout << "Het aantal minuten speeltijd is " << minSpeeltijd << endl;
}

void CD::inPutVales()
{
	Uitgave::inPutVales();
	cout << "Geef het aantal minuten speeltijd van de CD op" << endl;
	cin >> minSpeeltijd;
	cout << "U gaf " << minSpeeltijd << " op als minuten speeltijd." << endl;
}

int main(int argc, char *argv[])
{
	Uitgave u = Uitgave();
	u.inPutVales();
	u.toScreen();

	Tijdschrift t = Tijdschrift();
	t.inPutVales();
	t.toScreen();

	Boek b = Boek();
	b.inPutVales();
	b.toScreen();

	CD c = CD();
	c.inPutVales();
	c.toScreen();

	return 0;
}
