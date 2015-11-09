#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

void averageHeight(int height1, int height2);

int main3()
{
	averageHeight(2, 4);

	return 0;
}

void averageHeight(int height1, int height2)
{
	if (height1 > 0 && height2 > 0){
		int aveheight = (height1 + height2) / 2;
			cout << "The average of heights " << height1 << " and " << height2 << " is " << aveheight << endl;
	}
}