#include <iostream>
#include <list>

using namespace std;

int main()
{
	list<int> nList(6, 0);
	int priceArray[] = {6};


	for (int i = 0; i < 6; i++){
		cout << "Insert the next price tag: " << endl;

		cin >> priceArray[i];
		
	}

	nList.assign(priceArray, priceArray + 6);

	nList.sort();

	list<string>::const_iterator i;
	for (i = nList.begin(); i != nList.end(); ++i)
		cout << *i << " ";
	cout << endl;

	return 0;
}