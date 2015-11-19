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
float hungerDecreaseTimer = 10; // Time to wait before decreasing the food counter 
float sleepDecreaseTimer = 15; // Time to wait before decreasing the sleep counter
bool isSleeping = false; // Determines if the pet is asleep or not
float awakeInTimer = 7; // Determines how much the pet will sleep

// Enum of the states and correlated arrays containing the string version of the states
enum hungerStates { Dead, Starving, RatherHungry, SlightlyPeckish, WellFed };
string hungerStrings[] = { "Dead", "Starving", "Rather Hungry", "Slightly Peckish", "Well-fed" };

enum sleepStates { Collapsed, FallingAsleep, Tired, Awake, WideAwake };
string sleepinessStrings[] = { "Collapsed", "Falling asleep", "Tired", "Awake", "Wide awake" };

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
	// Also needed to avoid the mess that Clear_Screen makes of the UI

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
	Draw_String(0, 19, name + "'s food level: " + hungerStrings[food] + "            ");
	Draw_String(0, 21, name + "'s sleep level: " + sleepinessStrings[sleepiness] + "         ");
	Draw_String(0, 23, name + "'s happy level: " + happinessStrings[happiness] + "           ");

	// Display if the pet is actually sleeping or not
	string sleepingValue;

	// Spaces needed to avoid overprinting issues
	if (isSleeping == true) {
		sleepingValue = "Asleep  ";
	}
	else {
		sleepingValue = "Wakeful  ";
	}
	Draw_String(40, 21, "State: " + sleepingValue);

	// Update the timers on the bottom-right corner of the screen (with integers to avoid wasting space)
	Draw_String(60, 19, "Awake in: " + to_string(int(awakeInTimer)) + " ");
	Draw_String(60, 21, "-Food in: " + to_string(int(hungerDecreaseTimer)) + " ");
	Draw_String(60, 23, "-Sleep in: " + to_string(int(sleepDecreaseTimer)) + " ");
}

void addPetCommunication(string message)
{
	// Adds a message to an array and organize the output as a scrollable list of strings
	// Move down each string by one position every time a new one is added
	for (int i = COMM_SIZE - 1; i > 0; i--) {

		petCommunications[i] = petCommunications[i - 1];
	}

	petCommunications[0] = message + "               ";
}

// Game related functions
void increasePetFood() // Increase the pet's level of food
{
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
	case Dead:
		// You cannot eat when you are dead... silly...
		break;
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
		addPetCommunication("If you don't feed I am going to die... Please...");
		food = Starving;
		break;
	case Starving:
		food = Dead;
		game_running = 0;
		break;
	case Dead:
		// Dead... yep... no need for this case
		break;
	}

}

void increasePetSleep() // Increase the current sleep level/state
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
		addPetCommunication("*Collapsed* 'Your pet has fallen asleep.'");
		isSleeping = true;
		break;
	case Collapsed:
		// Ugly way to handle one of the few exceptions... after collapsing the pet must go back up to FallingAsleep
		sleepiness = FallingAsleep;
		break;

	}

}

void increasePetHappiness() // Increase the current happiness level/state
{
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
		addPetCommunication("Why should I even bother to play? Life is meaningless either way...");
		happiness = Depressed;
		break;
	case Depressed:
		break;
	}

}

void balancePetHappiness() // Combine the pet's food and sleep states in order to determine its current level of happiness
{
	// The result of the expression is a reasonable value that represents the relationship between food and sleep
	// To be fully happy the player has to play with the pet
	int expression = (sleepiness + food) / 2 - 1;

	// Assign the value of the expression to the happiness variable
	switch (expression) {
	case ExtremelyHappy:
		happiness = ExtremelyHappy;
		break;
	case Happy:
		happiness = Happy;
		break;
	case NotAmused:
		happiness = NotAmused;
		break;
	case Malinconic:
		happiness = Malinconic;
		break;
	case Depressed:
		happiness = Depressed;
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
	cout << "(Insert your pet's name or leave blank for the default option)" << endl;
	getline(cin,name);

	// Don't allow names longer than 8 characters... they break the interface
	while (name.length() > 8) {
		cout << "The name that you chose is too long, please choose a shorter one. (Max 8 char)" << endl;
		getline(cin, name);
	}

	if (name == "") {
		name = "your pet";
	}

	// Print the different actions that the player can trigger
	cout << endl << "Well, what are you waiting for? Feed me already!" << endl;
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

			// Is player trying to feed, if so feed and reset food timer
			if (key == 'F') {

				if (isSleeping == true) {
					// You can't feed the pet while it's sleeping
					addPetCommunication("Are you serious? I'm sleeping and you're trying to feed me!");
				}
				else {
					increasePetFood();
					hungerDecreaseTimer = 10;
				}

			}

			// Is player trying to nap, if so nap and reset sleep timer
			if (key == 'S') {
				if (isSleeping == true) {
					addPetCommunication("I'm already sleeping, duh.");
				}
				// Avoid being able to reset sleep timer when WideAwake
				else if (sleepiness != WideAwake) {
					sleepDecreaseTimer = 15;
					isSleeping = true;
				}

			}

			// Is player trying to play with the pet, if so play with it
			if (key == 'P') {
				if (isSleeping == true) {
					addPetCommunication("I cannot play right now... I'm sleeping, duh.");
				}
				else {
					increasePetHappiness();
				}
			}
		}

		// After a certain amount of time the pet gets more hungry
		if (hungerDecreaseTimer <= 0) {
			decreasePetFood();
			balancePetHappiness();

			hungerDecreaseTimer = 10;
		}

		updateUI();

		/*The timers are not perfect since they are also affected by the Sleep() function.
		They lose 1 second for each counted one.
		To compensate for the loss the subtracted value is doubled.*/

		if (isSleeping == true) {
			// If the timer after which the pet wakes up is over the pet's sleep state increases and the 
			if (awakeInTimer <= 0) {
				increasePetSleep();
				isSleeping = false;

				awakeInTimer = 7;
			}
			// While the pet is sleeping the timer continues to tick until it reaches 0
			else {
				awakeInTimer -= pauseTime / 1000 * 2;
			}
		}

		if (isSleeping == false) {
			// After a certain amount of time the pet gets more sleepy
			if (sleepDecreaseTimer <= 0) {
				decreasePetSleep();
				balancePetHappiness();

				sleepDecreaseTimer = 15;
			}
			else {
				// While sleeping the sleep level should not decrease
				sleepDecreaseTimer -= pauseTime / 1000 * 2; // Decreases the timer after which the pet will lose some 'sleep'
			}
		}


		// Sleeping should not affect the hunger timer because it increases the difficulty and it makes sense
		hungerDecreaseTimer -= pauseTime / 1000 * 2; // Decreases the timer after which the pet will lose some 'food'

		Sleep(pauseTime); // The process is paused for 'sleepTime' milliseconds, needed to synchronize frames
	}

	Clear_Screen();

	// End game message
	Draw_String(35, 10, "Game Over");
	Draw_String(34, 12, name + " died.");
	Draw_String(0, 0, ""); // Reset output position

	system("pause"); // Wait until user input before closing

	return 0;
}

// Limitations: The UI can be destroyed by quickly pressing the sleep and feed button alternatively.
// The refresh of the UI is not really istantaneous, probably related to the Sleep function
// The timers are also not really precise, again a limitation of using this approach with Sleep()

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

// TODO: - Update pseudocode;