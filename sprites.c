/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:27:28 by ltressen          #+#    #+#             */
/*   Updated: 2023/10/11 13:26:26 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sprite_deux(t_cub *cub, int i)
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
}

void	sprite_trois(t_cub *cub, int i)
{
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
}

void	print_sprite(t_cub *cub, int i, int j, int k)
{
	int	color;

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
}

void	sprite_un(t_cub *cub, int i, int j, int k)
{
	if (cub->spr[cub->spr_order[i]].type == 'C'
		|| cub->spr[cub->spr_order[i]].type == 'B'
		|| cub->spr[cub->spr_order[i]].type == 'V')
	{
		sprite_deux(cub, i);
		sprite_trois(cub, i);
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
					print_sprite(cub, i, j, k++);
			}
			j++;
		}
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
		sprite_un(cub, i, 0, 0);
		i++;
	}
}
