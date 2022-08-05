#include "tetris.h"

void	output_tetris(t_game	game)
{
	int i,j;

	for(i = 0; i < length_size; i++){
	for(j = 0; j < width_size; j++){
		printf("%c ", game.map[i][j] ? '#': '.');
	}
	printf("\n");
	}
	printf("\nGame over!\n");
	printf("\nScore: %d\n", game.score);
}