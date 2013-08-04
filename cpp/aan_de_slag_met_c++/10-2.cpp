#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Voorraad {
	private:
		int klein;
		int groot;
	public :
		Voorraad(int k = 0, int g = 0)
			: klein(k), groot(g)
		{

		}

		Voorraad som( const Voorraad &x) const;
		string toString() const;

		Voorraad &operator+=(const Voorraad &v);
		Voorraad &operator-(); //unair
		Voorraad &operator-(const Voorraad &v); // binair
		friend Voorraad &operator*(double d, Voorraad &v); // vermenigvuldiging met
		Voorraad &operator*(double d);
};

Voorraad &Voorraad::operator+=(const Voorraad &v)
{
	groot += v.groot;
	klein += v.klein;

	return *this;
}

Voorraad &Voorraad::operator-()
{
	groot *= -1;
	klein *= -1;

	return *this;
}

Voorraad &Voorraad::operator-(const Voorraad &v)
{
	groot -= v.groot;
	klein -= v.klein;

	return *this;
}

Voorraad &operator*(double d, Voorraad &v)
{
	d *= v.groot;
	d *= v.klein;

	return v;
}

Voorraad &Voorraad::operator*(double d)
{
	groot += d;
	klein  += d;

	return *this;
}

Voorraad Voorraad::som( const Voorraad &x) const {
	Voorraad resultaat;
	resultaat.klein = klein + x.klein;
	resultaat.groot = groot + x.groot;

	return resultaat;
}

string Voorraad::toString() const {
	ostringstream os;
	os << klein << " klein en " << groot << " groot.";
	return os.str();
}

int main(int argc, char *argv[])
{
	Voorraad v(3, 2);
	Voorraad r(4, 3);
	Voorraad k(4, 2);

	cout << "v = -v" << endl;
	cout << "voor:" << endl;
	cout << v.toString() << endl;
	v = -v;
	cout << "na:" << endl;
	cout << v.toString() << endl;

	cout << "r = r - r" << endl;
	cout << "voor:" << endl;
	cout << r.toString() << endl;
	r = r -r;
	cout << "na:" << endl;
	cout << r.toString() << endl;

	cout << "k = k * 1.5" << endl;
	cout << "voor:" << endl;
	cout << k.toString() << endl;
	k = k * 1.5;
	cout << "na:" << endl;
	cout << k.toString() << endl;

	cout << "-v * 1.5" << endl;
	cout << "voor:" << endl;
	cout << v.toString() << endl;
	-v * 1.5;
	cout << "na:" << endl;
	cout << v.toString() << endl;

	k = 1.5 * k;

	return 0;
}
