/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:27:28 by ltressen          #+#    #+#             */
/*   Updated: 2023/10/11 12:28:28 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_sort_sprite(t_cub *cub)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (i < cub->tono)
	{
		j = 0;
		count = 0;
		while (j < cub->tono)
		{
			if (cub->spr[j].dist > cub->spr[i].dist)
				count++;
			j++;
		}
		cub->spr_order[count] = i;
		i++;
	}
}

void	sprite(t_cub *cub)
{
	int	i;
	int	j;
	int	k;
	int	color;

	i = 0;
	while (i < cub->tono)
	{
		cub->spr_order[i] = i;
		cub->spr[i].dist = (((cub->posX - cub->spr[i].x) * (cub->posX
						- cub->spr[i].x)) + ((cub->posY - cub->spr[i].y)
					* (cub->posY - cub->spr[i].y)));
		i++;
	}
	ft_sort_sprite(cub);
	i = 0;
	while (i < cub->tono)
	{
		if (cub->spr[cub->spr_order[i]].type == 'C'
			|| cub->spr[cub->spr_order[i]].type == 'B'
			|| cub->spr[cub->spr_order[i]].type == 'V')
		{
			cub->spr[cub->spr_order[i]].spriteX = cub->spr[cub->spr_order[i]].x
				- cub->posX;
			cub->spr[cub->spr_order[i]].spriteY = cub->spr[cub->spr_order[i]].y
				- cub->posY;
			cub->spr[cub->spr_order[i]].invert = 1.0 / (cub->planeX * cub->dirY
					- cub->dirX * cub->planeY);
			cub->spr[cub->spr_order[i]].transX
				= cub->spr[cub->spr_order[i]].invert * (cub->dirY
					* cub->spr[cub->spr_order[i]].spriteX - cub->dirX
					* cub->spr[cub->spr_order[i]].spriteY);
			cub->spr[cub->spr_order[i]].transY
				= cub->spr[cub->spr_order[i]].invert * ((cub->planeY * -1)
					* cub->spr[cub->spr_order[i]].spriteX + cub->planeX
					* cub->spr[cub->spr_order[i]].spriteY);
			cub->spr[cub->spr_order[i]].spr_screenX = (int)((WIDTH / 2)
					* (1 + cub->spr[cub->spr_order[i]].transX
						/ cub->spr[cub->spr_order[i]].transY));
			cub->spr[cub->spr_order[i]].spr_hgt = abs((int)(HEIGHT
						/cub->spr[cub->spr_order[i]].transY));
			cub->spr[cub->spr_order[i]].draw_startY
				= -cub->spr[cub->spr_order[i]].spr_hgt / 2 + HEIGHT / 2;
			if (cub->spr[cub->spr_order[i]].draw_startY < 0)
				cub->spr[cub->spr_order[i]].draw_startY = 0;
			cub->spr[cub->spr_order[i]].draw_endY
				= cub->spr[cub->spr_order[i]].spr_hgt / 2 + HEIGHT / 2;
			if (cub->spr[cub->spr_order[i]].draw_endY >= HEIGHT)
				cub->spr[cub->spr_order[i]].draw_endY = HEIGHT - 1;
			cub->spr[cub->spr_order[i]].spr_wth = abs((int)(HEIGHT
						/ cub->spr[cub->spr_order[i]].transY));
			cub->spr[cub->spr_order[i]].draw_startX
				= -cub->spr[cub->spr_order[i]].spr_wth / 2
				+ cub->spr[cub->spr_order[i]].spr_screenX;
			if (cub->spr[cub->spr_order[i]].draw_startX < 0)
				cub->spr[cub->spr_order[i]].draw_startX = 0;
			cub->spr[cub->spr_order[i]].draw_endX
				= cub->spr[cub->spr_order[i]].spr_wth / 2
				+ cub->spr[cub->spr_order[i]].spr_screenX;
			if (cub->spr[cub->spr_order[i]].draw_endX >= WIDTH)
				cub->spr[cub->spr_order[i]].draw_endX = WIDTH - 1;
			j = cub->spr[cub->spr_order[i]].draw_startX;
			while (j < cub->spr[cub->spr_order[i]].draw_endX)
			{
				cub->spr[cub->spr_order[i]].tex_X = (int)(256 * (j
							- (-cub->spr[cub->spr_order[i]].spr_wth / 2
								+ cub->spr[cub->spr_order[i]].spr_screenX))
						* cub->tex[cub->spr[cub->spr_order[i]].tex].img_w
						/ cub->spr[cub->spr_order[i]].spr_wth) / 256;
				if (cub->spr[cub->spr_order[i]].transY > 0 && j > 0 && j < WIDTH
					&& cub->spr[cub->spr_order[i]].transY < cub->cam[j].w_dist)
				{
					k = cub->spr[cub->spr_order[i]].draw_startY;
					while (k < cub->spr[cub->spr_order[i]].draw_endY)
					{
						cub->spr[cub->spr_order[i]].tex_Y = ((((k * 256 - HEIGHT
											* 128)
										+ cub->spr
									[cub->spr_order[i]].spr_hgt * 128)
									*cub->tex[cub->spr
								[cub->spr_order[i]].tex].img_h)
								/ cub->spr[cub->spr_order[i]].spr_hgt) / 256;
						color = cub->tex[cub->spr[cub->spr_order[i]].tex].addr
						[((cub->spr[cub->spr_order[i]].tex_Y
									* cub->tex[cub->spr
								[cub->spr_order[i]].tex].img_h))
							+ cub->spr[cub->spr_order[i]].tex_X];
						if ((color & 0x00FFFFFF) != 0)
							pxl_to_img(cub, j, k, color);
						k++;
					}
				}
				j++;
			}
		}
		i++;
	}
}

void	check_sprite(t_cub *cub)
{
	int			i;
	static int	j = 0;
	double		move_x;
	double		move_y;

	i = 0;
	j++;
	move_x = 0;
	move_y = 0;
	if (j == 6)
		j = 0;
	while (i < cub->tono)
	{
		cub->spr[i].dist = (((cub->posX - cub->spr[i].x) * (cub->posX
						- cub->spr[i].x)) + ((cub->posY - cub->spr[i].y)
					* (cub->posY - cub->spr[i].y)));
		if (cub->spr[i].dist < 3 && cub->spr[i].type == 'C')
			cub->spr[i].transf = 1;
		if (cub->spr[i].dist < 0.5 && cub->spr[i].type == 'C')
		{
			cub->game = 0;
			cub->gameover = 1;
		}
		if (cub->spr[i].dist < 0.5 && cub->spr[i].type == 'V')
		{
			cub->game = 0;
			cub->gamewin = 1;
		}
		if (cub->spr[i].type == 'C' && cub->spr[i].transf == 1)
		{
			cub->spr[i].tex = 4 + j;
			move_x = (cub->spr[i].x - cub->posX) / 10;
			if (move_x < cub->speed)
				move_x = -1 * cub->speed;
			if (move_x > 0.05)
				move_x = cub->speed;
			move_y = (cub->spr[i].y - cub->posY) / 10;
			if (move_y < -1 * cub->speed)
				move_y = -1 * cub->speed;
			if (move_y > cub->speed)
				move_y = cub->speed;
			if (cub->map[(int)(cub->spr[i].y - (move_y * 2))]
				[(int)(cub->spr[i].x - (move_x * 2))] != '1'
				&& cub->map[(int)(cub->spr[i].y - (move_y * 2))]
				[(int)(cub->spr[i].x - (move_x * 2))] != 'D')
			{
				cub->spr[i].x -= move_x;
				cub->spr[i].y -= move_y;
			}
			else if (cub->map[(int)(cub->spr[i].y - (move_y * 2))]
				[(int)(cub->spr[i].x)] != '1' && cub->map[(int)(cub->spr[i].y
				- (move_y * 2))][(int)(cub->spr[i].x)] != 'D')
				cub->spr[i].y -= move_y;
			else if (cub->map[(int)(cub->spr[i].y)][(int)(cub->spr[i].x
				- (move_x * 2))] != '1' && cub->map[(int)(cub->spr[i].y)]
				[(int)(cub->spr[i].x - (move_x * 2))] != 'D')
				cub->spr[i].x -= move_x;
		}
		i++;
	}
}
