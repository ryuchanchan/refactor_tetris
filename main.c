/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitoda <hitoda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 23:47:35 by rykawamu          #+#    #+#             */
/*   Updated: 2022/08/07 01:41:03 by hitoda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

int main() {
	t_game game;
	t_block *current;
	int c;

	init_game(&game, current);
	while(game.status){
		if ((c = getch()) != ERR)
			operate(c, &game, current);
		gettimeofday(&game.now, NULL);
		if (check_time_diff(&game)) {
			operate('s', &game, current);
			gettimeofday(&game.previous_time, NULL);
		}
	}
	end_game(&game, current);
	
    return 0;
}
