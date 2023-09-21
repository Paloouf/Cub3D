/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:30:08 by ltressen          #+#    #+#             */
/*   Updated: 2023/09/21 16:00:06 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_all(t_cub *cub)
{
	free(cub->cam);
	free(cub->mlx_ptr);
	free(cub->east);
	free(cub->north);
	free(cub->west);
	free(cub->south);
	free(cub->map);
}

int	mouse_events(int key, t_cub *cub)
{
	if (key)
	{
		printf("mouse key: %d\n", key);
		if (key == 1)
			cub->key.shoot = 1;
		if (key == 3)
			cub->key.aim = 1;
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
	if (key == XK_a)
		cub->key.r_left = 1;
	if (key == XK_s)
		cub->key.back = 1;
	if (key == XK_d)
		cub->key.r_right = 1;
	if (key == XK_q)
		cub->key.s_left = 1;
	if (key == XK_e)
		cub->key.s_right = 1;
	if (key == XK_c)
		cub->key.crouch = 1;
	if (key == 32)
		cub->key.jump = 1;
	if (key == XK_f)
		cub->key.fov = 1;
	return (0);
}

int	key_release(int key, t_cub *cub)
{
	if (key == XK_w)
		cub->key.forward = 0;
	if (key == XK_a)
		cub->key.r_left = 0;
	if (key == XK_s)
		cub->key.back = 0;
	if (key == XK_d)
		cub->key.r_right = 0;
	if (key == XK_q)
		cub->key.s_left = 0;
	if (key == XK_e)
		cub->key.s_right = 0;
	if (key == XK_c)
		cub->key.crouch = 0;
	if (key == XK_space)
		cub->key.jump = 0;
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
