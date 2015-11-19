#include <iostream>
#include <cstdio>
#define MAX_SIZE 10

using namespace std;

void readNumbers(int unsortedArray[])
{
	for (int i = 0; i < MAX_SIZE; i++) {
		cout << "Insert a number: ";
		cin >> unsortedArray[i];
		cout << endl;
	}
}

int main() 
{
	int inputArray[MAX_SIZE];
	int sortedArray[MAX_SIZE];
	int chosenPos = 0;

	readNumbers(inputArray);

	cout << "Elaborating..." << endl;

	// This section sorts the array
	for (int k = 0; k < MAX_SIZE; k++) {

		chosenPos = k; // The value in this position will be compared with all the values that have not been compared yet
		for (int i = 0 + k; i < MAX_SIZE; i++) {

			if (inputArray[chosenPos] > inputArray[i]) {
				chosenPos = i; // Only the smaller of the two will sorted
			}
		}

		// Execute only if the current smallest number isn't already in the leftomost not-sorted position
		if (k != chosenPos) {
			// Move the value in the leftmost not-sorted position to a temp variable
			int tmpVar = inputArray[k];
			// Move into that same position the current smallest value
			inputArray[k] = inputArray[chosenPos];
			// Move the value from the temp variable to the position previously occupied by the smallest number
			inputArray[chosenPos] = tmpVar;
		}

	}

	// Output the result
	for (int i = 0; i < MAX_SIZE; i++) {
		cout << " " << inputArray[i];
	}

	cout << endl;

	system("pause"); // Wait for user input before closing
	
	return 0;

}


/*
1 Find the smallest possible number
	1.1 Pick the first number in the array
	1.1 Loop through every position and confront the current number with the one you picked
		1.2.1 If the number is smaller than the chosen one
			Pick the new number as the chosen one
			Continue looping through the array
		1.2.2 If the number is bigger than the chosen one
			Continue looping through the array
	1.3 Repeat until you looped through the whole array
2 If the lefmost not-sorted position and the current smallest value's position are not the same, swap their content
	2.1 Store the value in the leftmost position in a temporary variable
	2.2 Store the current smallest value in the leftmost not-sorted position
	2.3 Store the temporary variable value inside the position where the smallest value was

3 Repeat step 1 and 2 until the value in every position of the array has been compared (a.k.a. loop the first step for the length of the array itself)
*/