#include "tetris.h"

int main() {
	t_game game;
	int c;

	init_game(&game);
	while(game.status){
		if ((c = getch()) != ERR)
			operate(c, &game);
		gettimeofday(&game.now, NULL);
		if (check_time_diff(&game)) {
			operate('s', &game);
			gettimeofday(&game.previous_time, NULL);
		}
	}
	end_game(&game);
	
    return 0;
}