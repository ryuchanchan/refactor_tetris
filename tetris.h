/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetris.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitoda <hitoda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 23:49:05 by rykawamu          #+#    #+#             */
/*   Updated: 2022/08/07 03:05:44 by hitoda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TETRIS_H
# define TETRIS_H

#include <stdlib.h>
#include <sys/time.h>
#include <ncurses.h>

#define MAP_HEIGHT 20
#define MAP_WIDTH 15
#define BLOCK_TYPE 7

typedef struct {
    char **shape;
    int width;
	int position_y;
	int position_x;
} t_block;

typedef struct {
	char map[MAP_HEIGHT][MAP_WIDTH];
	unsigned int score;
	bool status;
	suseconds_t speed;
	unsigned int time_decrease;
	struct timeval previous_time;
	struct timeval now;
	t_block current;
} t_game;


// time.c
int check_time_diff(t_game *game);

// init.c
void init_game(t_game *game);

// block.c
t_block duplicate_block(t_block block);
void free_block(t_block *block);
int check_new_position(t_game *game, t_block *block);
void rotate_block(t_block *block);
t_block create_block();

// operate.c
void operate(char c, t_game *game);

// window.c
void print_window(t_game *game);

// output.c
void	end_game(t_game *game);

#endif
