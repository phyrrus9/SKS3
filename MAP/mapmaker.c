#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#define RED "\33[31m"
#define RESET "\33[0m"
#define ARROW_UP -1
#define ARROW_DOWN -2
#define ARROW_LEFT -3
#define ARROW_RIGHT -4

int getch_()
{
    /*
     * Get a single character using the ncurses functions
     * so that you no longer need to press enter (like in
     * the original version of sks4200). This function being
     * here just makes it a lot easier to grab a character
     * instead of pasting this code everywhere we needed it
     */
    int c;
    cbreak();
    c = getch();
    return c;
}

int getche()
{
	int c = getch_();
	if (c == 27)
	{
		nodelay(stdscr, true);
		c = getch_();
		if (c == ERR)
			c = 27;
		else if (c == 91)
		{
			c = getch_();
			if (c < 65 || c > 68)
			{
				ungetch(c);
			}
			switch (c)
			{
				case 65:
					c = ARROW_UP;
					break;
				case 66:
					c = ARROW_DOWN;
					break;
				case 67:
					c = ARROW_RIGHT;
					break;
				case 68:
					c = ARROW_LEFT;
					break;
			}
		}
		nodelay(stdscr, false);
	}
	//nocbreak();
	return c;
}

char getmod()
{
	WINDOW *w = newwin(9, 70, LINES / 2, COLS / 2);
	wclear(w);
	wprintw(w, "\n"
		" & -- Small bug          %%     -- Large bug\n"
		" ! -- Vicious pitbull    $     -- Worm\n"
		" g -- Guard              z     -- Zombie\n"
		" - -- Tapeworm           b     -- boss\n"
		" k -- Key                @     -- Teleport\n"
		" ~ -- Empty              enter -- No change"
		);
	wborder(w, 0, 0, 0, 0, 0, 0, 0, 0);
	wrefresh(w);
	char newc = getch();
	wclear(w);
	return newc;
}

void modify(int x, int y, char map[30][30])
{
	char newopt = getmod();
	if (newopt == '\n')
		return;
	else
		map[y][x] = newopt;
}

void showmap(int x, int y, char map[30][30], WINDOW *w)
{
	wclear(w);
	int ypos, xpos;
	char space = ' ';
	for (ypos = 0; ypos < 30; ypos++)
	{
		for (xpos = 0; xpos < 30; xpos++)
		{
			if (ypos == y && xpos == x)
			{
				wprintw(w, "*");
				space = '*';
			}
			else
			{
				wprintw(w, " ");
				space = ' ';
			}
			wprintw(w, "%c%c", map[ypos][xpos], space);
		}
		wprintw(w, "\n");
	}
	wrefresh(w);
}


int main(int argc, char * * argv)
{
	char map[30][30];
	int xpos, ypos;
	WINDOW *w;
	int i, x;
	int opt = 0;
	char val = 0;
	FILE *f;

	initscr();
	noecho();
	w = newwin(LINES, COLS, 0, 0);
	wclear(w);

	xpos = ypos = 0;

	if ((f = fopen(argv[1], "r")) == NULL)
	{
		for (i = 0; i < 30; i++)
		{
			for (x = 0; x < 30; x++)
			{
				map[i][x] = '~';
			}
		}
	}
	else
	{
		for (i = 0; i < 30; i++)
		{
			for (x = 0; x < 30; x++)
			{
				fscanf(f, "%c  ", &map[i][x]);
			}
		}
		fclose(f);
	}

	while (opt != 'Q')
	{
		val = 0;
		showmap(xpos, ypos, map, w);
		opt = getche();
		switch (opt)
		{
			case ARROW_UP:
				if (ypos - 1 >= 0) ypos -= 1;
				break;
			case ARROW_LEFT:
				if (xpos - 1 >= 0) xpos -= 1;
				break;
			case ARROW_DOWN:
				if (ypos + 1 < 30) ypos += 1;
				break;
			case ARROW_RIGHT:
				if (xpos + 1 < 30) xpos += 1;
				break;
			case 'S':
				f = fopen(argv[1], "w");
				for (i = 0; i < 30; i++)
				{
					for (x = 0; x < 30; x++)
					{
						fprintf(f, "%c  ", map[i][x]);
					}
					fprintf(f, "\n");
				}
				fclose(f);
				break;
			case 'm':
				modify(xpos, ypos, map);
				break;
			case '\n': break;
			case '`':
				val = '~';
				break;
			case '1':
				val = '!';
				break;
			case '2':
				val = '@';
				break;
			case '3':
				val = '#';
				break;
			case '4':
				val = '$';
				break;
			case '5':
				val = '%';
				break;
			case '7':
				val = '&';
				break;
			case 'k':
				val = 'k';
				break;
			case 'b':
				val = 'b';
				break;
			case 'z':
				val = 'z';
				break;
		}
		if (val > 0)
			map[ypos][xpos] = val;
	}
	endwin();
}
