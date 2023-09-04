/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:31:14 by ltressen          #+#    #+#             */
/*   Updated: 2023/09/04 18:04:36 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_cub *cub, int color, float i, float j)
{
	int	k;
	int	l;

	k = i;
	while (k < i * 2)
	{
		l = j;
		while (l < (j * 2))
			pxl_to_img(cub, l++, k, color);
		++k;
	}
}

void	render_walls(t_cub *cub, int color, float i, float j)
{
	int 	y;
	int	x;

	y = 0;
	x = 0;
	while (cub->map[y])
	{
		while (cub->map[y][x])
		{
			if (cub->map[y][x] == '1')
			{
				draw_square(cub, color, i, j);
				i += i;
			}
			j += j;
			x++;
		}
		y++;
	}
}
void	render_player(t_cub *cub, int color, float i, float j)
{
	int	k;
	int	l;

	k = i * 4.5;
	
	while (k < i * 5.5)
	{
		l = j * 4.5;
		while(l < j * 5.5)
		{
			pxl_to_img(cub, l++, k, color);
		}
		k++;
	}
}

void	render_background(t_cub *cub, int color)
{
	float	i; //unite de hauteur
	float	j; //unite de longueur

	i = HEIGHT / 40;
	while (i < (HEIGHT / 40) * 9)
	{
		j = WIDTH / 71.1111111111111;
		while (j < (WIDTH / 71.1111111111111) * 9)
		{
			pxl_to_img(cub, j++, i, color);
		}
		++i;
	}
	i = HEIGHT / 40;
	j = WIDTH / 71.1111111111111;
	render_player(cub, rgba_to_int(220, 9, 9, 0.9), i, j);
	//render_walls(cub, rgba_to_int(53, 48, 220, 0.9), i, j);
}



void	minimap(t_cub *cub)
{
	render_background(cub, rgba_to_int(53, 48, 220, 0.5));
	
}
