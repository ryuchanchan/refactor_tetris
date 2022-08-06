/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitoda <hitoda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 02:29:31 by hitoda            #+#    #+#             */
/*   Updated: 2022/08/06 21:48:56 by hitoda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

t_block duplicate_block(t_block block){
	t_block new_shape = block;
	char **copyshape = block.shape;
	new_shape.shape = (char**)malloc(new_shape.width*sizeof(char*));
    int i, j;
    for(i = 0; i < new_shape.width; i++){
		new_shape.shape[i] = (char*)malloc(new_shape.width*sizeof(char));
		for(j=0; j < new_shape.width; j++) {
			new_shape.shape[i][j] = copyshape[i][j];
		}
    }
    return new_shape;
}

void free_block(t_block block){
    int i;
    for(i = 0; i < block.width; i++){
		free(block.shape[i]);
    }
    free(block.shape);
}

int check_new_position(t_block block, t_game *game){
	char **array = block.shape;
	int i, j;
	for(i = 0; i < block.width;i++) {
		for(j = 0; j < block.width ;j++){
			if((block.position_x+j < 0 || block.position_x+j >= MAP_WIDTH || block.position_y+i >= MAP_HEIGHT)){
				if(array[i][j])
					return false;
				
			}
			else if(game->map[block.position_y+i][block.position_x+j] && array[i][j])
				return false;
		}
	}
	return true;
}

void rotate_block(t_block block){
	t_block temp = duplicate_block(block);
	int i, j, k, width;
	width = block.width;
	for(i = 0; i < width; i++){
		for(j = 0, k = width - 1; j < width; j++, k--)
				block.shape[i][j] = temp.shape[k][i];
	}
	free_block(temp);
}

t_block create_block()
{
	const t_block block_patterns[BLOCK_TYPE]= {
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

	t_block new_block = duplicate_block(block_patterns[rand()%BLOCK_TYPE]);
	new_block.position_x = rand() % (MAP_WIDTH - new_block.width + 1);
    new_block.position_y = 0;

	return new_block;
}
