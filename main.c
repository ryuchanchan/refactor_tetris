/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitoda <hitoda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 23:47:35 by rykawamu          #+#    #+#             */
/*   Updated: 2022/08/07 04:03:48 by hitoda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

// #include <libc.h>
// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q tetris");
// }

static void	play_game(t_game *game)
{
	int key;

	while(game->status){
		if ((key = getch()) != ERR)
		{
			if (key == 's' || key == 'd' || key == 'a' || key == 'w')
				key_operate(key, game);
		}
		gettimeofday(&game->now, NULL);
		if (check_time_diff(game))
		{
			key_operate('s', game);
			gettimeofday(&game->previous_time, NULL);
		}
	}
}

int main()
{
	t_game game;

	init_game(&game);
	play_game(&game);
	end_game(&game);
    return 0;
}
