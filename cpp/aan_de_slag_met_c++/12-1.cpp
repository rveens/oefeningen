#include <iostream>
#include <sstream>

using namespace std;

class Container {
	protected:
		unsigned maxAantal;
		int aantal;
		int *p;
	public:
		Container(int max);
		~Container();
		Container(const Container &c);
		Container &operator=(const Container &c);
		void voegtoe(int a);
		int tel(int a) const;
		string toString() const;
};

Container::Container(int max)
	: maxAantal(max), aantal(0), p(new int[maxAantal]) {
}

Container::~Container() {
	delete[] p;
}

Container::Container(const Container &c) :
	maxAantal(c.maxAantal), aantal(c.aantal), p(new int[maxAantal])
{
	unsigned int i;

	for (i = 0; i < aantal; ++i)
		p[i] = c.p[i];
}

Container &Container::operator=(const Container &c)
{
	unsigned int i = 0;

	delete[] p;
	aantal = c.aantal;
	p = new int[maxAantal];
	for (i = 0; i < c.aantal; i++)
		p[i] = c.p[i];

	return *this;
}

void Container::voegtoe(int a) {
	int i, temp;

	if (aantal < maxAantal) {
		p[i = aantal++] = a;
		while (i > 0 && i < aantal)
			if (p[i-1] > p[i]) {
				temp = p[i-1];
				p[i-1] = p[i];
				p[i] = temp;
				--i;
			} else
				break;
	}
}

int Container::tel(int a) const
{
	int total = 0;

	for (int i = 0; i < aantal; ++i)
		if (p[i] == a)
			total++;

	return total;
}

string Container::toString() const
{
	ostringstream os;

	for (int i = 0; i < aantal; ++i)
		os << p[i] << " ";

	return os.str();
}


class Histogram : public Container {
	public:
		Histogram(int max);
		void print() const;
};

Histogram::Histogram(int max) :
	Container(max) {
}

void Histogram::print() const
{
	for (int i = 0; i < aantal; ++i) {
		cout << p[i] << " ";
		for (int j = 0; j < tel(p[i]); ++j)
			cout << 'x';
		cout << endl;
	}
}

class DoubleArray {
	private:
		unsigned aantal;
		double *p;
	public:
		DoubleArray(unsigned n = 1);
		DoubleArray(const DoubleArray &x);
		DoubleArray &operator=(const DoubleArray &x);
		double &operator[](int k);
		~DoubleArray();
};

DoubleArray::DoubleArray(unsigned n)
	: aantal(n), p(new double[n]) {
}

DoubleArray::DoubleArray(const DoubleArray &x) : aantal(x.aantal), p(new double[aantal])
{
	for (int i = 0; i < x.aantal; ++i)
		p[i] = x.p[i];
}

DoubleArray &DoubleArray::operator=(const DoubleArray &x)
{
	delete[] p;

	p = new double[x.aantal];
	for (int i = 0; i < x.aantal; ++i)
		p[i] = x.p[i];

	return *this;
}

double &DoubleArray::operator[](int k)
{
	if (k < 0 || k > aantal -1) {
		cout << "Array out of bounds" << endl;
		exit(1);
	} else
		return p[k];
}

DoubleArray::~DoubleArray()
{
	delete[] p;
}

int main(int argc, char *argv[])
{
	DoubleArray da = DoubleArray(20);
	da[0] = 20;
	cout << da[19] << endl;
}
