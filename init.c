/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitoda <hitoda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 01:41:06 by hitoda            #+#    #+#             */
/*   Updated: 2022/08/05 02:42:45 by hitoda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

static void init_game_info(t_game *game)
{
	game->score = 0;
	game->speed = 400000;
	game->decrease = 1000;
	for(int i=0; i<length_size; i++)
	{
		for(int j=0; j<width_size; j++)
			game->map[i][j] = 0;
	}
	gettimeofday(&game->before_now, NULL);
}

void init_game(t_game *game)
{
	srand(time(0));
	init_game_info(game);

	t_block new_block = create_block();
	Free_block(current);
	current = new_block;
	if(!Check_block_position(current, game))
		game->status = false;
	else
		game->status = true;

	initscr();
	timeout(1);
    Print_window(game);
}
