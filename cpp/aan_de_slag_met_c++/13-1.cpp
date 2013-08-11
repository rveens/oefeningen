#include <iostream>

using namespace std;

template<typename T> class LijstIterator {
	private:
		T *wijzer;
	public:
		LijstIterator(T *init = nullptr) : wijzer(init) {
		};

		T &operator*() {
			return *wijzer;
		}

		LijstIterator &operator++() {
			wijzer++;

			return *this;
		}

		bool operator!=(LijstIterator li) {
			return wijzer != li.wijzer;
		}
};

template<typename T> class Lijst {
	protected:
		T *data;
		unsigned aantal;
	public:
		typedef LijstIterator<T> iterator; // iterator

		Lijst<T>(unsigned max = 10); // default constructor
		Lijst<T>(const Lijst<T> &l); // copy constructor
		Lijst<T> &operator=(const Lijst<T> &l); // assignment operator
		T operator[](const int pos) const; // index operator
		T &operator[](const int pos); // index operator
		iterator begin();
		iterator end();
		~Lijst<T>(); // destructor
};

// constructor
template<typename T> Lijst<T>::Lijst(unsigned max) :
	data(new T[max]), aantal(max) {
}

// copy constructor
template<typename T> Lijst<T>::Lijst(const Lijst<T> &l) :
	data(new T[l.aantal]), aantal(l.aantal) {
}

// assignment operator
template<typename T> Lijst<T> &Lijst<T>::operator=(const Lijst<T> &l)
{
	delete[] data;

	new T[aantal = l.aantal];
	for (unsigned i = 0; i < aantal; i++)
		data[i] = l.data[i];

	return *this;
}

// index operator
template<typename T> T Lijst<T>::operator[](const int pos) const
{
	if (pos < 0 || pos > aantal) {
		cout << "error: index out of range" << endl;
		exit(1);
	} else
		return data[pos];
}

// index operator
template<typename T> T &Lijst<T>::operator[](const int pos)
{
	if (pos < 0 || pos > aantal) {
		cout << "error: index out of range" << endl;
		exit(1);
	} else
		return data[pos];
}

template<typename T> Lijst<T>::~Lijst<T>()
{
	delete[] data;
}

template<typename T> LijstIterator<T> Lijst<T>::begin()
{
	return LijstIterator<T>(data);
}

template<typename T> LijstIterator<T> Lijst<T>::end()
{
	return LijstIterator<T>(data + aantal);
}

template<typename T> class LijstMetVerwijder : public Lijst<T> {
	public:
		void verwijder(const T &d);
};

template<typename T> void LijstMetVerwijder<T>::verwijder(const T &d)
{
	for (unsigned i = 0; i < this->aantal; i++)
		if (this->data[i] == d)
			this->data[i] = T();
}

int main(int argc, char *argv[])
{
	Lijst<int> t(10), k = t;
	LijstMetVerwijder<unsigned int> z;
	LijstMetVerwijder<unsigned int>::iterator 	start = z.begin(),
							end;

	z[0] = 56;
	z[1] = 200;
	z[2] = 20;

	z.verwijder(20);

	for (end = z.end(); start != end; ++start)
		cout << *start << endl;

	return 0;
}
