#include <iostream>
#include <limits>

using namespace std;

class Integer
{
	private:
		int value;
		void checkerror(double input);
	public:
		Integer(int i = 0) : value(i) {
		}
		operator int();
		/* / * - + */
		// met Integer
		Integer operator+(Integer i);
		Integer operator-(Integer i);
		Integer operator/(Integer i);
		Integer operator*(Integer i);
		// met int
		Integer operator+(int i);
		Integer operator-(int i);
		Integer operator/(int i);
		Integer operator*(int i);
};

void Integer::checkerror(double input)
{
	bool isError = false;
	double amount = 0;

	cout << "input waarde: " << (int)input << " limit max: " << numeric_limits<int>::max() << endl;
	cout << "input waarde: " << (int)input << " limit min: " << numeric_limits<int>::min() << endl;
	
	if (input > numeric_limits<int>::max()) {
		isError = true;
		amount = numeric_limits<int>::max() - input;
	} else if (input < numeric_limits<int>::min()) {
		isError = true;
		amount = numeric_limits<int>::min() - input;
	}
	
	if (isError) {
		cout << "error: int waarde out of range" << endl;
		cout << "out of range met waarde " << amount << endl;
		exit(1);
	}
}

Integer Integer::operator+(Integer i)
{
	checkerror(value += i);

	return Integer(value);
}

Integer Integer::operator-(Integer i)
{
	checkerror(value -= i);

	return Integer(value);
}

Integer Integer::operator/(Integer i)
{
	checkerror(value /= i);

	return Integer(value);
}

Integer Integer::operator*(Integer i)
{
	checkerror(value *= i);

	return Integer(value);
}

Integer Integer::operator+(int i)
{
	double t = value + i;
	checkerror(t);

	value = t;

	return value;
}

Integer Integer::operator-(int i)
{
	checkerror(value -= i);

	return Integer(value);
}

Integer Integer::operator/(int i)
{
	checkerror(value /= i);

	return Integer(value);
}

Integer Integer::operator*(int i)
{
	checkerror(value *= i);

	return Integer(value);
}

Integer::operator int()
{
	return value;
}

int main(int argc, char *argv[])
{
	Integer a(4), b(5), c(2147483600), d(-2147483600);

	cout << "waarde a(4)" << endl;
	cout << a << endl;
	cout << "waarde a(4) - 1" << endl;
	cout << a - 1 << endl;
	cout << "waarde a(4) + 1" << endl;
	cout << a + 1 << endl;
	cout << "waarde a(4) * 2" << endl;
	cout << a * 2 << endl;
	cout << "waarde a(4) / 2" << endl;
	cout << a / 2 << endl;

	a = 4;

	cout << "waarde a(4) b(5)" << endl;
	cout << a << ' ' << b << endl;
	cout << "waarde a(4) - b(5)" << endl;
	cout << a - b << endl;
	cout << "waarde a(4) + b(5)" << endl;
	cout << a + b << endl;
	cout << "waarde a(4) * b(5)" << endl;
	cout << a * b << endl;
	cout << "waarde a(4) / b(5)" << endl;
	cout << a / b << endl;

	cout << "out of range +" << endl;
	cout << "c + 100" << endl;
	cout << c + 100 << endl;

	cout << "out of range -" << endl;
	cout << "d - 100" << endl;
	cout << d - 100 << endl;

	return 0;
}
