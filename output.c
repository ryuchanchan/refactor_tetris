/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitoda <hitoda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 21:25:18 by hitoda            #+#    #+#             */
/*   Updated: 2022/08/07 04:13:08 by hitoda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

static void	print_map(t_game *game)
{
	int i, j;

	for(i = 0; i < MAP_HEIGHT; i++){
		for(j = 0; j < MAP_WIDTH; j++){
			printf("%c ", game->map[i][j] ? '#': '.');
		}
		printf("\n");
	}
}

void	end_game(t_game *game)
{
	free_block(&game->current);
	endwin();
	print_map(game);
	printf("\nGame over!\n");
	printf("\nScore: %d\n", game->score);
}