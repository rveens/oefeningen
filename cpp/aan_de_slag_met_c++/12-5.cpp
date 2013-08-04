#include <iostream>

using namespace std;

class DNode {
	private:
		int x;
		DNode *next, *previous;
	public:
		DNode(int n = 0, DNode *pv = nullptr, DNode *ne = nullptr)
			:x(n), next(ne), previous(pv) {
		}

		int &getInt() {
			return x;
		}

		void setPrevious(DNode *previous) {
			this->previous = previous;
		}

		void setNext(DNode *next) {
			this->next = next;
		}

		DNode *&getPrevious() {
			return previous;
		}

		DNode *&getNext() {
			return next;
		}
};

class DLijstIterator {
	private:
		DNode *wijzer;
	public:
		DLijstIterator(DNode *init = nullptr) : wijzer(init) {
		}
		int &operator*() {
			return wijzer->getInt();
		}
		DLijstIterator &operator++()
		{
			wijzer = wijzer->getNext();
			return *this;
		}
		DLijstIterator &operator--()
		{
			wijzer = wijzer->getPrevious();
			return *this;
		}
		bool operator!=(DLijstIterator liter) {
			return wijzer != liter.wijzer;
		}
};

class DLijst {
	private:
		DNode *kop, *staart;
	public:
		typedef DLijstIterator iterator;
		DLijst() : kop(nullptr), staart(nullptr) {
		}
		~DLijst() {
			DNode *wijzer = kop, *pvolgende;
			while (wijzer != nullptr) {
				pvolgende = wijzer->getNext();
				delete wijzer;
				wijzer = pvolgende;
			}
		}
		void voegtoeeind(int x) {
			DNode *t = nullptr;
			
			if (staart == nullptr && kop == nullptr)
				kop = staart = new DNode(x); // staart en kop beide null
			else {
				t = new DNode(x, nullptr, staart);
				staart->setNext(t);
				staart = t;
			}
		}
		void voegtoebegin(int x) {
			DNode *t = nullptr;
			
			if (staart == nullptr && kop == nullptr)
				kop = staart = new DNode(x); // staart en kop beide null
			else {
				t = new DNode(x, kop, nullptr);
				kop->setPrevious(t);
				kop = t;
			}
		}
		iterator begin() {
			return iterator(kop);
		}
		iterator end() {
			return iterator(staart);
		}
};

int main(int argc, char *argv[])
{
	DLijst *dl = new DLijst();
	dl->voegtoeeind(30);
	dl->voegtoeeind(34);
	dl->voegtoeeind(36);

	DLijst::iterator 	pos,
				einde = dl->end();

	for (pos = dl->begin(); pos != einde; ++pos)
		cout << *pos << endl;

	return 0;
}
