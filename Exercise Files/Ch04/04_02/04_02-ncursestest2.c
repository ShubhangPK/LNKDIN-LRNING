#include <ncurses.h>

int main()
{
	/* start Ncurses and create the standard screen */
	initscr();
	/* output text to the standard screen */
	printw("This is Ncurses version %s\n",NCURSES_VERSION);
	/* update the standard screen */
	refresh();
	/* wait for a key press */
	getch();

	/* exit Ncurses and cleanup */
	endwin();

	return(0);
}
