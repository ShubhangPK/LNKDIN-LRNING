#include <ncurses.h>

int main()
{
	int row,column,x;

	/* start Ncurses and create the standard screen */
	initscr();

	/* loop and update the cursor's position */
	for( x=0; x<LINES-3; x++ )
	{
		getyx( stdscr, row, column );
		printw("The cursor was at position %d, %d\n",
				row,
				column
			  );
		move(row+1,column+1);
	}
	/* update the standard screen */
	refresh();
	getch();

	/* cleanup */
	endwin();

	return(0);
}

