#include <iostream>

using namespace std;

int main3()
{
	int n_wives = 7, n_sacks = 7, n_cats = 7, n_kits = 7;

	cout << "As I was going to St. Ives," << endl;
	cout << "I met a man with seven wives." << endl;
	cout << "Each wife had seven sacks," << endl;
	cout << "Each sack had seven cats," << endl;
	cout << "Each cat had seven kits." << endl;
	cout << "Kits, cats, sacks, and wives," << endl;
	cout << "How many were going to St.Ives ?" << endl;

	cout << endl;

	cout << "The answer is: " << n_wives * n_sacks* n_cats * n_kits + 2 << endl;

	return 0;
}