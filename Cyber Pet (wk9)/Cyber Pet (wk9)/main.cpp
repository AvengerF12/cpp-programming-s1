#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>

using namespace std;

// Defines (Macros)
#define MAX_X        80  // maximum x position for player
#define SCROLL_POS   24  // the point that scrolling occurs
#define COMM_SIZE	12	// the maximum size of the communications array

// Function prototypes
void Init_Graphics();
void Draw_String(int, int, string);
void Clear_Screen();
void updateUI();
void addPetCommunication();

// Global variables
CONSOLE_SCREEN_BUFFER_INFO con_info;   // holds screen info
HANDLE hconsole;         // handle to console

int game_running = 1; // Determines if the games is still running or not
string name = ""; // Name of the pet
float timerFood = 10; // Time to wait before decreasing the food amount
float timerSleep = 15; // Time to wait before decreasing the sleep amount
bool sleeping = false;

// Enum of the states and correlated arrays
enum hungerStates {Dead, Starving, RatherHungry, SlightlyPeckish, WellFed};
string hungerStrings[] = {"Dead", "Starving", "Rather Hungry", "Slightly Peckish", "Well-fed"};

enum sleepStates {Collapsed, FallingAsleep, Tired, Awake, WideAwake};
string sleepinessStrings[] = {"Collapsed", "Falling asleep", "Tired", "Awake", "Wide awake"};

enum happyStates { Depressed, Malinconic, NotAmused, Happy, ExtremelyHappy };
string happinessStrings[] = { "Depressed", "Malinconic", "Not amused", "Happy", "Extremely happy" };

// Array of strings that contains the messages from the pet to the player
string petCommunications[COMM_SIZE];

// Current states
hungerStates food = RatherHungry;
sleepStates sleepiness = Tired;
happyStates happiness = NotAmused;

// UI related functions
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

void updateUI()
{
	// This didn't get out of end... no, not at all...
	// Additional spaces needed because of the overprinting of words and numbers... hackish...

	// Keep instructions on screen all the time
	Draw_String(0, 0, "(Press 'F' to feed " + name + ", 'S' to put " + name + " to sleep, 'P' to play with " + name + " or 'Q' to quit the game)\n\n");

	// Visual separator for the UI elements
	for (int i = 0; i < MAX_X; i++) {
		Draw_String(i, 2, "_");
	}

	// Display communications header
	Draw_String(0, 3, name + "'s communications:");

	// Print last pet communications
	for (int i = 0; i < COMM_SIZE; i++) {
		Draw_String(0, i + 5, petCommunications[i]);
	}

	// Visual separator for the UI elements
	for (int i = 0; i < MAX_X; i++) {
		Draw_String(i, 17, "_");
	}

	// Update the pet's stats, using the correspondant strings from the arrays, on the bottom-left of the screen
	Draw_String(0, 19, name + "'s hunger: " + hungerStrings[food] + "            ");
	Draw_String(0, 21, name + "'s sleepiness: " + sleepinessStrings[sleepiness] + "            ");
	Draw_String(0, 23, name + "'s happiness: " + happinessStrings[happiness] + "              ");

	string sleepingValue;

	if (sleeping){
		sleepingValue = "True";
	}
	else {
		sleepingValue = "False";
	}
	Draw_String(40, 21, "Sleeping: " + sleepingValue);

	// Update the timers on the bottom-right corner of the screen (with integers to avoid wasting space)
	Draw_String(64, 21, "Food timer: " + to_string(int(timerFood)) + " ");
	Draw_String(64, 23, "Sleep timer: " + to_string(int(timerSleep)) + " ");
}

void addPetCommunication(string message)
{
	// Move down each string by one position every time a new one is added
	for (int i = COMM_SIZE - 1; i > 0; i--) {
		
		petCommunications[i] = petCommunications[i-1];
	}

	petCommunications[0] = message + "               ";
}

