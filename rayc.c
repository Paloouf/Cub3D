/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:18:26 by jcasades          #+#    #+#             */
/*   Updated: 2023/10/03 14:08:51 by jcasades         ###   ########.fr       */
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
		if (cub->map[cub->cam[x].mapY][cub->cam[x].mapX] == '1')// || cub->map[cub->cam[x].mapY][cub->cam[x].mapX] == '2')
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
	cub->cam[x].w_num = cub->map[cub->cam[x].mapY][cub->cam[x].mapX] - 48;
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
	if (cub->cam[x].side == 0)
	{
		cub->cam[x].tex_num = 2 + (cub->cam[x].mapX > cub->posX);
		cub->cam[x].w_X = cub->posY + cub->cam[x].w_dist * cub->cam[x].raydirY;
		//if (cub->cam[x].w_num == 2)
		//	cub->cam[x].tex_num = 11;
	}
	else
	{
		cub->cam[x].tex_num = 0 + (cub->cam[x].mapY > cub->posY);
		cub->cam[x].w_X = cub->posX + cub->cam[x].w_dist * cub->cam[x].raydirX;
		//if (cub->cam[x].w_num == 2)
		//	cub->cam[x].tex_num = 11;
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
	int	x;
	int	y;
	int	color;

	x = 0;
	y = 0;
	cub->valid = 0;
	cub->tex[12].addr = (int *)mlx_get_data_addr(cub->tex[12].img, &cub->tex[12].bpp, &cub->tex[12].line_len, &cub->tex[12].endian);
	cub->tex[13].addr = (int *)mlx_get_data_addr(cub->tex[13].img, &cub->tex[13].bpp, &cub->tex[13].line_len, &cub->tex[13].endian);
	cub->tex[14].addr = (int *)mlx_get_data_addr(cub->tex[14].img, &cub->tex[14].bpp, &cub->tex[14].line_len, &cub->tex[14].endian);
	while (y < (HEIGHT * 8 / 10))
	{
		x = 0;
		while (x < WIDTH)
		{
			color = cub->tex[12].addr[((((int)(x * ((double)cub->tex[12].img_w / WIDTH)))) + (((int)(y * ((double)cub->tex[12].img_h / (HEIGHT * 8 / 10)))) * cub->tex[12].img_w))];
			pxl_to_img(cub, x, y, color);
			x++;
		}
		y++;
	}
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (x > (WIDTH * 2 / 10) && (x < (WIDTH * 4 / 10)))
			{
				color = cub->tex[13].addr[((((int)((x - (WIDTH * 2 / 10)) * ((double)cub->tex[13].img_w / (WIDTH * 2 / 10))))) + (((int)((y - (HEIGHT * 8 / 10)) * ((double)cub->tex[13].img_h / (HEIGHT * 2 / 10)))) * cub->tex[13].img_w))];
				if ((color & 0x00FFFFFF) == 0)
					color = rgba_to_int(255, 255, 255, 1);
			}
			else if (x > (WIDTH * 6 / 10) && (x < (WIDTH * 8 / 10)))
			{
				color = cub->tex[14].addr[((((int)((x - (WIDTH * 2 / 10)) * ((double)cub->tex[14].img_w / (WIDTH * 2 / 10))))) + (((int)((y - (HEIGHT * 8 / 10)) * ((double)cub->tex[14].img_h / (HEIGHT * 2 / 10)))) * cub->tex[14].img_w))];
				if ((color & 0x00FFFFFF) == 0)
					color = rgba_to_int(255, 255, 255, 1);
			}
			else
				color = rgba_to_int(255, 255, 255, 1);
			pxl_to_img(cub, x, y, color);
			x++;
		}
		y++;
	}
	y = 0;
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
		if (cub->spr[i].dist < 3 && cub->spr[i].type == 'C')
			cub->spr[i].transf = 1;
		if (cub->spr[i].dist < 0.5 && cub->spr[i].type == 'C')
		{
			cub->game = 0;
			cub->gameover = 1;
		}
		if (cub->spr[i].transf == 1)
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

