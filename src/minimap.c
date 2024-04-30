/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:31:14 by ltressen          #+#    #+#             */
/*   Updated: 2023/10/11 14:09:00 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_square(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (HEIGHT / 30 + i < ((HEIGHT * 8) / 30))
	{
		j = 0;
		while (HEIGHT / 30 + j < ((HEIGHT * 8) / 30))
		{
			if ((i + j) % 2 == 0)
				pxl_to_img(cub, ((2 * HEIGHT) / 30 + j),
					((2 * HEIGHT) / 30 + i), rgba_to_int(200, 200, 200, 1));
			j++;
		}
		i++;
	}
}

int	draw_player(t_cub *cub)
{
	if (cub->phangle > 315 || cub->phangle < 45)
	{
		draw_north(cub, 0, 0);
		return (1);
	}
	if (cub->phangle > 225)
	{
		draw_west(cub, 0, 0);
		return (1);
	}
	if (cub->phangle > 135)
	{
		draw_south(cub, 0, 0);
		return (1);
	}
	draw_east(cub, 0, 0);
	return (1);
}

void	draw_map(t_cub *cub, int i, int j, int y)
{
	int	x;

	if ((cub->posy + j) - 1 >= 0 && cub->posy + j - 1 <= cub->hgt
		&& cub->posx + i - 1 > 0
		&& cub->posx + i - 1 < ft_strlen(cub->map[(int)(cub->posy + j - 1)]))
	{
		if (cub->map[(int)(cub->posy + j) - 1][(int)(cub->posx + i) - 1] == '1')
		{
			while ((HEIGHT * (3 + j)) / 30 + y != (HEIGHT * (4 + j)) / 30)
			{
				x = 0;
				while ((HEIGHT * (3 + i)) / 30 + x != (HEIGHT * (4 + i)) / 30)
				{
					if ((x + y) % 2 == 0)
						pxl_to_img(cub, (HEIGHT * (4 + i) / 30) + y,
							(HEIGHT * (4 + j)) / 30 + x,
							rgba_to_int(0, 0, 160, 1));
					x++;
				}
				y++;
			}
		}
	}
}

void	minimap(t_cub *cub)
{
	int	i;
	int	j;

	i = -2;
	draw_square(cub);
	while (i < 5)
	{
		j = -2;
		while (j < 5)
		{
			draw_map(cub, i, j, 0);
			j++;
		}
		i++;
	}
	draw_player(cub);
}
