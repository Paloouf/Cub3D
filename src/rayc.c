/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:18:26 by jcasades          #+#    #+#             */
/*   Updated: 2023/10/11 14:10:58 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_data(t_cub *data, int x, int y)
{
	data->posx = x + 0.5;
	data->posy = y + 0.5;
	data->phangle = 0 + ((90 * (data->map[y][x] == 'E'))
			+ (180 * (data->map[y][x] == 'S'))
			+ (270 * (data->map[y][x] == 'W')));
	data->pvangle = 0;
	data->dirx = (double)(0 + ((data->map[y][x] == 'W') * -1)
			+ ((data->map[y][x] == 'E')));
	data->diry = (double)(0 + ((data->map[y][x] == 'N') * -1)
			+ ((data->map[y][x] == 'S')));
	data->planex = (double)(0 + ((data->map[y][x] == 'S') * -1)
			+ ((data->map[y][x] == 'N')));
	data->planey = (double)(0 + ((data->map[y][x] == 'E') * -1)
			+ ((data->map[y][x] == 'W')));
}

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
		if (data->map[y][x] == 'N' || data->map[y][x] == 'S' || data->map[y][x]
			== 'E' || data->map[y][x] == 'W')
			break ;
		x++;
	}
	if (!data->map[y][x])
		return (0);
	init_data(data, x, y);
	if (check(data) == 1)
		free_all(data);
	return (0);
}

void	get_img_addr(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 15)
	{
		cub->tex[i].addr = (int *)mlx_get_data_addr(cub->tex[i].img,
				&cub->tex[i].bpp, &cub->tex[i].line_len, &cub->tex[i].endian);
		i++;
	}
}

void	camera(t_cub *cub, int x)
{
	int	i;

	math_one(cub, x);
	math_two(cub, x);
	dda(cub, x);
	math_draw(cub, x);
	if (cub->cam[x].side == 1 && cub->cam[x].raydiry < 0)
		cub->cam[x].tex_x = cub->tex[cub->cam[x].tex_num].img_w
			- cub->cam[x].tex_x - 1;
	cub->cam[x].step = 1.0 * cub->tex[cub->cam[x].tex_num].img_h
		/ cub->cam[x].line_hgt;
	cub->cam[x].tex_pos = (cub->cam[x].draw_start - (HEIGHT / 2)
			+ (cub->cam[x].line_hgt / 2)) * cub->cam[x].step;
	i = 0;
	while (i < HEIGHT)
		draw_wall(cub, x, i++);
}
