#include <iostream>
#include <fstream>

using namespace std;

/* #define LOGS */

int main(int argc, char *argv[])
{
	string filename = "alfabet.txt";

	ofstream alfabet(filename.c_str());
	for (int i = 0; i < 26; i++) {
#ifdef LOGS
		cout << static_cast<char>('A' + i) << endl;
#endif
		alfabet << static_cast<char>('A' + i);
	}
	alfabet.close();

	ifstream abc(filename.c_str());

	char ch;
	abc.seekg(3);
	abc >> ch;
	cout << ch;

	abc.seekg(2, ios::cur);
	abc >> ch;
	cout << ch;

	abc.seekg(-1, ios::end);
	abc >> ch;
	cout << ch;

	abc.close();

	return 0;
}
