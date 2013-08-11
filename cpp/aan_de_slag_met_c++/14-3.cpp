#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>

using namespace std;

int main(int argc, char *argv[])
{
	ifstream in("14-3.cpp");

	in >> noskipws;

	copy(istream_iterator<char>(in),
	     istream_iterator<char>(),
	     ostream_iterator<char>(cout));

	return 0;
}
