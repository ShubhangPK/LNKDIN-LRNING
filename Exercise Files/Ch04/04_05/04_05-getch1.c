#include <ncurses.h>

int main()
{
	int ch;

	/* start Ncurses */
	initscr();
	addstr("Type text; press ~ to Exit:\n");
	refresh();

	/* Loop until ~ pressed
	   no need to refresh for getch() */
	while( (ch = getch()) != '~' )
		;

	/* cleanup */
	endwin();
	return(0);
}
