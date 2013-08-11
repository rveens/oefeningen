#include <iostream>
#include <algorithm>
#include <string>
#include <iterator>

using namespace std;

int main(int argc, char *argv[])
{
	string s = "Mango";

	copy(s.begin(), s.end(), ostream_iterator<char>(cout, "\n"));
}
