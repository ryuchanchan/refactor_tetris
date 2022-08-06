/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rykawamu </var/mail/rykawamu>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 23:47:56 by rykawamu          #+#    #+#             */
/*   Updated: 2022/08/06 23:48:00 by rykawamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

void operate(char c, t_game *game)
{
    int i, j;

    t_block temp = duplicate_block(current);
    switch(c){
        case 's':
            temp.position_y++;  //move down
            if(check_new_position(temp, game))
                current.position_y++;
            else {
                for(i = 0; i < current.width ;i++){
                    for(j = 0; j < current.width ; j++){
                        if(current.shape[i][j])
                            game->map[current.position_y+i][current.position_x+j] = current.shape[i][j];
                    }
                }
                int n, m, sum, count=0;
                for(n = 0; n < MAP_HEIGHT; n++){
                    sum = 0;
                    for(m = 0; m < MAP_WIDTH; m++) {
                        sum+=game->map[n][m];
                    }
                    if(sum==MAP_WIDTH){
                        count++;
                        int l, k;
                        for(k = n; k >= 1; k--)
                            for(l=0; l < MAP_WIDTH; l++)
                                game->map[k][l] = game->map[k-1][l];
                        for(l=0; l < MAP_WIDTH; l++)
                            game->map[k][l]=0;
                        game->speed -= game->time_decrease--;
                    }
                }
                game->score += 100*count;
                t_block new_shape = create_block();
                free_block(current);
                current = new_shape;
                if(!check_new_position(current, game)){
                    game->status = false;
                }
            }
            break;
        case 'd':
            temp.position_x++;
            if(check_new_position(temp, game))
                current.position_x++;
            break;
        case 'a':
            temp.position_x--;
            if(check_new_position(temp, game))
                current.position_x--;
            break;
        case 'w':
            rotate_block(temp);
            if(check_new_position(temp, game))
                rotate_block(current);
            break;
        }
        free_block(temp);
        print_window(game);
}
