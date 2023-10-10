/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:31:14 by ltressen          #+#    #+#             */
/*   Updated: 2023/10/10 12:42:58 by jcasades         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
				pxl_to_img(cub, ((2 * HEIGHT) / 30 + j), ((2 * HEIGHT) / 30 + i), rgba_to_int(200, 200, 200, 1));
			j++;
		}
		i++;
	}
}

int	draw_player(t_cub *cub)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	if (cub->phangle > 315 || cub->phangle < 45)
	{
		while (j < (HEIGHT)/ 30)
		{
			i = 0;
			while (i < (HEIGHT)/ 30)
			{
				if (!(i <= ((HEIGHT)/ 60) - j || i >= ((HEIGHT)/ 60) + j))
					pxl_to_img(cub,((HEIGHT * 5 / 30) + i), ((HEIGHT * 5) / 30) + j, rgba_to_int(160, 0, 0, 1));
				i++;
			}
			j++;
		}
		return (1);
	}
	if (cub->phangle > 225)
	{
		while (i < (HEIGHT)/ 30)
		{
			j = 0;
			while (j < (HEIGHT)/ 30)
			{
				if (!(i <= ((HEIGHT)/ 60) - j || i >= ((HEIGHT)/ 60) + j))
					pxl_to_img(cub,((HEIGHT * 5 / 30) + j), ((HEIGHT * 5) / 30) + i, rgba_to_int(160, 0, 0, 1));
				j++;
			}
			i++;
		}
		return (1);
	}
	if (cub->phangle > 135)
	{
		while (j < (HEIGHT)/ 30)
		{
			i = 0;
			while (i < (HEIGHT)/ 30)
			{
				if (!(i <= ((HEIGHT)/ 60) - j || i >= ((HEIGHT)/ 60) + j))
					pxl_to_img(cub,((HEIGHT * 5 / 30) + i), ((HEIGHT * 5) / 30) + ((HEIGHT / 30) - j), rgba_to_int(160, 0, 0, 1));
				i++;
			}
			j++;
		}
		return (1);
	}
	while (i < (HEIGHT)/ 30)
	{
		j = 0;
		while (j < (HEIGHT)/ 30)
		{
			if (!(i <= ((HEIGHT)/ 60) - j || i >= ((HEIGHT)/ 60) + j))
				pxl_to_img(cub,((HEIGHT * 5 / 30) + ((HEIGHT / 30) - j)), ((HEIGHT * 5) / 30) + ((HEIGHT / 30) - i), rgba_to_int(160, 0, 0, 1));
			j++;
		}
		i++;
	}
	return (1);
}

void	draw_map(t_cub *cub, int i, int j)
{
	int	x;
	int	y;
	
	y = 0;
	if (cub->map[(int)(cub->posY + j) - 1] && j + cub->posY >= 1 && (int)cub->posX + i < ft_strlen((cub->map[(int)(cub->posY + j) - 1])))
	{	
		if (cub->map[(int)(cub->posY + j) - 1] && cub->map[(int)(cub->posY + j) - 1][(int)(cub->posX + i) - 1] == '1')
		{
			while((HEIGHT * (3 + j)) / 30 + y != (HEIGHT * (4 + j)) / 30)
			{
				x = 0;
				while((HEIGHT * (3 + i)) / 30 + x != (HEIGHT * (4 + i)) / 30)
				{
					if ((x + y) % 2 == 0)
						pxl_to_img(cub,(HEIGHT * (4 + i) / 30) + y, (HEIGHT * (4 + j)) / 30 + x, rgba_to_int(0, 0, 160, 1));
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
			draw_map(cub, i, j);
			j++;
		}
 		i++;
	}
	draw_player(cub);
}	
