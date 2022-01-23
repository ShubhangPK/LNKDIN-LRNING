#include <ncurses.h>

int main()
{
	int width,height;

	/* start Ncurses and create the standard screen */
	initscr();
	/* obtain the standard screen's dimensions */
	getmaxyx( stdscr, height, width);
	printw("The standard screen is %d rows by %d columns.\n",
			height,
			width
		  );
	/* update the standard screen */
	refresh();
	/* wait for a key press */
	getch();

	/* cleanup */
	endwin();

	return(0);
}

