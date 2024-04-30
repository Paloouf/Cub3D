/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayc_utilis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:55:19 by ltressen          #+#    #+#             */
/*   Updated: 2023/10/11 14:06:43 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	math_one(t_cub *cub, int x)
{
	cub->cam[x].camerax = (((double)x * 2) / (double)WIDTH) - 1;
	cub->cam[x].raydirx = cub->dirx + (cub->planex * cub->cam[x].camerax);
	cub->cam[x].raydiry = cub->diry + (cub->planey * cub->cam[x].camerax);
	if (cub->cam[x].raydirx == 0)
		cub->cam[x].d_distx = 50;
	else
		cub->cam[x].d_distx = (1 / cub->cam[x].raydirx)
			* (1 - (2 * (1 / cub->cam[x].raydirx < 0)));
	if (cub->cam[x].raydiry == 0)
		cub->cam[x].d_disty = 50;
	else
		cub->cam[x].d_disty = (1 / cub->cam[x].raydiry)
			* (1 - (2 * (1 / cub->cam[x].raydiry < 0)));
	cub->cam[x].mapx = (int)cub->posx;
	cub->cam[x].mapy = (int)cub->posy;
}

void	math_two(t_cub *cub, int x)
{
	if (cub->cam[x].raydirx < 0)
	{
		cub->cam[x].stepx = -1;
		cub->cam[x].s_distx = (cub->posx - (double)cub->cam[x].mapx)
			* cub->cam[x].d_distx;
	}
	else
	{
		cub->cam[x].stepx = 1;
		cub->cam[x].s_distx = ((double)cub->cam[x].mapx + 1.0 - cub->posx)
			* cub->cam[x].d_distx;
	}
	if (cub->cam[x].raydiry < 0)
	{
		cub->cam[x].stepy = -1;
		cub->cam[x].s_disty = (cub->posy - (double)cub->cam[x].mapy)
			* cub->cam[x].d_disty;
	}
	else
	{
		cub->cam[x].stepy = 1;
		cub->cam[x].s_disty = ((double)cub->cam[x].mapy + 1.0 - cub->posy)
			* cub->cam[x].d_disty;
	}
}

void	dda(t_cub *cub, int x)
{
	while (1)
	{
		if (cub->map[cub->cam[x].mapy][cub->cam[x].mapx] == '1'
			|| cub->map[cub->cam[x].mapy][cub->cam[x].mapx] == 'D')
			break ;
		if (cub->cam[x].s_distx < cub->cam[x].s_disty)
		{
			cub->cam[x].s_distx += cub->cam[x].d_distx;
			cub->cam[x].mapx += cub->cam[x].stepx;
			cub->cam[x].side = 0;
		}
		else
		{
			cub->cam[x].s_disty += cub->cam[x].d_disty;
			cub->cam[x].mapy += cub->cam[x].stepy;
			cub->cam[x].side = 1;
		}
	}
	cub->cam[x].w_num = cub->map[cub->cam[x].mapy][cub->cam[x].mapx];
	if (cub->cam[x].side == 0)
		cub->cam[x].w_dist = cub->cam[x].s_distx - cub->cam[x].d_distx;
	else
		cub->cam[x].w_dist = cub->cam[x].s_disty - cub->cam[x].d_disty;
	cub->cam[x].line_hgt = (int)(HEIGHT / cub->cam[x].w_dist);
	cub->cam[x].draw_start = ((-1 * cub->cam[x].line_hgt) / 2) + (HEIGHT / 2);
}

void	math_draw(t_cub *cub, int x)
{
	if (cub->cam[x].draw_start < 0)
		cub->cam[x].draw_start = 0;
	cub->cam[x].draw_end = (cub->cam[x].line_hgt / 2) + (HEIGHT / 2);
	if (cub->cam[x].draw_end >= HEIGHT)
		cub->cam[x].draw_end = HEIGHT - 1;
	if (cub->cam[x].side == 0)
	{
		cub->cam[x].tex_num = 2 + (cub->cam[x].mapx > cub->posx);
		cub->cam[x].w_x = cub->posy + cub->cam[x].w_dist * cub->cam[x].raydiry;
		if (cub->cam[x].w_num == 'D')
			cub->cam[x].tex_num = 11;
	}
	else
	{
		cub->cam[x].tex_num = 0 + (cub->cam[x].mapy > cub->posy);
		cub->cam[x].w_x = cub->posx + cub->cam[x].w_dist * cub->cam[x].raydirx;
		if (cub->cam[x].w_num == 'D')
			cub->cam[x].tex_num = 11;
	}
	cub->cam[x].w_x -= floor(cub->cam[x].w_x);
	cub->cam[x].tex_x = cub->cam[x].w_x
		* (double)cub->tex[cub->cam[x].tex_num].img_w;
	if (cub->cam[x].side == 0 && cub->cam[x].raydirx > 0)
		cub->cam[x].tex_x = cub->tex[cub->cam[x].tex_num].img_w
			- cub->cam[x].tex_x - 1;
}

void	draw_wall(t_cub *cub, int x, int i)
{
	if (i < cub->cam[x].draw_start)
		pxl_to_img(cub, x, i, ft_color_c(cub, i, x));
	else if (i > cub->cam[x].draw_end)
		pxl_to_img(cub, x, i, ft_color_f(cub, i, x));
	else
	{
		cub->cam[x].tex_y = (int)cub->cam[x].tex_pos
			& (cub->tex[cub->cam[x].tex_num].img_h - 1);
		cub->cam[x].tex_pos += cub->cam[x].step;
		pxl_to_img(cub, x, i,
			cub->tex[cub->cam[x].tex_num].addr[((cub->cam[x].tex_y
					* cub->tex[cub->cam[x].tex_num].img_h))
			+ cub->cam[x].tex_x]);
	}
}