void	menu(t_cub *cub)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	y = 0;
	cub->valid = 0;
	cub->tex[12].addr = (int *)mlx_get_data_addr(cub->tex[12].img, &cub->tex[12].bpp, &cub->tex[12].line_len, &cub->tex[12].endian);
	cub->tex[15].addr = (int *)mlx_get_data_addr(cub->tex[15].img, &cub->tex[15].bpp, &cub->tex[15].line_len, &cub->tex[15].endian);
	cub->tex[16].addr = (int *)mlx_get_data_addr(cub->tex[16].img, &cub->tex[16].bpp, &cub->tex[16].line_len, &cub->tex[16].endian);
	cub->tex[17].addr = (int *)mlx_get_data_addr(cub->tex[17].img, &cub->tex[17].bpp, &cub->tex[17].line_len, &cub->tex[17].endian);
	while (y < (HEIGHT * 8 / 10))
	{
		x = 0;
		while (x < WIDTH)
		{
			color = cub->tex[12].addr[((((int)(x * ((double)cub->tex[12].img_w / WIDTH)))) + (((int)(y * ((double)cub->tex[12].img_h / (HEIGHT * 8 / 10)))) * cub->tex[12].img_w))];
			pxl_to_img(cub, x, y, color);
			x++;
		}
		y++;
	}
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (x > (WIDTH * 2 / 10) && (x < (WIDTH * 3 / 10)))
			{
				color = cub->tex[15].addr[((((int)((x - (WIDTH * 2 / 10)) * ((double)cub->tex[15].img_w / (WIDTH * 1 / 10))))) + (((int)((y - (HEIGHT * 8 / 10)) * ((double)cub->tex[15].img_h / (HEIGHT * 2 / 10)))) * cub->tex[15].img_w))];
				if ((color & 0x00FFFFFF) == 0)
					color = rgba_to_int(255, 255, 255, 1);
			}
			else if (x > (WIDTH * 4 / 10) && (x < (WIDTH * 5 / 10)))
			{
				color = cub->tex[16].addr[((((int)((x - (WIDTH * 2 / 10)) * ((double)cub->tex[16].img_w / (WIDTH * 1 / 10))))) + (((int)((y - (HEIGHT * 8 / 10)) * ((double)cub->tex[16].img_h / (HEIGHT * 2 / 10)))) * cub->tex[16].img_w))];
				if ((color & 0x00FFFFFF) == 0)
					color = rgba_to_int(255, 255, 255, 1);
			}
			else if (x > (WIDTH * 6 / 10) && (x < (WIDTH * 7 / 10)))
			{
				color = cub->tex[17].addr[((((int)((x - (WIDTH * 2 / 10)) * ((double)cub->tex[17].img_w / (WIDTH * 1 / 10))))) + (((int)((y - (HEIGHT * 8 / 10)) * ((double)cub->tex[17].img_h / (HEIGHT * 2 / 10)))) * cub->tex[17].img_w))];
				if ((color & 0x00FFFFFF) == 0)
					color = rgba_to_int(255, 255, 255, 1);
			}
			else
				color = rgba_to_int(255, 255, 255, 1);
			pxl_to_img(cub, x, y, color);
			x++;
		}
		y++;
	}
	y = 0;
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
		if (cub->spr[cub->spr_order[i]].type == 'C' || cub->spr[cub->spr_order[i]].type == 'B')
		{
			cub->spr[cub->spr_order[i]].spriteX = cub->spr[cub->spr_order[i]].x - cub->posX;
			cub->spr[cub->spr_order[i]].spriteY = cub->spr[cub->spr_order[i]].y - cub->posY;
			cub->spr[cub->spr_order[i]].invert = 1.0 / (cub->planeX * cub->dirY - cub->dirX * cub->planeY);
			cub->spr[cub->spr_order[i]].transX = cub->spr[cub->spr_order[i]].invert * (cub->dirY * cub->spr[cub->spr_order[i]].spriteX - cub->dirX * cub->spr[cub->spr_order[i]].spriteY);
			cub->spr[cub->spr_order[i]].transY = cub->spr[cub->spr_order[i]].invert * ((cub->planeY*-1) * cub->spr[cub->spr_order[i]].spriteX + cub->planeX * cub->spr[cub->spr_order[i]].spriteY);
			cub->spr[cub->spr_order[i]].spr_screenX = (int)((WIDTH/2) * (1 + cub->spr[cub->spr_order[i]].transX / cub->spr[cub->spr_order[i]].transY));
			cub->spr[cub->spr_order[i]].spr_hgt = abs((int)(HEIGHT/cub->spr[cub->spr_order[i]].transY));
			cub->spr[cub->spr_order[i]].draw_startY = -cub->spr[cub->spr_order[i]].spr_hgt / 2 + HEIGHT / 2;
			if (cub->spr[cub->spr_order[i]].draw_startY < 0)
				cub->spr[cub->spr_order[i]].draw_startY = 0;
			cub->spr[cub->spr_order[i]].draw_endY = cub->spr[cub->spr_order[i]].spr_hgt / 2 + HEIGHT / 2;
			if (cub->spr[cub->spr_order[i]].draw_endY >= HEIGHT)
				cub->spr[cub->spr_order[i]].draw_endY = HEIGHT - 1;
			cub->spr[cub->spr_order[i]].spr_wth = abs((int)(HEIGHT/cub->spr[cub->spr_order[i]].transY));
			cub->spr[cub->spr_order[i]].draw_startX = -cub->spr[cub->spr_order[i]].spr_wth / 2 + cub->spr[cub->spr_order[i]].spr_screenX;
			if (cub->spr[cub->spr_order[i]].draw_startX < 0)
				cub->spr[cub->spr_order[i]].draw_startX = 0;
			cub->spr[cub->spr_order[i]].draw_endX = cub->spr[cub->spr_order[i]].spr_wth / 2 + cub->spr[cub->spr_order[i]].spr_screenX;
			if (cub->spr[cub->spr_order[i]].draw_endX >= WIDTH)
				cub->spr[cub->spr_order[i]].draw_endX = WIDTH - 1;
			j = cub->spr[cub->spr_order[i]].draw_startX;
			while (j < cub->spr[cub->spr_order[i]].draw_endX)
			{
				cub->spr[cub->spr_order[i]].tex_X = (int)(256 * (j - (-cub->spr[cub->spr_order[i]].spr_wth / 2 + cub->spr[cub->spr_order[i]].spr_screenX)) * cub->tex[cub->spr[cub->spr_order[i]].tex].img_w / cub->spr[cub->spr_order[i]].spr_wth) / 256;
				if (cub->spr[cub->spr_order[i]].transY > 0 && j > 0 && j < WIDTH && cub->spr[cub->spr_order[i]].transY < cub->cam[j].w_dist)
				{
					k = cub->spr[cub->spr_order[i]].draw_startY;
					
					while (k < cub->spr[cub->spr_order[i]].draw_endY)
					{
						cub->spr[cub->spr_order[i]].tex_Y = ((((k * 256 - HEIGHT * 128) + cub->spr[cub->spr_order[i]].spr_hgt * 128) * cub->tex[cub->spr[cub->spr_order[i]].tex].img_h) / cub->spr[cub->spr_order[i]].spr_hgt) /256;
						color = cub->tex[cub->spr[cub->spr_order[i]].tex].addr[((cub->spr[cub->spr_order[i]].tex_Y * cub->tex[cub->spr[cub->spr_order[i]].tex].img_h)) + cub->spr[cub->spr_order[i]].tex_X];
						if ((color & 0x00FFFFFF) != 0)
							pxl_to_img(cub, j, k, color);
						k++;
					}
				}
				j++;
			}
		}
		if (cub->spr[cub->spr_order[i]].type == 'V' || cub->spr[cub->spr_order[i]].type == 'H')
		{
			cub->spr[cub->spr_order[i]].spr_hgt = (int)(HEIGHT / cub->spr[cub->spr_order[i]].dist);
			cub->spr[cub->spr_order[i]].draw_startX = WIDTH /2;//((-1 * cub->spr[cub->spr_order[i]].spr_hgt) / 2) + (HEIGHT / 2);
		//draw start et draw end
		if (cub->spr[cub->spr_order[i]].draw_startX < 0)
			cub->spr[cub->spr_order[i]].draw_startX = 0;
		cub->spr[cub->spr_order[i]].draw_end = (cub->spr[cub->spr_order[i]].line_height / 2) + (HEIGHT / 2);
		if (cub->spr[cub->spr_order[i]].draw_end >= HEIGHT)
			cub->spr[cub->spr_order[i]].draw_end = HEIGHT - 1;
		if (cub->spr[cub->spr_order[i]].side == 0)
		{
			cub->spr[cub->spr_order[i]].tex_num = 2 + (cub->spr[cub->spr_order[i]].mapX > cub->posX);
			cub->spr[cub->spr_order[i]].w_X = cub->posY + cub->spr[cub->spr_order[i]].w_dist * cub->spr[cub->spr_order[i]].raydirY;
			//if (cub->spr[cub->spr_order[i]].w_num == 2)
			//	cub->spr[cub->spr_order[i]].tex_num = 11;
		}
		else
		{
			cub->spr[cub->spr_order[i]].tex_num = 0 + (cub->spr[cub->spr_order[i]].mapY > cub->posY);
			cub->spr[cub->spr_order[i]].w_X = cub->posX + cub->spr[cub->spr_order[i]].w_dist * cub->spr[cub->spr_order[i]].raydirX;
			//if (cub->spr[cub->spr_order[i]].w_num == 2)
			//	cub->spr[cub->spr_order[i]].tex_num = 11;
		}
		cub->spr[cub->spr_order[i]].w_X -= floor(cub->spr[cub->spr_order[i]].w_X);
		cub->spr[cub->spr_order[i]].tex_X = cub->spr[cub->spr_order[i]].w_X * (double)cub->tex[cub->spr[cub->spr_order[i]].tex_num].img_w;
		if (cub->spr[cub->spr_order[i]].side == 0 && cub->spr[cub->spr_order[i]].raydirX > 0)
			cub->spr[cub->spr_order[i]].tex_X = cub->tex[cub->spr[cub->spr_order[i]].tex_num].img_w - cub->spr[cub->spr_order[i]].tex_X - 1;
		if (cub->spr[cub->spr_order[i]].side == 1 && cub->spr[cub->spr_order[i]].raydirY < 0)
			cub->spr[cub->spr_order[i]].tex_X = cub->tex[cub->spr[cub->spr_order[i]].tex_num].img_w - cub->spr[cub->spr_order[i]].tex_X - 1;
		cub->spr[cub->spr_order[i]].step = 1.0 * cub->tex[cub->spr[cub->spr_order[i]].tex_num].img_h / cub->spr[cub->spr_order[i]].line_height;
		cub->spr[cub->spr_order[i]].tex_pos = (cub->spr[cub->spr_order[i]].draw_start - (HEIGHT / 2) + (cub->spr[cub->spr_order[i]].line_height / 2)) * cub->spr[cub->spr_order[i]].step;
		i = 0;
		while (i < HEIGHT)
		{
			if (i < cub->spr[cub->spr_order[i]].draw_start)
				pxl_to_img(cub, x, i, ft_color_c(cub, i, x));
			else if (i > cub->spr[cub->spr_order[i]].draw_end)
				pxl_to_img(cub, x, i, ft_color_f(cub, i, x));
			else
			{
				cub->spr[cub->spr_order[i]].tex_Y = (int)cub->spr[cub->spr_order[i]].tex_pos & (cub->tex[cub->spr[cub->spr_order[i]].tex_num].img_h - 1);
				cub->spr[cub->spr_order[i]].tex_pos += cub->spr[cub->spr_order[i]].step;
				pxl_to_img(cub, x, i, cub->tex[cub->spr[cub->spr_order[i]].tex_num].addr[((cub->spr[cub->spr_order[i]].tex_Y * cub->tex[cub->spr[cub->spr_order[i]].tex_num].img_h)) + cub->spr[cub->spr_order[i]].tex_X]);
			}
			i++;
		}
		}
		i++;
	}
}
