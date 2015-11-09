#include <iostream>

using namespace std;

int main3()
{
	for (int x = 0; x < 4; x++){
		for (int y = 0; y < 4; y++){
			cout << (x + 1) * (y + 1) << "  ";
		}

		cout << endl;
	}

	return 0;
}