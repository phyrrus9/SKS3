#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#define RED "\33[31m"
#define RESET "\33[0m"

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
	char opt = 0;
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
		showmap(xpos, ypos, map, w);
		opt = getch();
		switch (opt)
		{
			case 'w':
				if (ypos - 1 >= 0) ypos -= 1;
				break;
			case 'a':
				if (xpos - 1 >= 0) xpos -= 1;
				break;
			case 's':
				if (ypos + 1 < 30) ypos += 1;
				break;
			case 'd':
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
		}
	}
	endwin();
}
