/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:18:26 by jcasades          #+#    #+#             */
/*   Updated: 2023/09/29 12:36:27 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_game(t_cub *data)
{
	int	x;
	int	y;
	
	y = 0;
	x = 0;
	while (data->map[y][x])
	{
		if (data->map[y][x] == '\n')
		{
			y++;
			x = 0;
		}
		if (data->map[y][x] == 'N' || data->map[y][x] == 'S' || data->map[y][x] == 'E' || data->map[y][x] == 'W')
			break;
		x++;
	}
	if (!data->map[y][x])
		return(0);
	data->posX = x + 0.5;
	data->posY = y + 0.5;
	data->phangle = 0 + ((90 * (data->map[y][x] == 'E')) + (180 * (data->map[y][x] == 'S')) + (270 * (data->map[y][x] == 'W')));
	data->pvangle = 0;
	data->dirX = (double)(0 + ((data->map[y][x] == 'W') * -1) + ((data->map[y][x] == 'E')));
	data->dirY = (double)(0 + ((data->map[y][x] == 'N') * -1) + ((data->map[y][x] == 'S')));
	data->planeX = (double)(0 + ((data->map[y][x] == 'S') * -1) + ((data->map[y][x] == 'N')));
	data->planeY = (double)(0 + ((data->map[y][x] == 'E') * -1) + ((data->map[y][x] == 'W')));
}

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
void	camera(t_cub *cub, int x)
{
	int	i;
	int	j;
	int	k;
	int	color;

	cub->cam[x].cameraX = (((double)x * 2) / (double)WIDTH) - 1;
	cub->cam[x].raydirX = cub->dirX + (cub->planeX * cub->cam[x].cameraX);
	cub->cam[x].raydirY = cub->dirY + (cub->planeY * cub->cam[x].cameraX);
	if (cub->cam[x].raydirX == 0)
		cub->cam[x].d_distX = 50;
	else
		cub->cam[x].d_distX = (1/cub->cam[x].raydirX) * (1 - (2 * (1 / cub->cam[x].raydirX < 0)));
	if (cub->cam[x].raydirY == 0)
		cub->cam[x].d_distY = 50;
	else
		cub->cam[x].d_distY = (1/cub->cam[x].raydirY) * (1 - (2 * (1 / cub->cam[x].raydirY < 0)));
	cub->cam[x].mapX = (int)cub->posX;
	cub->cam[x].mapY = (int)cub->posY;
	
	if (cub->cam[x].raydirX < 0)
	{
		cub->cam[x].stepX = -1;
		cub->cam[x].s_distX = (cub->posX - (double)cub->cam[x].mapX) * cub->cam[x].d_distX;
	}
	else
	{
		cub->cam[x].stepX = 1;
		cub->cam[x].s_distX = ((double)cub->cam[x].mapX + 1.0 - cub->posX) * cub->cam[x].d_distX;
	}
	if (cub->cam[x].raydirY < 0)
	{
		cub->cam[x].stepY = -1;
		cub->cam[x].s_distY = (cub->posY - (double)cub->cam[x].mapY) * cub->cam[x].d_distY;
	}
	else
	{
		cub->cam[x].stepY = 1;
		cub->cam[x].s_distY = ((double)cub->cam[x].mapY + 1.0 - cub->posY) * cub->cam[x].d_distY;
	}
	while (1)
	{	
		if (cub->map[cub->cam[x].mapY][cub->cam[x].mapX] == '1' || cub->map[cub->cam[x].mapY][cub->cam[x].mapX] == '2')
			break;
		if (cub->cam[x].s_distX < cub->cam[x].s_distY)
		{
			cub->cam[x].s_distX += cub->cam[x].d_distX;
			cub->cam[x].mapX += cub->cam[x].stepX;
			cub->cam[x].side = 0;
		}
		else
		{
			cub->cam[x].s_distY += cub->cam[x].d_distY;
			cub->cam[x].mapY += cub->cam[x].stepY;
			cub->cam[x].side = 1;
		}

	}
	//wall-dist
	if (cub->cam[x].side == 0)
		cub->cam[x].w_dist = cub->cam[x].s_distX - cub->cam[x].d_distX;
	else
		cub->cam[x].w_dist = cub->cam[x].s_distY - cub->cam[x].d_distY;
	//line height
	cub->cam[x].line_height = (int)(HEIGHT / cub->cam[x].w_dist);
	cub->cam[x].draw_start = ((-1 * cub->cam[x].line_height) / 2) + (HEIGHT / 2);
	//draw start et draw end
	if (cub->cam[x].draw_start < 0)
		cub->cam[x].draw_start = 0;
	cub->cam[x].draw_end = (cub->cam[x].line_height / 2) + (HEIGHT / 2);
	if (cub->cam[x].draw_end >= HEIGHT)
		cub->cam[x].draw_end = HEIGHT - 1;
	cub->tex[0].addr = (int *)mlx_get_data_addr(cub->tex[0].img, &cub->tex[0].bpp, &cub->tex[0].line_len, &cub->tex[0].endian);
	cub->tex[1].addr = (int *)mlx_get_data_addr(cub->tex[1].img, &cub->tex[1].bpp, &cub->tex[1].line_len, &cub->tex[1].endian);
	cub->tex[2].addr = (int *)mlx_get_data_addr(cub->tex[2].img, &cub->tex[2].bpp, &cub->tex[2].line_len, &cub->tex[2].endian);
	cub->tex[3].addr = (int *)mlx_get_data_addr(cub->tex[3].img, &cub->tex[3].bpp, &cub->tex[3].line_len, &cub->tex[3].endian);
	cub->tex[4].addr = (int *)mlx_get_data_addr(cub->tex[4].img, &cub->tex[4].bpp, &cub->tex[4].line_len, &cub->tex[4].endian);
	cub->tex[5].addr = (int *)mlx_get_data_addr(cub->tex[5].img, &cub->tex[5].bpp, &cub->tex[5].line_len, &cub->tex[5].endian);
	cub->tex[6].addr = (int *)mlx_get_data_addr(cub->tex[6].img, &cub->tex[6].bpp, &cub->tex[6].line_len, &cub->tex[6].endian);
	cub->tex[7].addr = (int *)mlx_get_data_addr(cub->tex[7].img, &cub->tex[7].bpp, &cub->tex[7].line_len, &cub->tex[7].endian);
	cub->tex[8].addr = (int *)mlx_get_data_addr(cub->tex[8].img, &cub->tex[8].bpp, &cub->tex[8].line_len, &cub->tex[8].endian);
	cub->tex[9].addr = (int *)mlx_get_data_addr(cub->tex[9].img, &cub->tex[9].bpp, &cub->tex[9].line_len, &cub->tex[9].endian);
	cub->tex[10].addr = (int *)mlx_get_data_addr(cub->tex[10].img, &cub->tex[10].bpp, &cub->tex[10].line_len, &cub->tex[10].endian);
	cub->tex[11].addr = (int *)mlx_get_data_addr(cub->tex[11].img, &cub->tex[11].bpp, &cub->tex[11].line_len, &cub->tex[11].endian);
	cub->cam[x].w_num = cub->map[cub->cam[x].mapY][cub->cam[x].mapX] - 48;
	if (cub->cam[x].side == 0)
	{
		cub->cam[x].tex_num = 2 + (cub->cam[x].mapX > cub->posX);
		cub->cam[x].w_X = cub->posY + cub->cam[x].w_dist * cub->cam[x].raydirY;
		if (cub->cam[x].w_num == 2)
			cub->cam[x].tex_num = 11;
	}
	else
	{
		cub->cam[x].tex_num = 0 + (cub->cam[x].mapY > cub->posY);
		cub->cam[x].w_X = cub->posX + cub->cam[x].w_dist * cub->cam[x].raydirX;
		if (cub->cam[x].w_num == 2)
			cub->cam[x].tex_num = 11;
	}
	cub->cam[x].w_X -= floor(cub->cam[x].w_X);
	cub->cam[x].tex_X = cub->cam[x].w_X * (double)cub->tex[cub->cam[x].tex_num].img_w;
	if (cub->cam[x].side == 0 && cub->cam[x].raydirX > 0)
		cub->cam[x].tex_X = cub->tex[cub->cam[x].tex_num].img_w - cub->cam[x].tex_X - 1;
	if (cub->cam[x].side == 1 && cub->cam[x].raydirY < 0)
		cub->cam[x].tex_X = cub->tex[cub->cam[x].tex_num].img_w - cub->cam[x].tex_X - 1;
	cub->cam[x].step = 1.0 * cub->tex[cub->cam[x].tex_num].img_h / cub->cam[x].line_height;
	cub->cam[x].tex_pos = (cub->cam[x].draw_start - (HEIGHT / 2) + (cub->cam[x].line_height / 2)) * cub->cam[x].step;
	i = 0;
	while (i < HEIGHT)
	{
		if (i < cub->cam[x].draw_start)
			pxl_to_img(cub, x, i, ft_color_c(cub, i, x));
		else if (i > cub->cam[x].draw_end)
			pxl_to_img(cub, x, i, ft_color_f(cub, i, x));
		else
		{
			cub->cam[x].tex_Y = (int)cub->cam[x].tex_pos & (cub->tex[cub->cam[x].tex_num].img_h - 1);
			cub->cam[x].tex_pos += cub->cam[x].step;
			pxl_to_img(cub, x, i, cub->tex[cub->cam[x].tex_num].addr[((cub->cam[x].tex_Y * cub->tex[cub->cam[x].tex_num].img_h)) + cub->cam[x].tex_X]);
		}
		i++;
	}
}

void	game_over(t_cub *cub)
{
	
	cub->valid = 0;
	cub->tex[12].addr = (int *)mlx_get_data_addr(cub->tex[12].img, &cub->tex[12].bpp, &cub->tex[12].line_len, &cub->tex[12].endian);
	while(cub->valid == 0)
	{
		mlx_key_hook(cub->win_ptr, key_events, cub);
		mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->tex[12].img, WIDTH / 2, HEIGHT /2);
	}
	key_events(XK_Escape, cub);
}

void	check_sprite(t_cub *cub)
{
	int	i;
	static	int j = 0;
	double	move_x;
	double	move_y;
	
	i = 0;
	j++;
	move_x = 0;
	move_y = 0;
	if (j == 6)
		j = 0;
	while (i < cub->tono)
	{
		cub->spr[i].dist = (((cub->posX - cub->spr[i].x) * (cub->posX - cub->spr[i].x)) + ((cub->posY - cub->spr[i].y) * (cub->posY - cub->spr[i].y)));
		if (cub->spr[i].dist < 3)
			cub->spr[i].transf = 1;
		if (cub->spr[i].dist < 0.5)
			game_over(cub);
		if (cub->spr[i].transf == 1)
		{	
			cub->spr[i].tex = 4 + j;
			move_x = (cub->spr[i].x - cub->posX) / 10;
			if (move_x < -0.05)
				move_x = -0.05;
			if (move_x > 0.05)
				move_x = 0.05;
			move_y = (cub->spr[i].y - cub->posY) / 10;
			if (move_y < -0.05)
				move_y = -0.05;
			if (move_y > 0.05)
				move_y = 0.05;
			if (cub->map[(int)(cub->spr[i].y - (move_y * 2))][(int)(cub->spr[i].x - (move_x * 2))] != '1')
			{
				cub->spr[i].x -= move_x;
				cub->spr[i].y -= move_y;
			}
			else if (cub->map[(int)(cub->spr[i].y - (move_y * 2))][(int)(cub->spr[i].x )] != '1')
				cub->spr[i].y -= move_y;
			else if (cub->map[(int)(cub->spr[i].y)][(int)(cub->spr[i].x - (move_x * 2))] != '1')
				cub->spr[i].x -= move_x;
		}	
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
		cub->spr[i].dist = (((cub->posX - cub->spr[i].x) * (cub->posX - cub->spr[i].x)) + ((cub->posY - cub->spr[i].y) * (cub->posY - cub->spr[i].y)));
		i++;
	}
	ft_sort_sprite(cub);
	//function sort_sprite
	i = 0;
	while (i < cub->tono)
	{
		cub->spr[i].spriteX = cub->spr[cub->spr_order[i]].x - cub->posX;
		cub->spr[i].spriteY = cub->spr[cub->spr_order[i]].y - cub->posY;
		cub->spr[i].invert = 1.0 / (cub->planeX * cub->dirY - cub->dirX * cub->planeY);
		cub->spr[i].transX = cub->spr[i].invert * (cub->dirY * cub->spr[i].spriteX - cub->dirX * cub->spr[i].spriteY);
		cub->spr[i].transY = cub->spr[i].invert * ((cub->planeY*-1) * cub->spr[i].spriteX + cub->planeX * cub->spr[i].spriteY);
		cub->spr[i].spr_screenX = (int)((WIDTH/2) * (1 + cub->spr[i].transX / cub->spr[i].transY));
		cub->spr[i].spr_hgt = abs((int)(HEIGHT/cub->spr[i].transY));
		cub->spr[i].draw_startY = -cub->spr[i].spr_hgt / 2 + HEIGHT / 2;
		if (cub->spr[i].draw_startY < 0)
			cub->spr[i].draw_startY = 0;
		cub->spr[i].draw_endY = cub->spr[i].spr_hgt / 2 + HEIGHT / 2;
		if (cub->spr[i].draw_endY >= HEIGHT)
			cub->spr[i].draw_endY = HEIGHT - 1;
		cub->spr[i].spr_wth = abs((int)(HEIGHT/cub->spr[i].transY));
		cub->spr[i].draw_startX = -cub->spr[i].spr_wth / 2 + cub->spr[i].spr_screenX;
		if (cub->spr[i].draw_startX < 0)
			cub->spr[i].draw_startX = 0;
		cub->spr[i].draw_endX = cub->spr[i].spr_wth / 2 + cub->spr[i].spr_screenX;
		if (cub->spr[i].draw_endX >= WIDTH)
			cub->spr[i].draw_endX = WIDTH - 1;
		j = cub->spr[i].draw_startX;
		while (j < cub->spr[i].draw_endX)
		{
			cub->spr[i].tex_X = (int)(256 * (j - (-cub->spr[i].spr_wth / 2 + cub->spr[i].spr_screenX)) * cub->tex[cub->spr[i].tex].img_w / cub->spr[i].spr_wth) / 256;
			if (cub->spr[i].transY > 0 && j > 0 && j < WIDTH && cub->spr[i].transY < cub->cam[j].w_dist)
			{
				k = cub->spr[i].draw_startY;
				
				while (k < cub->spr[i].draw_endY)
				{
					cub->spr[i].tex_Y = ((((k * 256 - HEIGHT * 128) + cub->spr[i].spr_hgt * 128) * cub->tex[cub->spr[i].tex].img_h) / cub->spr[i].spr_hgt) /256;
					color = cub->tex[cub->spr[i].tex].addr[((cub->spr[i].tex_Y * cub->tex[cub->spr[i].tex].img_h)) + cub->spr[i].tex_X];
					if ((color & 0x00FFFFFF) != 0)
						pxl_to_img(cub, j, k, color);
					k++;
				}
			}
			j++;
		}
		i++;
	}
}
