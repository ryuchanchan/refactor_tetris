#include "tetris.h"

void operate(char c, t_game *game)
{
    int i, j;

    t_block temp = Duplicate_block(current);
    switch(c){
        case 's':
            temp.row++;  //move down
            if(Check_block_position(temp, game))
                current.row++;
            else {
                for(i = 0; i < current.width ;i++){
                    for(j = 0; j < current.width ; j++){
                        if(current.shape[i][j])
                            game->map[current.row+i][current.col+j] = current.shape[i][j];
                    }
                }
                int n, m, sum, count=0;
                for(n = 0; n < length_size; n++){
                    sum = 0;
                    for(m = 0; m < width_size; m++) {
                        sum+=game->map[n][m];
                    }
                    if(sum==width_size){
                        count++;
                        int l, k;
                        for(k = n; k >= 1; k--)
                            for(l=0; l < width_size; l++)
                                game->map[k][l] = game->map[k-1][l];
                        for(l=0; l < width_size; l++)
                            game->map[k][l]=0;
                        game->speed -= game->decrease--;
                    }
                }
                game->score += 100*count;
                t_block new_shape = create_block();
                Free_block(current);
                current = new_shape;
                if(!Check_block_position(current, game)){
                    game->status = false;
                }
            }
            break;
        case 'd':
            temp.col++;
            if(Check_block_position(temp, game))
                current.col++;
            break;
        case 'a':
            temp.col--;
            if(Check_block_position(temp, game))
                current.col--;
            break;
        case 'w':
            Rotate_block(temp);
            if(Check_block_position(temp, game))
                Rotate_block(current);
            break;
        }
        Free_block(temp);
        Print_window(game);
}