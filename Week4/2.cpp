#include <iostream>

using namespace std;

int main2()
{
	int nStudents = 0;
	int currentEntry = 0;
	float totalCash = 0.0;

	while (true){
		cout << "Insert age if you are a new customer. Type -1 if you want to display the total cost." << endl;
		cin >> currentEntry;

		if (currentEntry == -1){
			
			if (nStudents >= 6){
				totalCash = totalCash - (totalCash * 20) / 100;
			}

			cout << "Here's the total amount of money that your group of " << nStudents << " owes us: " << totalCash << "." << endl;
			break;
		}
		
		nStudents++;

		if (currentEntry < 16){
			totalCash += 2.50;
		}

		else if (currentEntry > 65){
			totalCash += 3.00;
		}

		else if (currentEntry >= 16 && currentEntry <= 65){
			totalCash += 5.00;
		}
	}

	return 0;

}