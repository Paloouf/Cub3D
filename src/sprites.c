/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:27:28 by ltressen          #+#    #+#             */
/*   Updated: 2023/10/11 14:12:54 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	sprite_deux(t_cub *cub, int i)
{
	cub->spr[cub->spr_order[i]].spritex = cub->spr[cub->spr_order[i]].x
		- cub->posx;
	cub->spr[cub->spr_order[i]].spritey = cub->spr[cub->spr_order[i]].y
		- cub->posy;
	cub->spr[cub->spr_order[i]].invert = 1.0 / (cub->planex * cub->diry
			- cub->dirx * cub->planey);
	cub->spr[cub->spr_order[i]].transx
		= cub->spr[cub->spr_order[i]].invert * (cub->diry
			* cub->spr[cub->spr_order[i]].spritex - cub->dirx
			* cub->spr[cub->spr_order[i]].spritey);
	cub->spr[cub->spr_order[i]].transy
		= cub->spr[cub->spr_order[i]].invert * ((cub->planey * -1)
			* cub->spr[cub->spr_order[i]].spritex + cub->planex
			* cub->spr[cub->spr_order[i]].spritey);
	cub->spr[cub->spr_order[i]].spr_screenx = (int)((WIDTH / 2)
			* (1 + cub->spr[cub->spr_order[i]].transx
				/ cub->spr[cub->spr_order[i]].transy));
	cub->spr[cub->spr_order[i]].spr_hgt = abs((int)(HEIGHT
				/cub->spr[cub->spr_order[i]].transy));
	cub->spr[cub->spr_order[i]].draw_starty
		= -cub->spr[cub->spr_order[i]].spr_hgt / 2 + HEIGHT / 2;
}

void	sprite_trois(t_cub *cub, int i)
{
	if (cub->spr[cub->spr_order[i]].draw_starty < 0)
		cub->spr[cub->spr_order[i]].draw_starty = 0;
	cub->spr[cub->spr_order[i]].draw_endy
		= cub->spr[cub->spr_order[i]].spr_hgt / 2 + HEIGHT / 2;
	if (cub->spr[cub->spr_order[i]].draw_endy >= HEIGHT)
		cub->spr[cub->spr_order[i]].draw_endy = HEIGHT - 1;
	cub->spr[cub->spr_order[i]].spr_wth = abs((int)(HEIGHT
				/ cub->spr[cub->spr_order[i]].transy));
	cub->spr[cub->spr_order[i]].draw_startx
		= -cub->spr[cub->spr_order[i]].spr_wth / 2
		+ cub->spr[cub->spr_order[i]].spr_screenx;
	if (cub->spr[cub->spr_order[i]].draw_startx < 0)
		cub->spr[cub->spr_order[i]].draw_startx = 0;
	cub->spr[cub->spr_order[i]].draw_endx
		= cub->spr[cub->spr_order[i]].spr_wth / 2
		+ cub->spr[cub->spr_order[i]].spr_screenx;
	if (cub->spr[cub->spr_order[i]].draw_endx >= WIDTH)
		cub->spr[cub->spr_order[i]].draw_endx = WIDTH - 1;
}

void	print_sprite(t_cub *cub, int i, int j, int k)
{
	int	color;

	cub->spr[cub->spr_order[i]].tex_y = ((((k * 256 - HEIGHT
						* 128)
					+ cub->spr
				[cub->spr_order[i]].spr_hgt * 128)
				*cub->tex[cub->spr
			[cub->spr_order[i]].tex].img_h)
			/ cub->spr[cub->spr_order[i]].spr_hgt) / 256;
	color = cub->tex[cub->spr[cub->spr_order[i]].tex].addr
	[((cub->spr[cub->spr_order[i]].tex_y
				* cub->tex[cub->spr
			[cub->spr_order[i]].tex].img_h))
		+ cub->spr[cub->spr_order[i]].tex_x];
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
		j = cub->spr[cub->spr_order[i]].draw_startx;
		while (j < cub->spr[cub->spr_order[i]].draw_endx)
		{
			cub->spr[cub->spr_order[i]].tex_x = (int)(256 * (j
						- (-cub->spr[cub->spr_order[i]].spr_wth / 2
							+ cub->spr[cub->spr_order[i]].spr_screenx))
					* cub->tex[cub->spr[cub->spr_order[i]].tex].img_w
					/ cub->spr[cub->spr_order[i]].spr_wth) / 256;
			if (cub->spr[cub->spr_order[i]].transy > 0 && j > 0 && j < WIDTH
				&& cub->spr[cub->spr_order[i]].transy < cub->cam[j].w_dist)
			{
				k = cub->spr[cub->spr_order[i]].draw_starty;
				while (k < cub->spr[cub->spr_order[i]].draw_endy)
					print_sprite(cub, i, j, k++);
			}
			j++;
		}
	}
}

void	sprite(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < cub->tono)
	{
		cub->spr_order[i] = i;
		cub->spr[i].dist = (((cub->posx - cub->spr[i].x) * (cub->posx
						- cub->spr[i].x)) + ((cub->posy - cub->spr[i].y)
					* (cub->posy - cub->spr[i].y)));
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
