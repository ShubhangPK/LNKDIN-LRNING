#include <ncurses.h>

int main()
{
	initscr();
	start_color();

	/* Create a color pair */
		/* The color pair is referenced as pair 1.
		   It features red foreground text on a
		   blue background */
	init_pair( 1, COLOR_RED, COLOR_BLUE );
	/* Set color pair attribute */
	attrset( COLOR_PAIR(1) );
	addstr("This text is red on blue\n");
	/* turn off color */
	attrset( A_NORMAL );
	addstr("This text is normal");
	refresh();
	getch();

	endwin();

	return(0);
}

