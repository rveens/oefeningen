#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

class IsEven {
	private:
		vector<int> *vEven, *vOneven;
	public:
		IsEven() : vEven(new vector<int>()), vOneven(new vector<int>()) {
		}

		bool operator()(int &x)
		{
			if (x % 2 == 0) {
				vEven->push_back(x);
				return true;
			} else {
				vOneven->push_back(x);
				return false;
			}
		}

		vector<int> &getvEven(){
			return *vEven;
		}

		vector<int> &getvOneven(){
			return *vOneven;
		}
};

int main(int argc, char *argv[])
{
	/* vector met rij maken */ 
	int rij[] = { 3, 7, 11, 13, 15, 23, 24, 35, 40, 63, 121, 132, 144 };
	vector<int> *v = new vector<int>(rij, rij + (sizeof rij / sizeof rij[0]));

	vector<int>::iterator 	pos = v->begin(),
				end = v->end();

	IsEven a;

	while (pos != end)
		pos = find_if(++pos, end, a);

	cout << "vector v" << endl;
	copy(v->begin(), v->end(), ostream_iterator<int>(cout, ", "));
	cout << endl << "even" << endl;
	copy(a.getvEven().begin(), a.getvEven().end(), ostream_iterator<int>(cout, ", "));
	cout << endl << "oneven" << endl;
	copy(a.getvOneven().begin(), a.getvOneven().end(), ostream_iterator<int>(cout, ", "));

	return 0;
}
