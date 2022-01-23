#include <ncurses.h>

#define TAIL_LEN 10

struct coord {
	int y;
	int x;
	char c;
};

int main()
{
	int max_x, max_y,direction_x,direction_y,x;
	char ch;
	struct coord tail[TAIL_LEN];

	initscr();

	/* initialization */
	getmaxyx( stdscr, max_y, max_x);
	nodelay( stdscr, TRUE );
	noecho();
	ch = '*';
	direction_x = 1;
	direction_y = 1;
	for( x=0; x<TAIL_LEN; x++)
	{
		tail[x].y = 0;
		tail[x].x = 0;
		tail[x].c = ch;
	}

	/* main program loop */
	while(1)
	{
		/* is a key waiting? */
		ch = getch();
		if( ch == ERR )
			/* if not, set the existing character */
			ch = tail[TAIL_LEN-1].c;
		/* erase tail base */
		mvaddch( tail[0].y, tail[0].x, ' ');
		/* update tail base */
		tail[0].y = tail[1].y;
		tail[0].x = tail[1].x;
		/* update the rest of the tail */
		for( x=1; x<TAIL_LEN-1; x++)
		{
			/* draw the tail */
			mvaddch( tail[x].y, tail[x].x, tail[x].c );
			tail[x].y = tail[x+1].y;
			tail[x].x = tail[x+1].x;
			tail[x].c = tail[x+1].c;
		}
		/* set the last character, head of the snake */
		tail[TAIL_LEN-1].x = tail[TAIL_LEN-1].x + direction_x;
		tail[TAIL_LEN-1].y = tail[TAIL_LEN-1].y + direction_y;
		/* use the character just typed, if avialable */
		tail[TAIL_LEN-1].c = ch;
		/* draw the character */
		mvaddch( tail[TAIL_LEN-1].y, tail[TAIL_LEN-1].x, tail[TAIL_LEN-1].c );
		/* check the bounds */
		if( tail[TAIL_LEN-1].x == max_x-1 )
			direction_x = -1;
		if( tail[TAIL_LEN-1].x == 0 )
			direction_x = 1;
		if( tail[TAIL_LEN-1].y == max_y-1 )
			direction_y = -1;
		if( tail[TAIL_LEN-1].y == 0 )
			direction_y = 1;
		/* update the screen */
		refresh();
		/* pause */
		napms(100);

		/* check for exit condition */
		if( ch == ' ')
			break;
	}

	endwin();
	return(0);
}
