#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <ncurses.h>



/*
1) Start timer/counter
2) Start loop
	2.1) Check input keyboard
		2.11) If the key pressed is F, feed the pet
		2.12) If the key pressed is Q, quit the program

	2.2) Add the amount of elapsed time to the counter
	2.3) If the elapsed time is greater than X, remove one life from the pet
	2.4) Reset the timer

3) Repeat the loop until Q is pressed
*/

int kbhit();

int main()
{
	char key = 0;
	int food = 5;
	
	while(true){
		if(!kbhit()){
			// get keyboard data, and filter it
                        key = toupper(getch());

                        // is player trying to exit, if so exit
                        if (key == 'Q' || key == 27)
                                break;

                        // is player moving left
                        if (key == 'F')
                                food ++;
		}

	}

	return 0;
}

int kbhit()
{
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getchar();
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
 
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
 
  return 0;
}
