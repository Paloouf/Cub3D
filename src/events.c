/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:30:08 by ltressen          #+#    #+#             */
/*   Updated: 2023/10/11 14:09:38 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	menu_clic(int key, int x, int y, t_cub *cub)
{
	if (key == 1 && (x > (WIDTH * 2 / 10) && (x < (WIDTH * 3 / 10)))
		&& (y > HEIGHT * 8 / 10))
	{
		cub->speed = 0.03;
		cub->menu = 0;
		cub->game = 1;
	}
	if (key == 1 && (x > (WIDTH * 9 / 20) && (x < (WIDTH * 11 / 20)))
		&& (y > HEIGHT * 8 / 10))
	{
		cub->speed = 0.04;
		cub->menu = 0;
		cub->game = 1;
	}
	if (key == 1 && (x > (WIDTH * 14 / 20) && (x < (WIDTH * 16 / 20)))
		&& (y > HEIGHT * 8 / 10))
	{
		cub->speed = 0.05;
		cub->menu = 0;
		cub->game = 1;
	}
}

int	mouse_keys(int key, int x, int y, t_cub *cub)
{
	if (cub->menu == 1)
		menu_clic(key, x, y, cub);
	if (cub->gameover == 1 || cub->gamewin == 1)
	{
		if (key == 1 && (x > (WIDTH * 2 / 10) && (x < (WIDTH * 4 / 10)))
			&& (y > HEIGHT * 8 / 10))
		{
			init_all(cub, 0);
			parse_reset(cub);
			init_game(cub);
		}
		if (key == 1 && (x > (WIDTH * 7 / 10) && (x < (WIDTH * 9 / 10)))
			&& (y > HEIGHT * 8 / 10))
			key_events(XK_Escape, cub);
	}
	return (0);
}

int	mouse_suite(int x, int y, int value, t_cub *cub)
{
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
		cub->dirx = -1 * -sin(((double)cub->phangle * M_PI) / 180);
		cub->diry = -1 * cos(((double)cub->phangle * M_PI) / 180);
		cub->planex = 1 * cos(((double)cub->phangle * M_PI) / 180);
		cub->planey = 1 * sin(((double)cub->phangle * M_PI) / 180);
		value = x;
	}
	return (value);
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
		value = mouse_suite(x, y, value, cub);
	}
	else
		mlx_mouse_show(cub->mlx_ptr, cub->win_ptr);
	return (0);
}