// Game related functions
void increasePetFood() // Increase the pet's level of food
{
	if (sleeping == true) { // You can't feed the pet while it's sleeping
		addPetCommunication("Are you serious? I'm alredy sleeping and now you're trying to feed me! I can't multitask like that! Do i look like a computer program to you?!");
	}
	else {
		switch (food) { // Check the state in which the pet hunger is currently in and increase it
		case WellFed:
			addPetCommunication("You've fed me enough... Do I look fat?");
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
	}

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

}

void increasePetSleep() // Increase the pet's sleep state
{
	switch (sleepiness) { // Check the state in which the pet sleepness is currently in and increase it
	case WideAwake:
		addPetCommunication("I've slept enough for now, let's do something else.");
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
	if (sleeping == true) { // You can't play while the pet is sleeping
		cout << "Can't you see that i am sleeping? We will play later... I mean Zzz" << endl;
	}
	else {
		switch (happiness) {
		case ExtremelyHappy:
			addPetCommunication("I'm already plenty happy, no need to waste energies");
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
	}
	
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
	// The result of the expression is a reasonable value that represents the relationship between food and sleep
	int expression = (sleepiness + food) / 2 - 1; 

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

int main()
{
	// Local variable initialization
	float pauseTime = 100; // Time for which the process will be paused
	char key = '\0'; // Contains last key pressed

	// set up the console text graphics system
	Init_Graphics();

	// Check for a name, if no name is assigned just reference the pet as "your pet"
	cout << "Hello, I am your virtual pet... What shall my name be?" << endl;
	cout << "(Insert multiple characters for the name or a single one to skip name selection)" << endl;
	cin >> name;

	if (name.length() == 1){
		name = "your pet";
	}

	// Print the different actions that the player can trigger
	cout <<	endl << "Well, what are you waiting for? Feed me already!" << endl;
	cout << "(Press 'F' to feed " << name << ", 'S' to put " << name << " to sleep, 'P' to play with " << name << " or 'Q' to quit the game)" << endl << endl;

	// Clear screen from everything
	Clear_Screen();

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

		// After a certain amount of time the pet gets more hungry
		if (timerFood <= 0) { 
			decreasePetFood();
			balancePetHappiness();

			timerFood = 10;
		}

		// After a certain amount of time the pet gets more sleepy
		if (timerSleep <= 0) {
			decreasePetSleep();
			balancePetHappiness();

			timerSleep = 15;
		}

		updateUI();

		/*The timers are not perfect since they are also affected by the Sleep() function.
		The timer loses 1 second for each one that it counts.
		To compensate for the time that Sleep() makes the timer lose the subtracted value is doubled.*/
		timerFood -= pauseTime / 1000 * 2; // Decreases the timer after which the pet will lose some 'food'
		timerSleep -= pauseTime / 1000 * 2; // Decreases the timer after which the pet will lose some 'sleep'

		Sleep(pauseTime); // The process is paused for 'sleepTime' milliseconds
	}

	Clear_Screen();

	Draw_String(35, 10, "Game Over");
	Draw_String(0, 0, ""); // Reset output position

	system("pause"); // Wait until user input before closing

	return 0;
}


/*
1) Start timer/counter

2) Start loop
	2.1) Check input keyboard

		2.1.1) If the key pressed is F, feed the pet 
			Check if the pet is sleeping
				If it is then:
					Leave the food state as it is
					Tell the player that the pet can't eat
				If it's not then proceed
			Check if the pet is well-fed
				If it's not then increment the food amount and display the pet's values
				If it is then just display the values

		2.1.2) If the key pressed is S, put the pet to sleep
			Check if the pet's sleepiness state is at maximum
				If it's not: 
					Increment the sleepiness state
					Display the pet's values
				If it is:
					Display the pet's values

		2.1.3) If the key pressed is P, play with the pet
			Check if the pet is sleeping
				If it is:
					Leave the happiness state as it is
					Tell the player that the pet can't play
				If it's not:
					Proceed
			Check if the pet's happiness is at maximum
				If it's not:
					Increment the happiness state
					Display the pet's values
				If it is:
					Display the values

		2.1.4) If the key pressed is Q, quit the program

	2.2) Add the amount of elapsed time to the counter
	2.3) If the elapsed time is greater than X, go down one state from the current one
	2.4) Reset the timer

3) Repeat the loop until Q is pressed
*/

// TODO: - Add sleeping check to food function