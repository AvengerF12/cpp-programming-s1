#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

int main()
{	
	int i = 0; //number of rolls
	int answer = 0;
	int rand_roll = 0;
	int total_rolls = 0;
	int n_6 = 0; //number of sixes

	srand((unsigned)time(0));

	while (true){
		rand_roll = rand() % 6 + 1;

		if (rand_roll != 6){
			i++;
		}
		else {
			n_6 ++;

			cout << "The dice rolled " << i << " times before rolling 6." << endl;
			cout << "Insert a number greater than 0 to continue. Insert 0 to terminate." << endl;

			cin >> answer;

			total_rolls += i;
			i = 0;
			
			if (answer == 0){
				break;
			}

		}
	}


	
	cout << "The average is:" << (float) total_rolls/n_6 << endl;
}