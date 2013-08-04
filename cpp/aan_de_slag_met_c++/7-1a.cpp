#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MAXSTRINGSIZE = 100;

void vervang(string &s, char bron, char doel)
{
	string::iterator pos;
	
	for (pos = s.begin(); pos != s.end(); ++pos)
		if (*pos == bron)
			*pos = doel;
}

void vervang2(string &s, char bron, char doel)
{
	s.replace(s.find(bron), 1, string(1, doel).c_str());
}

string voegsamen(vector<string> &v)
{
	vector<string>::iterator pos, end;
	string total;

	end = v.end();

	for (pos = v.begin(); pos != end; ++pos)
		total += *pos;

	return total;
}

void verdubbel(vector<int> &v)
{
	for (int &t : v)
		t *= 2;
}

int som(vector<int> &v)
{
	int count = 0; 

	for (int &t : v)
		count += t;

	return count;
}

/* Schrijf een functie die bepaalde exemplaren van een letter in een string 
vervangt met een andere letter */
int main(int argc, char *argv[])
{
	/* som test */
	vector<int> ir = { 10, 20 };
	cout << som(ir) << endl;

	/* verdubbel test */
	vector<int> i = { 10, 20 };
	verdubbel(i);
	cout << i[0] << i[1] << endl;

	/* vector test */
	vector<string> t = { string("appelflap"), string("kaas") };
	cout << voegsamen(t) << endl;

	char broncharacter, doelcharacter;
	string s;

	cout << "Geef een broncharacter op" << endl;
	cin >> broncharacter;
	cout << "Geef een doelcharacter op" << endl;
	cin >> doelcharacter;

	cout << "Geef string op" << endl;
	cin.ignore(1000, '\n');
	getline(cin, s);

	vervang(s, broncharacter, doelcharacter);
	cout << "Uitkomst: " << s << endl;

	return 0;
}
