#include <stdbool.h>

#define	CHAR_SNAKE_HEAD		'*'
#define	CHAR_SNAKE_BODY		'O'
#define	CHAR_SNAKE_TAIL		'o'
#define	CHAR_FLOOR			' '
#define CHAR_APPLE			'+'

enum colors {COLOR_SNAKE = 1, COLOR_TONGUE, COLOR_FLOOR, COLOR_APPLE};
enum directions {DIR_LEFT, DIR_DOWN, DIR_RIGHT, DIR_UP};

//-----MAIN.C-----
void restart_game();
void snake();

//-----APPLE.C-----
typedef struct
{
	int x;
	int y;
} Apple;
void randomize_apple(Apple*);
void draw_apple(Apple*);

//-----SNAKE.C-----
typedef struct snake
{
	int x;
	int y;
	int head_direction;
	struct snake* child;
} Snake;
void add_snake_child(Snake*);
bool update_snake(Snake*, Apple*);
void draw_snake(Snake*);
void dispose_snake(Snake*);