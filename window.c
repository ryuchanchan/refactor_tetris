/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitoda <hitoda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 21:33:06 by hitoda            #+#    #+#             */
/*   Updated: 2022/08/07 04:13:43 by hitoda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

static char check_current_block_position(int i, int j, t_block *current)
{
	if (current->position_y <= i && i < current->position_y + current->width \
		&& current->position_x <= j && j < current->position_x + current->width)
	{
		if (current->shape[i - current->position_y][j - current->position_x])
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
			current_block = check_current_block_position(i, j, &game->current);
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
