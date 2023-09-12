/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:18:26 by jcasades          #+#    #+#             */
/*   Updated: 2023/09/12 14:28:04 by ltressen         ###   ########.fr       */
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
		if (data->map[y][x] == 'N' || data->map[y][x] == 'S' || data->map[y][x] == 'E' || data->map[y][x] == 'W')
			break;
		x++;
	}
	if (!data->map[y][x])
		return(0);
	data->posX = x + 0.5;
	data->posY = y + 0.5;
	data->phangle = 0 + ((90 * (data->map[y][x] == 'E')) + (180 * (data->map[y][x] == 'S')) + (270 * (data->map[y][x] == 'W')));
	data->pvangle = 0;
	data->dirX = (double)(0 + ((data->map[y][x] == 'W') * -1) + ((data->map[y][x] == 'E')));
	data->dirY = (double)(0 + ((data->map[y][x] == 'S') * -1) + ((data->map[y][x] == 'N')));
	data->planeX = (double)(0 + ((data->map[y][x] == 'S') * -1) + ((data->map[y][x] == 'N')));
	data->planeY = (double)(0 + ((data->map[y][x] == 'E') * -1) + ((data->map[y][x] == 'W')));

	printf("x : %d, y : %d dirx %f diry: %f planex :%f planey : %f\n", (int)data->posX, (int)data->posY, data->dirX, data->dirY, data->planeX, data->planeY);
}

void	camera(t_cub *cub, int x)
{
	int	i;

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
	while (1)
	{	
		if (cub->map[cub->cam[x].mapY][cub->cam[x].mapX] == '1')
		{
			//ft_printf("side %d\n", cub->cam[x].side);
			break;
		}
		if (cub->cam[x].s_distX < cub->cam[x].s_distY)
		{
			//ft_printf("ici\n");
			cub->cam[x].s_distX += cub->cam[x].d_distX;
			cub->cam[x].mapX += cub->cam[x].stepX;
			cub->cam[x].side = 0;
		}
		else
		{
			cub->cam[x].s_distY += cub->cam[x].d_distY;
			cub->cam[x].mapY += cub->cam[x].stepY;
			cub->cam[x].side = 1;
		}

	}
	//wall-dist
	//if (cub->cam[x].side == 0)
	//	ft_printf("side %d\n", cub->cam[x].side);
	if (cub->cam[x].side == 0)
		cub->cam[x].w_dist = cub->cam[x].s_distX - cub->cam[x].d_distX;
	else
		cub->cam[x].w_dist = cub->cam[x].s_distY - cub->cam[x].d_distY;
	//line height
	cub->cam[x].line_height = (HEIGHT / cub->cam[x].w_dist);
	cub->cam[x].draw_start = ((-1 * cub->cam[x].line_height) / 2) + (HEIGHT / 2);
	//draw start et draw end
	if (cub->cam[x].draw_start < 0)
		cub->cam[x].draw_start = 0;
	cub->cam[x].draw_end = (cub->cam[x].line_height / 2) + (HEIGHT / 2);
	if (cub->cam[x].draw_end >= HEIGHT)
		cub->cam[x].draw_end = HEIGHT - 1;
	i = 0;
	//ft_printf("start : %d, end : %d\n", cub->cam[x].draw_start, cub->cam[x].draw_end);
	//if (cub->cam[x].w_dist != 360)
	//	ft_printf("wall_dist:%d\n", cub->cam[x].w_dist);
	while (cub->cam[x].draw_start + i != cub->cam[x].draw_end)
	{
		pxl_to_img(cub, x, cub->cam[x].draw_start + i, (rgba_to_int(255, 0, 0, 0.9) / 1 + (cub->cam[x].side == '1')));
		i+= 1 - ((cub->cam[x].draw_start > cub->cam[x].draw_end) * 2);
	}
	

}