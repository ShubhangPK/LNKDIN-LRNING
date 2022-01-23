#include <ncurses.h>

int main()
{
	char name[32];

	/* start Ncruses */
	initscr();

	/* prompt the user for their name */
	addstr("Type your name: ");
	refresh();
	getnstr(name,32);

	/* confirm input */
	printw("Hello, %s",name);
	refresh();
	getch();

	/* clean up */
	endwin();
	return(0);
}
