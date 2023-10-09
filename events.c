/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:30:08 by ltressen          #+#    #+#             */
/*   Updated: 2023/10/09 13:12:24 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_all(t_cub *cub)
{
	int	i;

	i = -1;
	if (cub->img.image)
		mlx_destroy_image(cub->mlx_ptr, cub->img.image);
	if (cub->map)
	{
		while (cub->map[++i])
			free(cub->map[i]);
		free(cub->map);
	}
	i = 0;
	while (i < 15)
	{
		if (cub->tex[i].img)
			mlx_destroy_image(cub->mlx_ptr, cub->tex[i].img);
		i++;
	}
	if (cub->tex)
		free(cub->tex);
	if (cub->spr_order)
		free(cub->spr_order);
	if (cub->spr)
		free(cub->spr);
	if (cub->cam)
		free(cub->cam);
	if (cub->mlx_ptr)
	{
		mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
		mlx_destroy_display(cub->mlx_ptr);
		free(cub->mlx_ptr);
	}
	free(cub->east);
	free(cub->north);
	free(cub->west);
	free(cub->south);
}
void	parse_reset(t_cub *cub)
{
	int	i;
	int	j;
	int	count_spr;

	j = 0;
	count_spr = 0;
	while (cub->map[j])
	{
		i = 0;
		while (cub->map[j][i])
		{
			if (cub->map[j][i] == 'd')
				cub->map[j][i] = 'D';
			if (cub->map[j][i] == 'C')
			{
				cub->spr[count_spr].x = i + 0.3;
				cub->spr[count_spr].y = j + 0.3;
				cub->spr[count_spr].tex = 10;
				cub->spr[count_spr].transf = 0;
				count_spr++;
			}
			if (cub->map[j][i] == 'B' || cub->map[j][i] == 'V')
				count_spr++;
			i++;
		}
		j++;
	}
}

int	mouse_keys(int key, int x, int y, t_cub *cub)
{
	if (cub->menu == 1)
	{
		if (key == 1 && (x > (WIDTH * 2 / 10) && (x < (WIDTH * 3 / 10))) && (y > HEIGHT * 8 / 10))
		{
			cub->speed = 0.03;
			cub->menu = 0;
			cub->game = 1;
		}
		if (key == 1 && (x > (WIDTH * 9 / 20) && (x < (WIDTH * 11 / 20))) && (y > HEIGHT * 8 / 10))
		{
			cub->speed = 0.04;
			cub->menu = 0;
			cub->game = 1;
		}
		if (key == 1 && (x > (WIDTH * 14 / 20) && (x < (WIDTH * 16 / 20))) && (y > HEIGHT * 8 / 10))
		{
			cub->speed = 0.05;
			cub->menu = 0;
			cub->game = 1;
		}
	}
	if (cub->gameover == 1 || cub->gamewin == 1)
	{
		if (key == 1 && (x > (WIDTH * 2 / 10) && (x < (WIDTH * 4 / 10))) && (y > HEIGHT * 8 / 10))
		{
			cub->menu = 1;
			cub->gameover = 0;
			init_all(cub);
			parse_reset(cub);
			init_game(cub);
		}
		if (key == 1 && (x > (WIDTH * 7 / 10) && (x < (WIDTH * 9 / 10))) && (y > HEIGHT * 8 / 10))
			key_events(XK_Escape, cub);
	}
}
int	mouse_events(int x, int y, t_cub *cub)
{	
	static int	value = 0;

	if (cub->game == 1)
	{
		mlx_mouse_hide(cub->mlx_ptr, cub->win_ptr);
		if (x > WIDTH - 10)
		{
			mlx_mouse_move(cub->mlx_ptr, cub->win_ptr, 10, y);
			x = 10;
			value = 0;
		}
		if (x < 10)
		{
			mlx_mouse_move(cub->mlx_ptr, cub->win_ptr, WIDTH - 10, y);
			value = WIDTH;
			x = WIDTH - 10;
		}
		if (y > HEIGHT - 10)
			mlx_mouse_move(cub->mlx_ptr, cub->win_ptr, x, 10);
		if (y < 10)
			mlx_mouse_move(cub->mlx_ptr, cub->win_ptr, x, HEIGHT - 10);
		if (value == 0)
			value = x;
		else
		{
			cub->phangle -= (value - x) / 3;
			if (cub->phangle <= 0)
				cub->phangle += 360;
			if (cub->phangle > 360)
				cub->phangle -= 360;
			cub->dirX = -1 * -sin(((double)cub->phangle * M_PI) / 180);
			cub->dirY = -1 * cos(((double)cub->phangle * M_PI) / 180);
			cub->planeX = 1 * cos(((double)cub->phangle * M_PI) / 180);
			cub->planeY = 1 * sin(((double)cub->phangle * M_PI) / 180); 
			value = x;
		}
	}
	else
		mlx_mouse_show(cub->mlx_ptr, cub->win_ptr);
}

int	key_events(int key, t_cub *cub)
{
	if (key == XK_Escape)
	{
		free_all(cub);
		exit(0);
	}
	if (key == 65293)	
		cub->valid= 1;
	if (key == XK_w)
		cub->key.forward = 1;
	if (key == XK_q)
		cub->key.r_left = 1;
	if (key == XK_Left)
		cub->key.r_left = 1;
	if (key == XK_Right)
		cub->key.r_right = 1;
	if (key == XK_s)
		cub->key.back = 1;
	if (key == XK_e)
		cub->key.r_right = 1;
	if (key == XK_a)
		cub->key.s_left = 1;
	if (key == XK_d)
		cub->key.s_right = 1;
	if (key == XK_f)
		cub->key.open = 1;	
	return (0);
}

int	key_release(int key, t_cub *cub)
{
	if (key == XK_w)
		cub->key.forward = 0;
	if (key == XK_q)
		cub->key.r_left = 0;
	if (key == XK_Left)
		cub->key.r_left = 0;
	if (key == XK_Right)
		cub->key.r_right = 0;
	if (key == XK_s)
		cub->key.back = 0;
	if (key == XK_e)
		cub->key.r_right = 0;
	if (key == XK_a)
		cub->key.s_left = 0;
	if (key == XK_d)
		cub->key.s_right = 0;
	if (key == XK_f)
		cub->key.open = 0;
	return (0);
}

int	close_cross(t_cub *cub)
{
	free_all(cub);
	exit(EXIT_SUCCESS);
	return (0);
}
