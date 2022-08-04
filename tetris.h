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
Struct current;

typedef struct {
    char **shape;
    int width, row, col;
} t_block;


typedef struct {
	char **map;
	unsigned int score;
	bool status;
	suseconds_t speed;
	int decrease;
	struct timeval before_now;
	struct timeval now;
} t_game;

const Struct StructsArray[7] = {
	{(char *[]){(char []){0,1,1},
				(char []){1,1,0},
				(char []){0,0,0}}, 3},
	{(char *[]){(char []){1,1,0},
				(char []){0,1,1},
				(char []){0,0,0}}, 3},
	{(char *[]){(char []){0,1,0},
				(char []){1,1,1},
				(char []){0,0,0}}, 3},
	{(char *[]){(char []){0,0,1},
				(char []){1,1,1},
				(char []){0,0,0}}, 3},
	{(char *[]){(char []){1,0,0},
				(char []){1,1,1}, 
				(char []){0,0,0}}, 3},
	{(char *[]){(char []){1,1},
				(char []){1,1}}, 2},
	{(char *[]){(char []){0,0,0,0},
				(char []){1,1,1,1},
				(char []){0,0,0,0}, 
				(char []){0,0,0,0}}, 4}
};

// char Table[length_size][width_size] = {0};
// int score = 0;
// char game_start = true;
// suseconds_t timer = 400000;
// int decrease = 1000;

Struct Duplicate_block(Struct shape);

void operate(char c);

void Free_block(Struct shape);
void Rotate_block(Struct shape);
void Print_window();
int Check_block_position(Struct shape);

#endif