/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:31:14 by ltressen          #+#    #+#             */
/*   Updated: 2023/09/21 14:59:40 by jcasades         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_cub *cub)
{
	int	x;
	int	y;
	int	pyt;
	int	lx;
	int	ly;

	y = 0;
	while ((HEIGHT * 3) / 10 + y != (HEIGHT * 4) / 10)
	{
		while ((HEIGHT * 3) / 10 + x != (HEIGHT * 4) / 10)
		{

			if (pyt < HEIGHT / 20)
		}
	}
}

void	draw_map(t_cub *cub, int i, int j)
{
	int	x;
	int	y;
	
	y = 0;
	if ((int)cub->posX + i < ft_strlen((cub->map[(int)(cub->posY + j) - 1])))
	{	
		if (cub->map[(int)(cub->posY + j) - 1][(int)(cub->posX + i) - 1] == '1')
		{
			while((HEIGHT * (3 + i)) / 10 + y != (HEIGHT * (4 + i)) / 10)
			{
				x = 0;
				while((HEIGHT * (3 + j)) / 10 + x != (HEIGHT * (4 + j)) / 10)
				{
					pxl_to_img(cub,(((HEIGHT * (3 + j)) / 10 + x)), ((HEIGHT * (3 + i) / 10) + y), rgba_to_int(0, 0, 160, 2));
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

	while (i < 3)
	{
		j = -2;
		while (j < 3)
		{	
			ft_printf("%d\n", j);
			draw_map(cub, i, j);
			j++;
		}
 		i++;
	}
	draw_player(cub);
}	
