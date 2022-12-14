/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitoda <hitoda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 02:29:31 by hitoda            #+#    #+#             */
/*   Updated: 2022/08/07 03:47:25 by hitoda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

t_block duplicate_block(t_block block)
{
	t_block new_block = block;
	int i, j;

	new_block.shape = (char**)malloc(new_block.width * sizeof(char*));
	if (!new_block.shape)
		exit(EXIT_FAILURE);
    for(i = 0; i < new_block.width; i++)
	{
		new_block.shape[i] = (char*)malloc(new_block.width * sizeof(char));
		if (!new_block.shape[i])
			exit(EXIT_FAILURE);
		for(j = 0; j < new_block.width; j++)
		{
			new_block.shape[i][j] = block.shape[i][j];
		}
    }
    return new_block;
}

void free_block(t_block *block)
{
    int i;
	
    for(i = 0; i < block->width; i++){
		free(block->shape[i]);
    }
    free(block->shape);
}

int check_new_position(t_game *game, t_block *block)
{
	int i, j;

	for(i = 0; i < block->width;i++) {
		for(j = 0; j < block->width ;j++){
			if((block->position_x + j) < 0 || MAP_WIDTH <= (block->position_x + j) \
				|| MAP_HEIGHT <= (block->position_y + i)){
				if(block->shape[i][j])
					return false;
			}
			else if(game->map[block->position_y + i][block->position_x + j] && block->shape[i][j])
				return false;
		}
	}
	return true;
}

void rotate_block(t_block *block)
{
	int i, j, k;

	t_block temp = duplicate_block(*block);
	for(i = 0; i < block->width; i++)
	{
		for(j = 0, k = (block->width - 1); j < block->width; j++, k--)
			block->shape[i][j] = temp.shape[k][i];
	}
	free_block(&temp);
}

t_block create_block()
{
	const t_block block_patterns[BLOCK_TYPE]= {
	{(char *[]){(char []){0,1,1},
				(char []){1,1,0},
				(char []){0,0,0}}, 3, 0, 0},
	{(char *[]){(char []){1,1,0},
				(char []){0,1,1},
				(char []){0,0,0}}, 3, 0, 0},
	{(char *[]){(char []){0,1,0},
				(char []){1,1,1},
				(char []){0,0,0}}, 3, 0, 0},
	{(char *[]){(char []){0,0,1},
				(char []){1,1,1},
				(char []){0,0,0}}, 3, 0, 0},
	{(char *[]){(char []){1,0,0},
				(char []){1,1,1}, 
				(char []){0,0,0}}, 3, 0, 0},
	{(char *[]){(char []){1,1},
				(char []){1,1}}, 2, 0, 0},
	{(char *[]){(char []){0,0,0,0},
				(char []){1,1,1,1},
				(char []){0,0,0,0}, 
				(char []){0,0,0,0}}, 4, 0, 0}
	};

	t_block new_block = duplicate_block(block_patterns[rand()%BLOCK_TYPE]);
	new_block.position_x = rand() % (MAP_WIDTH - new_block.width + 1);
    new_block.position_y = 0;

	return new_block;
}
