#include <iostream>
#include <string>

using namespace std;

int main4()
{
	string coursework = "";
	float mark = 0;
	int n_mark = 0;
	float total = 0;

	cout << "Insert your coursework code:" << endl;

	cin >> coursework;

	while (true)
	{
		cout << "Insert your grade: " << endl;

		cin >> mark;

		if (mark == -1)
			break;

		total += mark;
		n_mark++;
	}

	cout << "Your average grade in " + coursework + " is: " << (float) (total / n_mark) << "." << endl;

	return 0;
}