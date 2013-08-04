#include <iostream>
#include <string>
#include <sstream>
#include <ostream>

using namespace std;

class Tijdstip {
	private:
		int uur, minuut, seconde;
	public:
		Tijdstip(int uur = 0, int minuut = 0, int seconde = 0) : 
			uur(uur), minuut(minuut), seconde(seconde) {
		}
		Tijdstip operator+(Tijdstip t);
		Tijdstip &operator+=(Tijdstip t);
		Tijdstip &operator+=(int t);
		friend ostream &operator<<(ostream &o, const Tijdstip &t);
};

Tijdstip Tijdstip::operator+(Tijdstip t )
{
	int uurt = uur + t.uur;
	int minuutt = uur + t.minuut;
	int secondet = uur + t.seconde;

	return Tijdstip(uurt, minuutt, secondet);
}

Tijdstip &Tijdstip::operator+=(Tijdstip t)
{
	uur += t.uur;
	minuut += t.minuut;
	seconde += t.seconde;

	return *this;
}

Tijdstip &Tijdstip::operator+=(int t)
{
	seconde += t;

	return *this;
}

ostream &operator<<(ostream &o, const Tijdstip &t)
{
	o << "uur: " << t.uur << endl;
	o << "minuut: " << t.minuut << endl;
	o << "seconde: " << t.seconde << endl;

	return o;
}

int main(int argc, char *argv[])
{
	Tijdstip v(3, 5, 10);
	Tijdstip k(5, 9, 14);

	cout << "v + k" << endl;
	cout << "v voor: " << endl;
	cout << v << endl;
	cout << (v + k) << endl;
	cout << "v na: " << endl;
	cout << v << endl;

	cout << "k += 150" << endl;
	cout << "k voor" << endl;
	cout << k << endl;
	k += 150;
	cout << "k na" << endl;
	cout << k << endl;

	return 0;
}
