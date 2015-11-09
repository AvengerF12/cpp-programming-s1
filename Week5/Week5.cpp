#include <iostream>

using namespace std;

int main()
{
	int totalNights = 0;
	int totalRooms = 0;
	float totalCost = 0;
	string answerRoom = "";
	string answerGroupon = "";
	bool isChecking = true;
	
	cout << "Room		Price		Code" << endl;
	cout << "---------------------------------------------------------------" << endl;
	cout << "Deluxe Room	£200		D" << endl;
	cout << "Twin Room	£150		T" << endl;
	cout << "Single		£110		S" << endl;

	while(true){
		cout << "Do you need a room? (Insert the code of the chosen one)";
		cin >> answerRoom;
		cout << endl;

		if(answerRoom == "D"){
			totalCost += 200;
		} else if(answerRoom == "T"){
			totalCost += 150;
		} else if(answerRoom == "S"){
			totalCost += 110;
		}
		
		cout << "How many nights do you plan to stay?";
                cin >> totalNights;
                cout << endl;
	
		totalCost *= totalNights;

		cout << "Do you need more rooms? (Insert \'F\' for no, \'exit\' to terminate the program or type \'Y\' to input another room) ";
		cin >> answerRoom;


		if(answerRoom == "F"){
			break;

		} else if(answerRoom == "exit"){
			isChecking = false;

			totalCost *= totalNights;

			break;
		}
	}

	if(isChecking == true){

		cout << "Do you have a groupon discount?(If yes input the code, if no type \'N\')";
		cin >> answerGroupon;
		cout << endl;

                if(answerGroupon != "N"){
                        totalCost -= totalCost*15/100;
                }
		
		cout << "The total cost is " << totalCost << endl;
		cout << "Thank you for choosing us." << endl;

	}
	
	return 0;

}
