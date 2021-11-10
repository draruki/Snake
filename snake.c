#include <windows.h>
#include <stdlib.h>
#include "curses.h"
#include "game.h"

static const int WIDTH = 80;
static const int HEIGHT = 24;

int score = 0;

static void move_snake(Snake* snk, int x, int y);
static void draw_snake_full(Snake* snk, char char_part);
static bool snake_collision_check(Snake* snk, Snake* head);

void add_snake_child(Snake* snk)
{
	if (snk->child != NULL)
	{
		add_snake_child(snk->child);
	}
	else
	{
		snk->child = malloc(sizeof(Snake));
		snk->child->x = snk->x;
		snk->child->y = snk->y;
		snk->child->child = NULL;
	}
}

void dispose_snake(Snake* snk)
{
	if (snk->child != NULL)
	{
		dispose_snake(snk->child);
		snk->child = NULL;
	}

	free(snk);
}

static void move_snake(Snake* snk, int x, int y)
{
	if (snk->child != NULL)
	{
		move_snake(snk->child, snk->x, snk->y);
	}

	snk->x = x;
	snk->y = y;
}

bool update_snake(Snake* snk, Apple* apl)
{
	int dx, dy;
	dx = dy = 0;

	switch (snk->head_direction)
	{
		case DIR_LEFT: 	dx -= 1; break;
		case DIR_DOWN: 	dy += 1; break;
		case DIR_RIGHT: dx += 1; break;
		case DIR_UP: 	dy -= 1; break;
	}
	move_snake(snk, snk->x + dx, snk->y + dy);

	if (snk->x < 0) 		{score = 0; return false;}
	if (snk->x > WIDTH) 	{score = 0; return false;}
	if (snk->y < 0) 		{score = 0; return false;}
	if (snk->y > HEIGHT) 	{score = 0; return false;}

	if (snk->x == apl->x && snk->y == (*apl).y)
	{
		randomize_apple(apl);
		add_snake_child(snk);
		score += 1;  
		char str[40];
   		sprintf(str, "Snake [%i]", score);
		SetConsoleTitle(str);
	}
	if (snake_collision_check(snk, snk) == true) 
	{
		score = 0;
		return false;
	}

	return true;
}

static bool snake_collision_check(Snake* snk, Snake* head)
{
	if (snk->child != NULL)
	{
		if (snake_collision_check(snk->child, head) == true)
			return true;
	}
	if (snk == head) return false;

	return snk->x == head->x && snk->y == head->y;
}

void draw_snake(Snake* snk)
{
	draw_snake_full(snk, CHAR_SNAKE_HEAD);
}

static void draw_snake_full(Snake* snk, char char_part)
{
	if (snk->child != NULL)
		draw_snake_full(snk->child,CHAR_SNAKE_BODY);
	else
	{
		char_part = CHAR_SNAKE_TAIL;
	}

	if (char_part == CHAR_SNAKE_HEAD)
		attron(COLOR_PAIR(COLOR_TONGUE));
	else
		attron(COLOR_PAIR(COLOR_SNAKE));

	move(snk->y, snk->x);
	addch(char_part);
	attron(COLOR_PAIR(0));
}