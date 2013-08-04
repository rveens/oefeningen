#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Voertuig
{
	private:
		int aantalWielen;
		string soort;
		bool speciaal;
	public:
		Voertuig()
		{
			aantalWielen = 4;
			soort = string("subaru");
		}

		Voertuig(int aantalWielen = 0, string soort = "")
		{

		}

		Voertuig(int aantalWielen = 0) : aantalWielen(aantalWielen), soort("subaru")
		{

		}

		Voertuig(int aantalWielen = 0, string soort = "subaru", bool speciaal = false)
			: aantalWielen(aantalWielen), soort(soort), speciaal(speciaal)
		{

		}

		string toString() const
		{
			ostringstream os;
			os << "aanal wielen: " << aantalWielen << endl;
			os << "soort: " << soort << endl;
			os << "speciaal: " << speciaal << endl;

			return os.str();
		}
};

int main(int argc, char *argv[])
{
	Voertuig 	persnauto(4, "personenauto", false);
	Voertuig 	vrachtwagen(3, "vrachtwagen", false);
	Voertuig
			limo(6, "limosine", true),
			taxi(4, "taxi", false),
			ijscowagen(4, "ijscowagen", true),
			stuntwagen(1, "stuntwagen", false),
			tank(8, "tank", true), 
			monstertruct(4, "monster truck", true);

	return 0;
}
