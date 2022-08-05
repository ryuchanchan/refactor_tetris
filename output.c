#include "tetris.h"

void	output_tetris(t_game	game)
{
	int i,j;

	for(i = 0; i < MAP_HEIGHT; i++){
	for(j = 0; j < MAP_WIDTH; j++){
		printf("%c ", game.map[i][j] ? '#': '.');
	}
	printf("\n");
	}
	printf("\nGame over!\n");
	printf("\nScore: %d\n", game.score);
}