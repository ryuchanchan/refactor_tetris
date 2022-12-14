/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitoda <hitoda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 23:47:56 by rykawamu          #+#    #+#             */
/*   Updated: 2022/08/07 04:20:17 by hitoda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

static void	insert_block_to_map(t_game *game)
{
    int i, j;

    for(i = 0; i < game->current.width ;i++){
        for(j = 0; j < game->current.width ; j++){
            if(game->current.shape[i][j])
                game->map[game->current.position_y + i][game->current.position_x + j] = game->current.shape[i][j];
        }
    }
}

static void erase_line_from_map(int row, t_game *game)
{
    int i, j;
	
    for(i = row; i >= 1; i--)
	{
		for(j = 0; j < MAP_WIDTH; j++)
            game->map[i][j] = game->map[i-1][j];
	}
    for(j = 0; j < MAP_WIDTH; j++)
        game->map[i][j] = 0;
}

static void check_row_filled(t_game *game)
{
    int row, col, filled;
    for(row = 0; row < MAP_HEIGHT; row++){
        filled = 0;
        for(col = 0; col < MAP_WIDTH; col++)
            filled += game->map[row][col];
        if(filled == MAP_WIDTH)
		{
			erase_line_from_map(row, game);
			game->speed -= game->time_decrease--;
    		game->score += 100;
		}
    }
}

static void	next_block(t_game *game)
{
	insert_block_to_map(game);
	check_row_filled(game);
	free_block(&game->current);
	game->current = create_block();
	if(!check_new_position(game, &game->current))
		game->status = false;
}

void key_operate(char key, t_game *game)
{
    t_block temp = duplicate_block(game->current);

    switch(key)
	{
        case 's':	//move down
            temp.position_y++;
            break;
        case 'd':	//move right
            temp.position_x++;
            break;
        case 'a':	//move left
            temp.position_x--;
            break;
        case 'w':	//rotate
            rotate_block(&temp);
            break;
    }
	if(check_new_position(game, &temp))
	{
		free_block(&game->current);
		game->current = temp;
	}
	else if (key == 's')
	{
		next_block(game);
		free_block(&temp);
	}
	else
		free_block(&temp);
	print_window(game);
}
