/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:30:08 by ltressen          #+#    #+#             */
/*   Updated: 2023/09/28 15:25:22 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_all(t_cub *cub)
{
	int	i;

	i = -1;
	if (cub->img.image)
		mlx_destroy_image(cub->mlx_ptr, cub->img.image);
	while (cub->map[++i])
		free(cub->map[i]);
	i = 0;
	while (i < 12)
	{
		mlx_destroy_image(cub->mlx_ptr, cub->tex[i].img);
		i++;
	}
	free(cub->tex);
	free(cub->spr_order);
	free(cub->spr);
	free(cub->map);
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

int	mouse_events(int x, int y, t_cub *cub)
{	
	static int	value = 0;

	mlx_mouse_hide(cub->mlx_ptr, cub->win_ptr);
	if (x > 1910 || x < 10 || y > 1070 || y < 10)
		mlx_mouse_move(cub->mlx_ptr, cub->win_ptr, WIDTH/2, HEIGHT/2);
	if (value == 0)
		value = x;
	else
	{
	 	cub->phangle -= value - x;
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

int	key_events(int key, t_cub *cub)
{
	if (key == XK_Escape)
	{
		free_all(cub);
		exit(0);
	}
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
		cub->key.fov = 1;
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
		cub->key.fov = 0;
	return (0);
}

int	close_cross(t_cub *cub)
{
	free_all(cub);
	exit(EXIT_SUCCESS);
	return (0);
}
