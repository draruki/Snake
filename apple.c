#include <stdlib.h>
#include "curses.h"
#include "game.h"
#include "rand.h"

static const int WIDTH = 80;
static const int HEIGHT = 24;

void randomize_apple(Apple* apl)
{
	apl->x = rand_interval(0, WIDTH-1);
	apl->y = rand_interval(0, HEIGHT-1);
}

void draw_apple(Apple* apl)
{
	attron(COLOR_PAIR(COLOR_APPLE));
	mvaddch(apl->y, apl->x, CHAR_APPLE);
	attron(COLOR_PAIR(0));
}