/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcasades <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:18:26 by jcasades          #+#    #+#             */
/*   Updated: 2023/09/04 16:16:35 by jcasades         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_game(t_cub *data)
{
	int	x;
	int	y;
	
	y = 0;
	x = 0;
	while (data->map[y][x])
	{
		if (data->map[y][x] == '\n')
		{
			y++;
			x = 0;
		}
		if (data->map[y][x] == 'N' || data->map[y][x] == 'O' || data->map[y][x] == 'E' || data->map[y][x] == 'W')
			break;
		x++;
	}
	if (!data->map[y][x])
		return(0);
	data->pos = malloc ((sizeof (int *)) * 2);
	data->pos[0] = x;
	data->pos[1] = y;
	data->phangle = 0 + ((90 * (data->map[y][x] == 'E')) + (180 * (data->map[y][x] == 'S')) + (270 * (data->map[y][x] == 'W')));
	data->pvangle = 0;
	//printf("x : %d, y : %d angle %d\n", data->pos[0], data->pos[1], data->phangle);
}
