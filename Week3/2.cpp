#include <iostream>

using namespace std;

int main2()
{
	for (int i = 99; i > 0; i--){
		cout << i << " bottles of beer on the wall, " << i << " bottles of beer." << endl;
		cout << "Take one down, pass it around, " << i << " bottles of beer on the wall." << endl;
	}

	cout << endl << "No more bottles of beer on the wall, no more bottles of beer. Go to the store and buy some more, 99 bottles of beer on the wall.";

	return 0;
}