/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitoda <hitoda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 01:48:57 by hitoda            #+#    #+#             */
/*   Updated: 2022/08/06 21:38:48 by hitoda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

int check_time_diff(t_game *game)
{
	return ((suseconds_t)(game->now.tv_sec*1000000 + game->now.tv_usec) \
			- ((suseconds_t)game->previous_time.tv_sec*1000000 + game->previous_time.tv_usec)) \
			> game->speed;
}
