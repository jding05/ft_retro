#include <ncurses.h>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Entity.hpp"
#include "Include.hpp"
#include "Sprite.hpp"
#include "Ascii.hpp"
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#define LIFE 1
#define COLLIDE_NB 3
int G_GAMEOVER = 0;
int	G_KILL = 0;
int	G_BULLS = 10;
int	G_BOSS = 0;

static void	init_ncurse(void)
{
	initscr();
	raw();
	noecho();
	timeout(0);
	curs_set(FALSE);
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	start_color();
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_RED, COLOR_RED);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLUE);
	init_pair(5, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(6, COLOR_CYAN, COLOR_CYAN);
	init_pair(7, COLOR_WHITE, COLOR_CYAN);
	init_pair(8, COLOR_RED, COLOR_BLACK);
}

static	void gameinfo(int i, struct	tm *cur_time)
{
	mvprintw(0, 10, "====================================");
	mvprintw(1, 10, "===         GAME  INFO           ===");
	mvprintw(2, 10, "====================================");
	mvprintw(3, 10, " Game time: %dh %dm %ds              ",
				cur_time->tm_hour - 16, cur_time->tm_min,cur_time->tm_sec);
	mvprintw(4, 10, " YOU ONLY HAVE ONE LIFE!            ");
	mvprintw(5, 10, " KILL: %d / %d                   ", G_KILL, NUM);
	mvprintw(6, 10, " cycle: %d                      ", i);
	mvprintw(7, 10, " Kill BOSS: %d / %d            ", G_BOSS, WINNER);
	mvprintw(8, 10, "====================================");
}

static bool	gameover_page(void)
{
	int dir = 0;
	refresh();
	erase();
	mvprintw(6, 30, "GAME OVER");
	mvprintw(7, 30, "Your Score is %d", G_KILL);

	mvprintw(10, 30, "Would you like to continue? Y/N....");
	G_GAMEOVER = 0;
	G_KILL = 0;
	G_BULLS = 10;
	G_BOSS = 0;
	while (1)
	{
		dir = getch();
		if (dir == 'y')
			return (true);
		else if (dir == 27 || dir =='q' || dir == 'n')
			return (false);
	}
	return (false);
}

static bool	win_page(void)
{
	int dir = 0;
	std::string buf;
	refresh();
	erase();
	splash();
	refresh();
	G_GAMEOVER = 0;
	G_KILL = 0;
	G_BULLS = 10;
	G_BOSS = 0;
	erase();
	mvprintw(6, 30, "YOU ARE THE WINNER !!! your score is: %d", G_KILL + WINNER);
	mvprintw(10, 30, "Press space bar to continue your journey...");
	mvprintw(11, 35, "Or <Q> or <ESC> to quit.");
	refresh();
	while (1)
	{
		dir = getch();
		if (dir == 27 || dir =='q')
			return (false);
		else if (dir == 32)
			return (true);
	}
	return (false);
}

int		main(void)
{
	int	row, col, dir, i = 0, check = 0;
	struct timespec wait, null;
	wait.tv_sec = 0;
	wait.tv_nsec = 20000000;
	srand(time(NULL));
	time_t	clk, slk = time(NULL);
	struct	tm *cur_time;
	init_ncurse();
	getmaxyx(stdscr, row, col);
	Player *player = new Player(20, 10);
	Enemy **guys = new Enemy*[NUM];
	Sprite **cld = new Sprite*[9];
	Sprite	plane = Sprite(abs(rand() % (col / 2) + (col / 4)), -18);
	for (dir = 0; dir < 9; dir++)
		cld[dir] = new Sprite((rand() % 300), dir * 9 );
	for ( dir = 0; dir < NUM; dir++ )
		guys[dir] = new Enemy(col, rand() % row);
	while (1)
	{
		if (G_GAMEOVER < LIFE && G_BOSS <= WINNER)
		{
			clk = time(NULL);
			clk -= slk;
			cur_time = localtime(&clk);
			for (dir = 0; dir < 9; dir++)
				cld[dir]->sprite();
			if (i % 3 == 0)
				for (dir = 0; dir < 9; dir++)
					cld[dir]->move();
			if (check == 0)
			{
				if (G_KILL >= NUM)
				{
					getmaxyx(stdscr, row, col);
					Sprite	plane = Sprite(0, rand() % (col - 40));
					plane.fly();
					check = 1;
				}
			}
			else
			{
				if (plane.getY() > 100)
					check = 0;
				plane.fly();
				if (rand() % 10 == 0)
					if (plane.drop() == true)
						plane.~Sprite();
			}
			gameinfo(i, cur_time);
			dir = getch();
			switch (dir)
			{
			case KEY_LEFT: player->left(); break;
			case KEY_RIGHT: player->right(); break;
			case KEY_UP: player->up(); break;
			case KEY_DOWN: player->down(); break;
			case 'w' : case 's' : case 'a' : case 'd' : player->shoot(dir); break;
			case 27: case 'q':
				endwin();
				delete player;
				delete [] guys;
				delete [] cld;
				return (0);
				break;
			default: break;
			}
			player->Weapon::update();
			for (dir = 0; dir < G_KILL + 1 && dir < NUM; dir++)
			{
				guys[dir]->update();
				guys[dir]->Weapon::update();
			}
			player->update();
			refresh();
			nanosleep(&wait, &null);
			erase();
			i++;
		}
		else if (G_GAMEOVER >= LIFE)
		{
			if (gameover_page() == true)
			{
				getmaxyx(stdscr, row, col);
				for ( dir = 0; dir < NUM; dir++ )
					guys[dir]->setMaxs(col, row);
				player->respawn(10, 20);
				continue ;
			}
			else
			{
				endwin();
				delete player;
				delete [] guys;
				delete [] cld;
				return (0);
			}
		}
		else
		{
			if (win_page() == true)
			{
				getmaxyx(stdscr, row, col);
				for ( dir = 0; dir < NUM; dir++ )
					guys[dir]->setMaxs(col, row);
				player->respawn(10, 20);
				continue ;
			}
			else
			{
				endwin();
				delete player;
				delete [] guys;
				delete [] cld;
				return (0);
			}
		}
	}
	endwin();
	return (0);
}
