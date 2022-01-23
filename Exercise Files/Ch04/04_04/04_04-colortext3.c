#include <ncurses.h>

int main()
{
	int cp,foreground, background;

	initscr();
	start_color();

	/* cycle through the basic 64 color combinations */
		/* cp variable sets 64 different color pairs */
	cp = 1;
		/* color constants are mapped to color numbers
		   0 through 7 */
	for( foreground=0; foreground<8; foreground++ )
	{
		for( background=0; background<8; background++ )
		{
			/* set the color pair pattern */
			init_pair( cp, foreground, background );
			/* activate the color pair attribute */
			attrset( COLOR_PAIR(cp) );
			printw("Pair %d %d ",foreground,background);
			/* increment cp to set a new color pair value */
			cp++;
		}
		addch('\n');
	}
	refresh();
	getch();

	endwin();

	return(0);
}

