/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitoda <hitoda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 01:48:57 by hitoda            #+#    #+#             */
/*   Updated: 2022/08/05 01:51:17 by hitoda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

t_block Duplicate_block(t_block shape){
	t_block new_shape = shape;
	char **copyshape = shape.shape;
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

void Free_block(t_block shape){
    int i;
    for(i = 0; i < shape.width; i++){
		free(shape.shape[i]);
    }
    free(shape.shape);
}

int Check_block_position(t_block shape, t_game *game){
	char **array = shape.shape;
	int i, j;
	for(i = 0; i < shape.width;i++) {
		for(j = 0; j < shape.width ;j++){
			if((shape.col+j < 0 || shape.col+j >= width_size || shape.row+i >= length_size)){
				if(array[i][j])
					return false;
				
			}
			else if(game->map[shape.row+i][shape.col+j] && array[i][j])
				return false;
		}
	}
	return true;
}

void Rotate_block(t_block shape){
	t_block temp = Duplicate_block(shape);
	int i, j, k, width;
	width = shape.width;
	for(i = 0; i < width; i++){
		for(j = 0, k = width - 1; j < width; j++, k--)
				shape.shape[i][j] = temp.shape[k][i];
	}
	Free_block(temp);
}

void Print_window(t_game *game){
	char Buffer[length_size][width_size] = {0};
	int i, j;
	for(i = 0; i < current.width; i++){
		for(j = 0; j < current.width; j++){
			if(current.shape[i][j])
				Buffer[current.row+i][current.col+j] = current.shape[i][j];
		}
	}
	clear();
	for(i = 0; i < width_size - 9; i++)
		printw(" ");
	printw("42 Tetris\n");
	for(i = 0; i < length_size; i++){
		for(j = 0; j < width_size ; j++){
			printw("%c ", (game->map[i][j] + Buffer[i][j])? '#': '.');
		}
		printw("\n");
	}
	printw("\nScore: %d\n", game->score);
}

struct timeval before_now, now;
int check_elapsed_time(t_game *game){
	return ((suseconds_t)(game->now.tv_sec*1000000 + game->now.tv_usec) -((suseconds_t)game->before_now.tv_sec*1000000 + game->before_now.tv_usec)) > game->speed;
}