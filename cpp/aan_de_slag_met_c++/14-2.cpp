#include <iostream>

using namespace std;

class Dubbel {
	public:
		void operator()(int &x) const
		{
			x *= 2;
		}
};

int main(int argc, char *argv[])
{
	int y = 4;

	Dubbel a;

	cout << y << endl;
	a(y);
	cout << y << endl;

	return 0;
}
