/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitoda <hitoda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 01:41:06 by hitoda            #+#    #+#             */
/*   Updated: 2022/08/07 04:17:53 by hitoda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

static void init_game_info(t_game *game)
{
	int i, j;

	game->score = 0;
	game->speed = 400000;
	game->time_decrease = 1000;
	for(i = 0; i < MAP_HEIGHT; i++)
	{
		for(j = 0; j < MAP_WIDTH; j++)
			game->map[i][j] = 0;
	}
	gettimeofday(&game->previous_time, NULL);
}

void init_game(t_game *game)
{
	srand(time(0));
	init_game_info(game);

	game->current = create_block();
	if(!check_new_position(game, &game->current))
		game->status = false;
	else
		game->status = true;
	initscr();
	timeout(1);
    print_window(game);
}
