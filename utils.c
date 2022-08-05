/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitoda <hitoda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 01:48:57 by hitoda            #+#    #+#             */
/*   Updated: 2022/08/06 04:27:59 by hitoda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

static char check_current_block_position(int i, int j)
{
	if (current.position_y <= i && i < current.position_y + current.width \
		&& current.position_x <= j && j < current.position_x + current.width)
	{
		if (current.shape[i - current.position_y][j - current.position_x])
			return (1);
	}
	return (0);
}

static void print_current_game(t_game *game)
{
	int i, j;
	char current_block;

	for(i = 0; i < MAP_HEIGHT; i++){
		for(j = 0; j < MAP_WIDTH ; j++){
			current_block = check_current_block_position(i, j);
			printw("%c ", (game->map[i][j] + current_block)? '#': '.');
		}
		printw("\n");
	}
}

void print_window(t_game *game)
{
	int i;

	clear();
	for(i = 0; i < MAP_WIDTH - 9; i++)
		printw(" ");
	printw("42 Tetris\n");
	print_current_game(game);
	printw("\nScore: %d\n", game->score);
}

struct timeval previous_time, now;
int check_time_diff(t_game *game)
{
	return ((suseconds_t)(game->now.tv_sec*1000000 + game->now.tv_usec) -((suseconds_t)game->previous_time.tv_sec*1000000 + game->previous_time.tv_usec)) > game->speed;
}