#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>

using namespace std;

int game_running = 1;
string name = "";

// Enum of the states and correlated arrays 
enum hungerStates {Dead, Starving, RatherHungry, SlightlyPeckish, WellFed};
string hungerNames[] = {"Dead", "Starving", "Rather Hungry", "Slightly Peckish", "Well-fed"};

enum sleepStates {Collapsed, FallingAsleep, Tired, Awake, WideAwake};
string sleepNames[] = {"Collapsed", "Falling asleep", "Tired", "Awake", "Wide awake"};

// Current states
hungerStates food = RatherHungry;
sleepStates sleep = Tired;

void displayStates() 
{
	cout << name << "'s food state is now: " << hungerNames[food] << endl;
	cout << name << "'s sleep state is now: " << sleepNames[sleep] << endl;
	cout << endl;
}

void feedPet()
{
	switch (food) {
		case WellFed:
			cout << "I've been fed enough already... Do I look fat?" << endl;
			break;
		case SlightlyPeckish:
			cout << "Finally, I was just waiting for the dessert to arrive." << endl;
			food = WellFed;
			break;
		case RatherHungry:
			cout << "Feed me more or else!" << endl;
			food = SlightlyPeckish;
			break;
		case Starving:
			cout << "Thanks God tou came to your senses!" << endl;
			food = RatherHungry;
			break;
	}

	cout << endl;

	displayStates();
}

void foodStarvePet()
{
	switch (food) {
	case WellFed:
		cout << "Oh... I'm not starving but I could eat something..." << endl;
		food = SlightlyPeckish;
		break;
	case SlightlyPeckish:
		cout << "Are you still there? My plate will not fill itself." << endl;
		food = RatherHungry;
		break;
	case RatherHungry:
		cout << "I'm serious, if you don't feed me now I'm going to die on you!" << endl;
		food = Starving;
		break;
	case Starving:
		food = Dead;
		cout << "R.I.P. " << name << endl;
		game_running = 0;
		break;
	}

	cout << endl;

	displayStates();
}

void napPet()
{
	switch (sleep) {
	case WideAwake:
		cout << "I've slept enough for now." << endl;
		break; 
	case Awake:
		cout << "I could use a little nap." << endl;
		sleep = WideAwake;
		break;
	case Tired:
		cout << "I'm quite tired... See you later." << endl;
		sleep = Awake;
		break;
	case FallingAsleep:
		cout << "I won't be able to stay conscious for long..." << endl;
		sleep = Tired;
		break;
	case Collapsed:
		cout << "Zzz" << endl;
		sleep = FallingAsleep;
		break;
	}

	displayStates();
}

void sleepStarvePet() 
{
	switch (sleep) {
	case WideAwake:
		cout << "I don't feel quite as energetic anymore." << endl;
		sleep = Awake;
		break;
	case Awake:
		cout << "Time for a nap, don't you think?" << endl;
		sleep = Tired;
		break;
	case Tired:
		cout << "I... need... sleep... now..." << endl;
		sleep = FallingAsleep;
		break;
	case FallingAsleep:
		cout << "Zzz... *Went unconscious*" << endl;
		sleep = Collapsed;
		break;
	case Collapsed:
		cout << "Zzz... *Still unconscious*" << endl;
		break;
	}

	displayStates();
}

int main()
{
	float sleepTime = 100;
	char key = '\0';
	float timer = 0;

	cout << "Hello, I am your virtual pet... What shall my name be?" << endl;
	cin >> name;
	cout <<	endl << "well, what are you waiting for? Feed me already!" << endl;
	cout << "(Press 'F' to feed " << name << ", 'S' to put " << name << " to sleep or 'Q' to quit the game)" << endl << endl;

	displayStates();

	// Get player input
	while (game_running) {
		if (_kbhit())
		{
			// Get keyboard data, and filter it
			key = toupper(_getch());

			// Is player trying to exit, if so exit
			if (key == 'Q' || key == 27)
				game_running = 0;

			// Is player trying to feed, if so feed
			if (key == 'F')
				feedPet();

			if (key == 'S')
				napPet();

		} // end if

		if (timer > 5) {
			sleepStarvePet();
			foodStarvePet();
			timer = 0;
		}

		timer += sleepTime / 1000;

		Sleep(sleepTime);
	}

	system("pause"); // Wait until user input before closing

	return 0;
}


/*
1) Start timer/counter

2) Start loop
	2.1) Check input keyboard

		2.1.1) If the key pressed is F, feed the pet 
			Check if the pet is well-fed
			If it's not then increment the food amount and display the pet's values
			If it is then just display the values

		2.1.2) If the key pressed is S, put the pet to sleep
			Check if the pet has slept enough
			If it hasn't then increment the sleep amount and display the pet's values
			If it has then just display the values

		2.1.3) If the key pressed is Q, quit the program

	2.2) Add the amount of elapsed time to the counter
	2.3) If the elapsed time is greater than X, go down one state from the current one
	2.4) Reset the timer

3) Repeat the loop until Q is pressed
*/