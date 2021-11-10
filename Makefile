CC=gcc
CFLAGS= -Wall -std=c99

game: main.c
	$(CC) $(CFLAGS) main.c snake.c apple.c game.res -o Snake -lpdcurses