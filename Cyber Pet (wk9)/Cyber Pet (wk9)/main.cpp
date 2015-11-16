#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>

using namespace std;

// Defines
#define MAX_X        80  // maximum x position for player
#define SCROLL_POS   25  // the point that scrolling occurs

// Global variables
CONSOLE_SCREEN_BUFFER_INFO con_info;   // holds screen info
HANDLE hconsole;         // handle to console

int game_running = 1; // Determines if the games is still running or not
string name = ""; // Name of the pet
float timerFood = 0; // Time to wait before decreasing the food amount
float timerSleep = 0; // Time to wait before decreasing the sleep amount
bool sleeping = false;

// Enum of the states and correlated arrays
enum hungerStates {Dead, Starving, RatherHungry, SlightlyPeckish, WellFed};
string hungerNames[] = {"Dead", "Starving", "Rather Hungry", "Slightly Peckish", "Well-fed"};

enum sleepStates {Collapsed, FallingAsleep, Tired, Awake, WideAwake};
string sleepNames[] = {"Collapsed", "Falling asleep", "Tired", "Awake", "Wide awake"};

enum happyStates { Depressed, Malinconic, NotAmused, Happy, ExtremelyHappy };
string happyNames[] = { "Depressed", "Malinconic", "Not amused", "Happy", "Extremely happy" };

// Current states
hungerStates food = RatherHungry;
sleepStates sleepiness = Tired;
happyStates happiness = NotAmused;

void Init_Graphics()
{
	// this function initializes the console graphics engine

	COORD console_size = { 80, 25 }; // size of console

	// open i/o channel to console screen
	hconsole = CreateFile(TEXT("CONOUT$"), GENERIC_WRITE | GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		0L, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0L);

	// make sure we are in 80x25
	SetConsoleScreenBufferSize(hconsole, console_size);

	// get details for console screen                       
	GetConsoleScreenBufferInfo(hconsole, &con_info);

} // end Init_Graphics

void Draw_String(int x, int y, string string)
{
	// this function draws a string at the given x,y

	COORD cursor_pos; // used to pass coords

	// set printing position
	cursor_pos.X = x;
	cursor_pos.Y = y;
	SetConsoleCursorPosition(hconsole, cursor_pos);

	// print the string
	cout << string;

} // end Draw_String

void Clear_Screen()
{
	// this function clears the screen

	// clear the screen
	for (int index = 0; index <= 25; index++)
		Draw_String(0, SCROLL_POS, "\n");

} // end Clear_Screen

void displayStates() // Display the current states of the pet
{
	cout << name << "'s food state is now: " << hungerNames[food] << endl;
	cout << name << "'s sleep state is now: " << sleepNames[sleepiness] << endl;
	cout << name << "'s happiness state is now: " << happyNames[happiness] << endl;
	cout << endl;
} 

void updateUI()
{
	Clear_Screen();
	Draw_String(0, 0, "(Press 'F' to feed " + name + ", 'S' to put " + name + " to sleep, 'P' to play with " + name + " or 'Q' to quit the game)\n\n");
	Draw_String(0, 3, "");
	displayStates();
}

void increasePetFood() // Increase the pet's level of food
{
	switch (food) { // Check the state in which the pet hunger is currently in and increase it
		case WellFed:
			break;
		case SlightlyPeckish:
			food = WellFed;
			break;
		case RatherHungry:
			food = SlightlyPeckish;
			break;
		case Starving:
			food = RatherHungry;
			break;
	}

	displayStates();

	cout << endl;

}

void decreasePetFood() // Decrease the current food level/state
{
	switch (food) {
	case WellFed:
		food = SlightlyPeckish;
		break;
	case SlightlyPeckish:
		food = RatherHungry;
		break;
	case RatherHungry:
		food = Starving;
		break;
	case Starving:
		food = Dead;
		game_running = 0;
		break;
	}

	cout << endl;

}

void increasePetSleep() // Increase the pet's sleep state
{
	switch (sleepiness) { // Check the state in which the pet sleepness is currently in and increase it
	case WideAwake:
		break;
	case Awake:
		sleepiness = WideAwake;
		break;
	case Tired:
		sleepiness = Awake;
		break;
	case FallingAsleep:
		sleepiness = Tired;
		break;
	case Collapsed:
		sleepiness = FallingAsleep;
		break;
	}

	displayStates();

}

void decreasePetSleep() // Decrease the current sleep level/state
{
	switch (sleepiness) {
	case WideAwake:
		sleepiness = Awake;
		break;
	case Awake:
		sleepiness = Tired;
		break;
	case Tired:
		sleepiness = FallingAsleep;
		break;
	case FallingAsleep:
		sleepiness = Collapsed;
		break;
	case Collapsed:
		break;
	}

}

void increasePetHappiness() // Increase the current happiness level/state
{
	switch (happiness) {
	case ExtremelyHappy:
		break;
	case Happy:
		happiness = ExtremelyHappy;
		break;
	case NotAmused:
		happiness = Happy;
		break;
	case Malinconic:
		happiness = NotAmused;
		break;
	case Depressed:
		happiness = Malinconic;
		break;
	}

	displayStates();

}

void decreasePetHappiness() // Decrease the current happiness level/state
{
	switch (sleepiness) {
	case ExtremelyHappy:
		happiness = Happy;
		break;
	case Happy:
		happiness = NotAmused;
		break;
	case NotAmused:
		happiness = Malinconic;
		break;
	case Malinconic:
		happiness = Depressed;
		break;
	case Depressed:
		break;
	}

}

void balancePetHappiness() // Combine the pet's food and sleep states in order to determine its current level of happiness
{
	int expression = (sleepiness + food) / 2 - 1;
	if (happiness < expression) {
		switch (expression) {
		case Happy:
			happiness = NotAmused;
			break;
		case NotAmused:
			happiness = Malinconic;
			break;
		case Malinconic:
			happiness = Depressed;
			break;
		case Depressed:
			break;
		}
	}
}

int main()
{
	// Local variable initialization
	float sleepTime = 100;
	char key = '\0';

	// set up the console text graphics system
//	Init_Graphics();

	// Check for a name
	cout << "Hello, I am your virtual pet... What shall my name be?" << endl;
	cout << "(Insert multiple characters for the name or a single one to skip name selection)" << endl;
	cin >> name;
	if (name.length() == 1){
		name = "your pet";
	}

	cout <<	endl << "Well, what are you waiting for? Feed me already!" << endl;
	cout << "(Press 'F' to feed " << name << ", 'S' to put " << name << " to sleep, 'P' to play with " << name << " or 'Q' to quit the game)" << endl << endl;

	// Clear screen from everything
//	Clear_Screen();

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
				increasePetFood();
			
			// Is player trying to nap, if so nap
			if (key == 'S')
				increasePetSleep();

			// Is player trying to play with the pet, if so play with it
			if (key == 'P')
				increasePetHappiness();
		}

		// Check if the timer exceeded the intended limit, if so starve the pet and reset the timer
		if (timerFood > 10) { 
			decreasePetFood();
			decreasePetHappiness();
			balancePetHappiness();
			displayStates();

			timerFood = 0;
		}

		// Check if the timer exceeded the intended limit, if so starve the pet and reset the timer
		if (timerSleep > 15) {
			decreasePetSleep();
			decreasePetHappiness();
			balancePetHappiness();
			displayStates();

			timerSleep = 0;
		}

		timerFood += sleepTime / 1000; // Increases the timer after which the pet will lose some 'food'
		timerSleep += sleepTime / 1000; // Increases the timer after which the pet will lose some 'sleep'

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