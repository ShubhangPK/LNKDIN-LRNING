#include <ncurses.h>
#include <string.h>

int main()
{
	char center_text[] = "Powered by Ncurses";
	int width,height,y,x,len;

	/* start Ncurses and create the standard screen */
	initscr();
	/* obtain the standard screen's dimensions */
	getmaxyx( stdscr, height, width);
	/* calculate to center text on the screen */
	len = strlen(center_text);
	y = height >> 1;
	x = (width >> 1) - (len >> 1);
	/* move the cursor and add the string */
	mvaddstr( y, x, center_text );
	/* update the standard screen */
	refresh();
	/* wait for a key press */
	getch();

	/* cleanup */
	endwin();

	return(0);
}

