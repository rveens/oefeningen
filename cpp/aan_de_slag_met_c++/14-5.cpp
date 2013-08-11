#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

template<typename InputIterator, typename OutputIterator>
void kopieer(InputIterator first, InputIterator last,
		OutputIterator result)
{
	while(first < last)
		*result++ = *first++;
}

int main(int argc, char *argv[])
{
	vector<int> v = { 3, 4, 5, 6, 7 };
	vector<int> k = vector<int>(10);

	kopieer(v.begin(), v.end(), k.begin());
	copy(k.begin(), k.end(), ostream_iterator<int>(cout, "\n"));

	return 0;
}
