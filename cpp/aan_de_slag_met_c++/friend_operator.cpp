#include <iostream>
#include <sstream>

using namespace std;

class Voorraad {
	private:
		int klein, groot;
	public:
		Voorraad(int k = 0, int g = 0) : klein(k), groot(g) {
		}

		// operator*() als lid:
		Voorraad operator*(int d) const {
			return Voorraad(klein *d, groot *d);
		}

		// operator*() als friend:
		friend Voorraad operator*(int d, const Voorraad &v) {
			return Voorraad(d *v.klein, d *v.groot);
		}

		string toString() const {
			ostringstream os;
			os << klein << " klein en " << groot << " groot." << endl;

			return os.str();
		}
};

int main() {
	Voorraad v(1, 2), resultaat1, resultaat2;
	resultaat1 = 3 * v;
	resultaat2 = v * 5;
	cout << "De resultaten zijn:" << endl
		<< resultaat1.toString()
		<< resultaat2.toString();
}
