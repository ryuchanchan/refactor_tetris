#include "tetris.h"

char Table[length_size][width_size] = {0};
int score = 0;
char game_start = true;
suseconds_t timer = 400000;
int decrease = 1000;

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

int main() {
	t_game game;

	init_game(&game);

	int i, j;
	int c;
	while(game.status){
		if ((c = getch()) != ERR)
			operate(c, &game);
		gettimeofday(&game.now, NULL);
		if (check_elapsed_time(&game)) {
			operate('s', &game);
			gettimeofday(&game.before_now, NULL);
		}
	}
	Free_block(current);
	endwin();
	for(i = 0; i < length_size; i++){
		for(j = 0; j < width_size; j++){
			printf("%c ", game.map[i][j] ? '#': '.');
		}
		printf("\n");
	}
	printf("\nGame over!\n");
	printf("\nScore: %d\n", game.score);
    return 0;
}
