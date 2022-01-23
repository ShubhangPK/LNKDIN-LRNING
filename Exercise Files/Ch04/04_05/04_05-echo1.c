#include <ncurses.h>

int main()
{
	char buffer[64];

	/* start Ncurses */
	initscr();

	/* Echo is on by default */
	addstr("What is your favorite color? ");
	refresh();
	getnstr(buffer,64);
	printw("%s is my favorite color, too\n",buffer);

	/* echo off */
	noecho();	/* activate echo with the echo() function */
	addstr("Echo is off\n");
	addstr("What is your birth month? ");
	refresh();
	getnstr(buffer,64);
	printw("%s is my birth month, too\n",buffer);
	refresh();
	getch();

	/* cleanup */
	endwin();
	return(0);
}

