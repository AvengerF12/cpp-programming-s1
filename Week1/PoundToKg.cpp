// Conversion program

#include <iostream>
using namespace std;

#include <iomanip>

int main()
{
	double pounds, kgs;

	cout << "Give me the value in pounds..." << endl;
	cin >> pounds;
	cout << endl;

	kgs = pounds / 2.2;

	cout << pounds << " lbs. is (approx.) ";
	cout << setprecision(3);
	cout << kgs << " kgs.";
	cout << endl;
	cout << endl;

	return 0;
}