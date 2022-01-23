#include <ncurses.h>

int main()
{
	initscr();

	/* apply bold text */
	addstr("This text is ");
		/* activate the bold attribute */
	attron(A_BOLD);
	addstr("bold");
		/* deactivate bold attribute */
	attroff(A_BOLD);
	addch('\n');

	/* apply reverse text */
	addstr("This text is ");
		/* activate reverse attribute */
	attron(A_REVERSE);
	addstr("reverse");
		/* deactive reverse attribute */
	attroff(A_REVERSE);
	addch('\n');

	/* apply underline text */
	addstr("This text is ");
		/* activate underline attribute */
	attron(A_UNDERLINE);
	addstr("underlined");
		/* restore normal text */
	attrset(A_NORMAL);
	addch('\n');

	refresh();
	getch();

	endwin();

	return(0);
}

