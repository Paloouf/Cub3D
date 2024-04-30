/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_icon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:31:08 by jcasades          #+#    #+#             */
/*   Updated: 2023/10/12 14:22:32 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_player(t_cub *cub)
{
	int	i;
	int	j;
	int	flag;

	flag = 0;
	i = -1;
	while (cub->map[++i])
	{
		j = -1;
		while (cub->map[i][++j])
		{
			if (cub->map[i][j] == 'N' || cub->map[i][j] == 'W'
				|| cub->map[i][j] == 'E' || cub->map[i][j] == 'S')
			{
				if (flag == 0)
					flag = 1;
				else
					return (ft_error("Error : Too many players\n"));
			}
		}
	}
	return (0);
}

void	draw_north(t_cub *cub, int i, int j)
{
	while (j < (HEIGHT) / 30)
	{
		i = 0;
		while (i < (HEIGHT) / 30)
		{
			if (!(i <= ((HEIGHT) / 60) - j || i >= ((HEIGHT) / 60) + j))
				pxl_to_img(cub, ((HEIGHT * 5 / 30) + i),
					((HEIGHT * 5) / 30) + j, rgba_to_int(160, 0, 0, 1));
			i++;
		}
		j++;
	}
}

void	draw_west(t_cub *cub, int i, int j)
{
	while (i < (HEIGHT) / 30)
	{
		j = 0;
		while (j < (HEIGHT) / 30)
		{
			if (!(i <= ((HEIGHT) / 60) - j || i >= ((HEIGHT) / 60) + j))
				pxl_to_img(cub, ((HEIGHT * 5 / 30) + j),
					((HEIGHT * 5) / 30) + i, rgba_to_int(160, 0, 0, 1));
			j++;
		}
		i++;
	}
}

void	draw_south(t_cub *cub, int i, int j)
{
	while (j < (HEIGHT) / 30)
	{
		i = 0;
		while (i < (HEIGHT) / 30)
		{
			if (!(i <= ((HEIGHT) / 60) - j || i >= ((HEIGHT) / 60) + j))
				pxl_to_img(cub, ((HEIGHT * 5 / 30) + i),
					((HEIGHT * 5) / 30) + ((HEIGHT / 30) - j),
					rgba_to_int(160, 0, 0, 1));
			i++;
		}
		j++;
	}
}

void	draw_east(t_cub *cub, int i, int j)
{
	while (i < (HEIGHT) / 30)
	{
		j = 0;
		while (j < (HEIGHT) / 30)
		{
			if (!(i <= ((HEIGHT) / 60) - j || i >= ((HEIGHT) / 60) + j))
				pxl_to_img(cub, ((HEIGHT * 5 / 30) + ((HEIGHT / 30) - j)),
					((HEIGHT * 5) / 30) + ((HEIGHT / 30) - i),
					rgba_to_int(160, 0, 0, 1));
			j++;
		}
		i++;
	}
}
