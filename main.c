#include <stdbool.h>
#include <stdlib.h>
#include <windows.h>
#include "curses.h"
#include "game.h"

#define	ESCAPE				27
#define	UP					119
#define	LEFT				97
#define	DOWN				115
#define	RIGHT				100

#define SLEEP_TIME_MS		45
#define LOSE_TIME_MS		500
#define INITIAL_BODY_PARTS	3

static const int WIDTH = 80;
static const int HEIGHT = 25;

Snake* player_snake;
Apple* apple;

void initialize_ncurses()
{
	initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);
	timeout(0);
	start_color();
	use_default_colors();
	init_pair(COLOR_SNAKE, COLOR_GREEN, COLOR_BLACK);
	init_pair(COLOR_TONGUE, COLOR_RED, COLOR_BLACK);
	init_pair(COLOR_FLOOR, COLOR_WHITE, COLOR_BLACK);
	init_pair(COLOR_APPLE, COLOR_YELLOW, COLOR_BLACK);
	attron(A_BOLD);
	wresize(stdscr, HEIGHT, WIDTH);
}

void terminate_ncurses()
{
	endwin();
}

void update(bool *isRunning)
{
	char c = getch();

	if (c == ESCAPE)
	{
		*isRunning = false;;
	}
	switch (c)
	{
		case LEFT: player_snake->head_direction = (player_snake->head_direction == DIR_RIGHT) ? DIR_RIGHT : DIR_LEFT; break;
		case RIGHT: player_snake->head_direction = (player_snake->head_direction == DIR_LEFT) ? DIR_LEFT : DIR_RIGHT; break;
		case UP: player_snake->head_direction = (player_snake->head_direction == DIR_DOWN) ? DIR_DOWN : DIR_UP; break;
		case DOWN: player_snake->head_direction = (player_snake->head_direction == DIR_UP) ? DIR_UP : DIR_DOWN; break;
	}
	if (c == 'p')
		add_snake_child(player_snake);

	 if (update_snake(player_snake, apple) == false)
	 {
	 	restart_game();
	 }
}

void render()
{
	int rows, cols;
	getmaxyx(stdscr, rows, cols);
	int i;
	int j;

	for (i = 0; i < cols; ++i)
	{
		for (j = 0; j < rows; ++j)
		{
			attron(COLOR_PAIR(COLOR_FLOOR));
			move(j, i);
			addch(CHAR_FLOOR);
			attron(COLOR_PAIR(0));
		}
	}

	draw_apple(apple);
	draw_snake(player_snake);
	refresh();
}

void dispose()
{
	dispose_snake(player_snake);
	free(apple);
}

void restart_game()
{
	dispose();
	snake();
	Sleep(LOSE_TIME_MS);
}

void snake()
{
	SetConsoleTitle("Snake [0]");
	player_snake = malloc(sizeof(Snake));
	player_snake->x = 24;
	player_snake)->y = 8;
	player_snake->head_direction = DIR_RIGHT;
	player_snake->child  = NULL;
	apple = malloc(sizeof(Apple));
	randomize_apple(apple);
	randomize_apple(apple);
	randomize_apple(apple);

	int i = 0;
	while (i < INITIAL_BODY_PARTS)
	{
		add_snake_child(player_snake);
		++i;
	}
}

int main()
{
	initialize_ncurses();
	snake();
	render();

	bool isRunning = true;
	while (isRunning)
	{
		update(&isRunning);
		render();
		Sleep(SLEEP_TIME_MS);
	}

	dispose();
	terminate_ncurses();
	return 0;
}