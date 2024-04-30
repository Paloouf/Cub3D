/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:28:46 by ltressen          #+#    #+#             */
/*   Updated: 2023/10/11 13:38:40 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	game_win(t_cub *cub)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	y = 0;
	cub->valid = 0;
	while (y < (HEIGHT))
	{
		x = 0;
		while (x < WIDTH)
		{
			color = cub->tex[14].addr[((((int)(x * ((double)cub->tex[14].img_w
									/ WIDTH)))) + (((int)(y
								* ((double)cub->tex[14].img_h / (HEIGHT))))
						* cub->tex[14].img_w))];
			pxl_to_img(cub, x, y, color);
			x++;
		}
		y++;
	}
}

void	game_over(t_cub *cub)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	y = 0;
	cub->valid = 0;
	while (y < (HEIGHT))
	{
		x = 0;
		while (x < WIDTH)
		{
			color = cub->tex[13].addr[((((int)(x * ((double)cub->tex[13].img_w
									/ WIDTH)))) + (((int)(y
								* ((double)cub->tex[13].img_h / (HEIGHT))))
						* cub->tex[13].img_w))];
			pxl_to_img(cub, x, y, color);
			x++;
		}
		y++;
	}
}

void	menu(t_cub *cub)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	y = 0;
	cub->valid = 0;
	while (y < (HEIGHT))
	{
		x = 0;
		while (x < WIDTH)
		{
			color = cub->tex[12].addr[((((int)(x * ((double)cub->tex[12].img_w
									/ WIDTH)))) + (((int)(y
								* ((double)cub->tex[12].img_h
									/ (HEIGHT)))) * cub->tex[12].img_w))];
			pxl_to_img(cub, x, y, color);
			x++;
		}
		y++;
	}
}
