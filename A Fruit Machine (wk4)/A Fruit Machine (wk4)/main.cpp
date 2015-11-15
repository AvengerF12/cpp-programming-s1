
//  A game fragment adapted from Andre La Mothe's book

//	The Black Art of 3D Games Programming

//  Modified by CJM 24/9/'08 to run without error or warnings:

//	1.  hconsole - called TEXT( ) for parameter 1
//	2.  added _ as prefix to deprecated kbhit() function
//	3.  added _ as prefix to deprecated getch() function

//	Note: this is very old-fashioned code originally written for 16-bit PCs



// INCLUDES ///////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> 
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string>
#include <iostream>


// DEFINES ////////////////////////////////////////////////

#define MAX_X        77  // maximum x position for player
#define SCROLL_POS   24  // the point that scrolling occurs

// PROTOTYPES /////////////////////////////////////////////

void Init_Graphics(void);
inline void Set_Color(int fcolor, int bcolor);
inline void Draw_String(int x, int y, char *string);

// GLOBALS ////////////////////////////////////////////////

CONSOLE_SCREEN_BUFFER_INFO con_info;   // holds screen info

HANDLE hconsole;         // handle to console
int    game_running = 1; // state of game, 0=done, 1=run

						 // FUNCTIONS //////////////////////////////////////////////

void Init_Graphics(void)
{
	// this function initializes the console graphics engine

	COORD console_size = { 80, 25 }; // size of console

									 // seed the random number generator with time
	srand((unsigned)time(NULL));

	// open i/o channel to console screen
	hconsole = CreateFile(TEXT("CONOUT$"), GENERIC_WRITE | GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		0L, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0L);

	// make sure we are in 80x25
	SetConsoleScreenBufferSize(hconsole, console_size);

	// get details for console screen                       
	GetConsoleScreenBufferInfo(hconsole, &con_info);

} // end Init_Graphics

  ///////////////////////////////////////////////////////////

inline void Set_Color(int fcolor, int bcolor = 0)
{
	// this function sets the color of the console output
	SetConsoleTextAttribute(hconsole, (WORD)((bcolor << 4) |
		fcolor));

} // Set_Color

  ///////////////////////////////////////////////////////////

inline void Draw_String(int x, int y, char *string)
{
	// this function draws a string at the given x,y

	COORD cursor_pos; // used to pass coords

					  // set printing position
	cursor_pos.X = x;
	cursor_pos.Y = y;
	SetConsoleCursorPosition(hconsole, cursor_pos);

	// print the string in current color
	printf("%s", string);

} // end Draw_String

  ///////////////////////////////////////////////////////////

inline void Clear_Screen(void)
{
	// this function clears the screen

	// set color to white on black
	Set_Color(15, 0);

	// clear the screen
	for (int index = 0; index <= 25; index++)
		Draw_String(0, SCROLL_POS, "\n");

} // end Clear_Screen

  // MAIN GAME LOOP /////////////////////////////////////////
using namespace std;
int main()
{
	char key;            // player input data
	int player_x = 40;  // player's x 
	char symbol1 = 3;
	char symbol2 = 4;
	char symbol3 = 5;
	char symbol4 = 6;
	char symbol5 = 5;
	char symbol6 = 4;
	char symbol7 = 3;
	char symbol8 = 4;
	char symbol9 = 5;
	float timer = 0.0F;
	float sleepTime = 100.0F;
	string result = "\nGame Over\n\n";

						 // SECTION: initialization

						 // set up the console text graphics system
	Init_Graphics();

	// clear the screen
	Clear_Screen();

	// SECTION: main event loop, this is where all the action  
	// takes place, the general loop is erase-move-draw

	while (game_running)
	{

		// SECTION: get player input
		if (_kbhit())
		{
			// get keyboard data, and filter it
			key = toupper(_getch());

			// is player trying to exit, if so exit
			if (key == 'Q' || key == 27)
				game_running = 0;

		} // end if   

		// SECTION: draw everything

		// First rotor
		Set_Color(4, 0); // Set required colour palette
		Draw_String(20, 5, ""); // Move to the cursor to the desired position without printing
		cout << symbol3; // Output the number

		Set_Color(12, 0); // Set required colour palette
		Draw_String(20, 7, ""); // Move to the cursor to the desired position without printing
		cout << symbol2; // Output the number

		Set_Color(4, 0); // Set required colour palette
		Draw_String(20, 9, ""); // Move to the cursor to the desired position without printing
		cout << symbol1; // Output the number

		// Second rotor
		Set_Color(4, 0); // Set required colour palette
		Draw_String(22, 5, ""); // Move to the cursor to the desired position without printing
		cout << symbol6; // Output the number

		Set_Color(12, 0); // Set required colour palette
		Draw_String(22, 7, ""); // Move to the cursor to the desired position without printing
		cout << symbol5; // Output the number

		Set_Color(4, 0); // Set required colour palette
		Draw_String(22, 9, ""); // Move to the cursor to the desired position without printing
		cout << symbol4; // Output the number

		// Third rotor
		Set_Color(4, 0); // Set required colour palette
		Draw_String(24, 5, ""); // Move to the cursor to the desired position without printing
		cout << symbol9; // Output the number

		Set_Color(12, 0); // Set required colour palette
		Draw_String(24, 7, ""); // Move to the cursor to the desired position without printing
		cout << symbol8; // Output the number

		Set_Color(4, 0); // Set required colour palette
		Draw_String(24, 9, ""); // Move to the cursor to the desired position without printing
		cout << symbol7; // Output the number

		// Winning condition
		if (symbol2 == symbol5 && symbol5 == symbol8) {
			result = "\nYou Won\n\n";
			game_running = 0;
		}

		// Check that a second passed and increment numbers
		if (timer >= 1) { 
			timer = 0;
			symbol1++;
			symbol2++;
			symbol3++;
			symbol4++;
			symbol5++;
			symbol6++;
			symbol7++;
			symbol8++;
			symbol9++;
		}

		if (symbol1 > 6) { // Check that number didn't exceed its limit
			symbol1 = rand()%4 + 3;
		}

		if (symbol2 > 6) { // Check that number didn't exceed its limit
			symbol2 = rand()%4 + 3;
		}

		if (symbol3 > 6) { // Check that number didn't exceed its limit
			symbol3 = rand()%4 + 3;
		}

		if (symbol4 > 6) { // Check that number didn't exceed its limit
			symbol4 = rand()%4 + 3;
		}

		if (symbol5 > 6) { // Check that number didn't exceed its limit
			symbol5 = rand()%4 + 3;
		}

		if (symbol6 > 6) { // Check that number didn't exceed its limit
			symbol6 = rand()%4 + 3;
		}

		if (symbol7 > 6) { // Check that number didn't exceed its limit
			symbol7 = rand()%4 + 3;
		}

		if (symbol8 > 6) { // Check that number didn't exceed its limit
			symbol8 = rand()%4 + 3;
		}

		if (symbol9 > 6) { // Check that number didn't exceed its limit
			symbol9 = rand()%4 + 3;
		}


		timer += sleepTime / 1000; // Total amount of time since the last second passed

		// SECTION: synchronize to a constant frame rate
		Sleep(sleepTime);

	} // end while

	  // SECTION: shutdown and bail
//	Clear_Screen();

	Draw_String(10, 20, "");
	Set_Color(15, 0); // Set required colour palette
	cout << result;

	system("pause"); // Wait until user input before closing

	return 0;
} // end main