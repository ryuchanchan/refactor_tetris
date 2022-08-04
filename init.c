/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitoda <hitoda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 01:41:06 by hitoda            #+#    #+#             */
/*   Updated: 2022/08/05 01:54:59 by hitoda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

static const t_block StructsArray[7]= {
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

static void init_map(t_game *game)
{
	for(int i=0; i<length_size; i++)
	{
		for(int j=0; j<width_size; j++)
		{
			game->map[i][j] = 0;
		}
	}
}

void init_game(t_game *game)
{
	init_map(game);
	game->score = 0;
	game->speed = 400000;
	game->decrease = 1000;
	srand(time(0));
	initscr();
	timeout(1);
	gettimeofday(&game->before_now, NULL);
	t_block new_shape = Duplicate_block(StructsArray[rand()%7]);
	new_shape.col = rand() % (width_size - new_shape.width + 1);
    new_shape.row = 0;
	Free_block(current);
	current = new_shape;
	if(!Check_block_position(current, game))
		game->status = false;
	else
		game->status = true;
    Print_window(game);
}