#include "tetris.h"

void operate(char c)
{
    
    char Table[length_size][width_size] = {0};
    int score = 0;
    char game_start = true;
    suseconds_t timer = 400000;
    int decrease = 1000;
	int i, j;
	Struct temp = Duplicate_block(current);
	switch(c){
				case 's':
					temp.row++;  //move down
					if(Check_block_position(temp))
						current.row++;
					else {
						for(i = 0; i < current.width ;i++){
							for(j = 0; j < current.width ; j++){
								if(current.array[i][j])
									Table[current.row+i][current.col+j] = current.array[i][j];
							}
						}
						int n, m, sum, count=0;
						for(n = 0; n < length_size; n++){
							sum = 0;
							for(m = 0; m < width_size; m++) {
								sum+=Table[n][m];
							}
							if(sum==width_size){
								count++;
								int l, k;
								for(k = n; k >= 1; k--)
									for(l=0; l < width_size; l++)
										Table[k][l] = Table[k-1][l];
								for(l=0; l < width_size; l++)
									Table[k][l]=0;
								timer-=decrease--;
							}
						}
						score += 100*count;
						Struct new_shape = Duplicate_block(StructsArray[rand() % 7]);
						new_shape.col = rand() % (width_size - new_shape.width + 1);
						new_shape.row = 0;
						Free_block(current);
						current = new_shape;
						if(!Check_block_position(current)){
							game_start = false;
						}
					}
					break;
				case 'd':
					temp.col++;
					if(Check_block_position(temp))
						current.col++;
					break;
				case 'a':
					temp.col--;
					if(Check_block_position(temp))
						current.col--;
					break;
				case 'w':
					Rotate_block(temp);
					if(Check_block_position(temp))
						Rotate_block(current);
					break;
			}
			Free_block(temp);
			Print_window();
}
