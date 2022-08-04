/*
----やったこと----
- RとCの名前変えた
- TとFをtrue falseにした
- 2つのヘッダーファイル消去
	#include <stdio.h>
	#include <time.h>
- timeoutの関数を消去
- 全体的なfor文の見栄え
- tetris.hの作成
- 変数変えた
    final -> score
    GameON -> game_start
-main（）の中でiとjが何回も宣言されていたので一回に統一(n mとかもiとjではダメ？)
---
*/

#include "tetris.h"

char Table[length_size][width_size] = {0};
int score = 0;
char game_start = true;
suseconds_t timer = 400000;
int decrease = 1000;


Struct Duplicate_block(Struct shape){
	Struct new_shape = shape;
	char **copyshape = shape.array;
	new_shape.array = (char**)malloc(new_shape.width*sizeof(char*));
    int i, j;
    for(i = 0; i < new_shape.width; i++){
		new_shape.array[i] = (char*)malloc(new_shape.width*sizeof(char));
		for(j=0; j < new_shape.width; j++) {
			new_shape.array[i][j] = copyshape[i][j];
		}
    }
    return new_shape;
}

void Free_block(Struct shape){
    int i;
    for(i = 0; i < shape.width; i++){
		free(shape.array[i]);
    }
    free(shape.array);
}

int Check_block_position(Struct shape){
	char **array = shape.array;
	int i, j;
	for(i = 0; i < shape.width;i++) {
		for(j = 0; j < shape.width ;j++){
			if((shape.col+j < 0 || shape.col+j >= width_size || shape.row+i >= length_size)){
				if(array[i][j])
					return false;
				
			}
			else if(Table[shape.row+i][shape.col+j] && array[i][j])
				return false;
		}
	}
	return true;
}

void Rotate_block(Struct shape){
	Struct temp = Duplicate_block(shape);
	int i, j, k, width;
	width = shape.width;
	for(i = 0; i < width; i++){
		for(j = 0, k = width - 1; j < width; j++, k--)
				shape.array[i][j] = temp.array[k][i];
	}
	Free_block(temp);
}

void Print_window(){
	char Buffer[length_size][width_size] = {0};
	int i, j;
	for(i = 0; i < current.width; i++){
		for(j = 0; j < current.width; j++){
			if(current.array[i][j])
				Buffer[current.row+i][current.col+j] = current.array[i][j];
		}
	}
	clear();
	for(i = 0; i < width_size - 9; i++)
		printw(" ");
	printw("42 Tetris\n");
	for(i = 0; i < length_size; i++){
		for(j = 0; j < width_size ; j++){
			printw("%c ", (Table[i][j] + Buffer[i][j])? '#': '.');
		}
		printw("\n");
	}
	printw("\nScore: %d\n", score);
}

struct timeval before_now, now;
int check_elapsed_time(){
	return ((suseconds_t)(now.tv_sec*1000000 + now.tv_usec) -((suseconds_t)before_now.tv_sec*1000000 + before_now.tv_usec)) > timer;
}

int main() {
	int i, j;
    srand(time(0));
    score = 0;
    int c;
    initscr();
	gettimeofday(&before_now, NULL);
	timeout(1);
	Struct new_shape = Duplicate_block(StructsArray[rand()%7]);
    new_shape.col = rand() % (width_size - new_shape.width + 1);
    new_shape.row = 0;
    Free_block(current);
	current = new_shape;
	if(!Check_block_position(current)){
		game_start = false;
	}
    Print_window();
	while(game_start){
		if ((c = getch()) != ERR) {
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
		gettimeofday(&now, NULL);
		if (check_elapsed_time()) {
			Struct temp = Duplicate_block(current);
			switch('s'){
				case 's':
					temp.row++;
					if(Check_block_position(temp))
						current.row++;
					else {
						for(i = 0; i < current.width ; i++){
							for(j = 0; j < current.width ; j++){
								if(current.array[i][j])
									Table[current.row + i][current.col+j] = current.array[i][j];
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
								for(k = n;k >=1;k--)
									for(l=0;l<width_size;l++)
										Table[k][l]=Table[k-1][l];
								for(l=0;l<width_size;l++)
									Table[k][l]=0;
								timer-=decrease--;
							}
						}
						Struct new_shape = Duplicate_block(StructsArray[rand()%7]);
						new_shape.col = rand()%(width_size-new_shape.width+1);
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
			gettimeofday(&before_now, NULL);
		}
	}
	Free_block(current);
	endwin();
	for(i = 0; i < length_size; i++){
		for(j = 0; j < width_size; j++){
			printf("%c ", Table[i][j] ? '#': '.');
		}
		printf("\n");
	}
	printf("\nGame over!\n");
	printf("\nScore: %d\n", score);
    return 0;
}
