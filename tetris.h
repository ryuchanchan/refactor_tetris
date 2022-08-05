#ifndef TETRIS_H
# define TETRIS_H

#include <stdlib.h>
#include <sys/time.h>
#include <ncurses.h>

#define length_size 20
#define width_size 15

typedef struct {
    char **array;
    int width, row, col;
} Struct;

typedef struct {
    char **shape;
    int width, row, col;
} t_block;
t_block current;

typedef struct {
	char map[length_size][width_size];
	unsigned int score;
	bool status;
	suseconds_t speed;
	int decrease;
	struct timeval before_now;
	struct timeval now;
} t_game;


// utils.c
t_block Duplicate_block(t_block shape);
void Free_block(t_block shape);
int Check_block_position(t_block shape, t_game *game);
void Rotate_block(t_block shape);
void Print_window(t_game *game);
int check_elapsed_time(t_game *game);

// init.c
void init_game(t_game *game);

// block.c
t_block create_block();

// operate.c
void operate(char c, t_game *game);

// output.c
void	output_tetris(t_game	game);
#endif