/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:18:26 by jcasades          #+#    #+#             */
/*   Updated: 2023/09/11 14:45:32 by ltressen         ###   ########.fr       */
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
	data->posX = x - 0.5;
	data->posY = y - 0.5;
	data->phangle = 0 + ((90 * (data->map[y][x] == 'E')) + (180 * (data->map[y][x] == 'S')) + (270 * (data->map[y][x] == 'W')));
	data->pvangle = 0;
	data->dirX = 0 + ((data->map[y][x] == 'W') * -1) + ((data->map[y][x] == 'E'));
	data->dirY = 0 + ((data->map[y][x] == 'S') * -1) + ((data->map[y][x] == 'N'));
	data->planeX = 0 + ((data->map[y][x] == 'S') * -1) + ((data->map[y][x] == 'N'));
	data->planeY = 0 + ((data->map[y][x] == 'E') * -1) + ((data->map[y][x] == 'W'));

	//printf("x : %d, y : %d angle %d\n", data->pos[0], data->pos[1], data->phangle);
}

void	camera(t_cub *cub, int x)
{
	cub->cam[x].cameraX = ((x * 2) / WIDTH) - 1;
	cub->cam[x].raydirX = cub->dirX + cub->planeX * cub->cam[x].cameraX;
	cub->cam[x].raydirY = cub->dirY + cub->planeY * cub->cam[x].cameraX;
	if (cub->cam[x].raydirX == 0)
		cub->cam[x].d_distX = 50;
	else
		cub->cam[x].d_distX = abs(1 / cub->cam[x].raydirX);
	if (cub->cam[x].raydirY == 0)
		cub->cam[x].d_distY = 50;
	else
		cub->cam[x].d_distY = abs(1 / cub->cam[x].raydirY);
	cub->cam[x].mapX = (int)cub->posX;
	cub->cam[x].mapY = (int)cub->posY;
	if (cub->cam[x].raydirX < 0)
	{
		cub->cam[x].stepX = -1;
		cub->cam[x].s_distX = (cub->posX - cub->cam[x].mapX) * cub->cam[x].d_distX;
	}
	else
	{
		cub->cam[x].stepX = 1;
		cub->cam[x].s_distX = (cub->cam[x].mapX + 1.0 - cub->posX) * cub->cam[x].d_distX;
	}
	if (cub->cam[x].raydirY < 0)
	{
		cub->cam[x].stepY = -1;
		cub->cam[x].s_distY = (cub->posY - cub->cam[x].mapY) * cub->cam[x].d_distY;
	}
	else
	{
		cub->cam[x].stepY = 1;
		cub->cam[x].s_distY = (cub->cam[x].mapY + 1.0 - cub->posY) * cub->cam[x].d_distY;
	}

}