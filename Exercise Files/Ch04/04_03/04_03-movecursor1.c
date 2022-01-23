#include <ncurses.h>

int main()
{
	int width,height,midy,midx;

	/* start Ncurses and create the standard screen */
	initscr();
	/* obtain the standard screen's dimensions */
	getmaxyx( stdscr, height, width);
	/* obtain screen center */
	midy = height >> 1;
	midx = width >> 1;
	/* move the cursor */
	move( midy, midx);
	/* set an asterisk at approximate center */
	addch('*');
	/* update the standard screen */
	refresh();
	/* wait for a key press */
	getch();

	/* cleanup */
	endwin();

	return(0);
}

