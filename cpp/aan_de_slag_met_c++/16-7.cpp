#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Datum {
	private:
		int dag, maand, jaar;
	public:
		Datum(int d = 0, int m = 0, int j = 0) : dag(d), maand(m), jaar(j) {
		}
		string toString() const
		{
			ostringstream os;
			os << jaar << '-' << maand << '-' << jaar;

			return os.str();
		}

		friend ostream &operator<<(ostream &uit, const Datum &d);
		friend istream &operator>>(istream &in, Datum &d);
};

void skip (istream &in) {
	// pre: er is nog iets te lezen in de stream in
	char ch;
	do {
		in >> ch;
	} while (in && !isdigit(ch) && ch != '-');

	if (in) {
		in.putback(ch);
	}
}

ostream &operator<<(ostream &uit, const Datum &d)
{
	/* cout << d.jaar << '-' << d.maand << '-' << d.jaar << endl; */
	return uit << d.jaar << '-' << d.maand << '-' << d.jaar;
}

istream &operator>>(istream &in, Datum &d)
{
	skip(in);
	in >> d.jaar;
	skip(in);
	in >> d.maand;
	skip(in);
	in >> d.dag;
	return in;
}

int main(int argc, char *argv[])
{
	Datum test[5];
	test[0] = Datum(12, 10, 1992);
	test[1] = Datum(12, 1, 2021);
	test[2] = Datum(12, 9, 1992);
	test[3] = Datum(12, 12, 1992);
	test[4] = Datum(12, 4, 2002);

	ofstream weg("data.txt");

	weg << test[0] << endl;

	weg.close();

	Datum test2[5];

	ifstream terug("data.txt");
	terug >> test2[0];

	cout << test2[0].toString() << endl;

	terug.close();
	return 0;
}
