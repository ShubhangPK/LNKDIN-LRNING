#include <ncurses.h>

int main()
{
	int ch;

	/* start Ncurses */
	initscr();

	/* Read special keys */
	keypad( stdscr, TRUE );
		/* display full duplex */
	noecho();
	while( (ch=getch()) != '~' )
	{
		switch(ch)
		{
			case KEY_DOWN:
				addstr("DOWN");
				break;
			case KEY_LEFT:
				addstr("LEFT");
				break;
			case KEY_RIGHT:
				addstr("RIGHT");
				break;
			case KEY_UP:
				addstr("UP");
				break;
			default:
				addch(ch);
		}
	}

	/* cleanup */
	endwin();
	return(0);
}
