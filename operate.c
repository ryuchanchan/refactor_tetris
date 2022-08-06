/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitoda <hitoda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 23:47:56 by rykawamu          #+#    #+#             */
/*   Updated: 2022/08/07 01:24:32 by hitoda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

static void    insert_block_to_map(t_game *game)
{
    int i, j;
    t_block *current;

    for(i = 0; i < current->width ;i++){
        for(j = 0; j < current->width ; j++){
            if(current->shape[i][j])
                game->map[current->position_y+i][current->position_x+j] = current->shape[i][j];
        }
    }
}

static void erase_line_from_map(int row, t_game  *game)
{
    int i, j;
    for(i = row; i >= 1; i--)
        for(j=0; j < MAP_WIDTH; j++)
            game->map[i][j] = game->map[i-1][j];
    for(j=0; j < MAP_WIDTH; j++)
        game->map[i][j]=0;
    game->speed -= game->time_decrease--;
    game->score += 100;
}

static void check_row_filled(t_game   *game)
{
    int row, col, filled;
    for(row = 0; row < MAP_HEIGHT; row++){
        filled = 0;
        for(col = 0; col < MAP_WIDTH; col++)
            filled+=game->map[row][col];
        if(filled==MAP_WIDTH)
            erase_line_from_map(row, game);
    }
}

void operate(char c, t_game *game)
{
    int i, j;
    t_block *current;

    t_block temp = duplicate_block(*current);
    switch(c){
        case 's':
            temp.position_y++;	//move down
            break;
        case 'd':	//move right
            temp.position_x++;
            break;
        case 'a':	//move left
            temp.position_x--;
            break;
        case 'w':	//rotate
            rotate_block(temp);
            break;
    }
	if(check_new_position(temp, game))
	{
		free_block(*current);
		current = &temp;
	}
	else if (c == 's')
	{
		insert_block_to_map(game);
		check_row_filled(game);
		t_block new_shape = create_block();
		free_block(*current);
		current = &new_shape;
		if(!check_new_position(*current, game)){
			game->status = false;
		}
		free_block(temp);
	}
	else
		free_block(temp);
	print_window(game);
}
