/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:30:08 by ltressen          #+#    #+#             */
/*   Updated: 2023/09/22 15:27:28 by ltressen         ###   ########.fr       */
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
	while (i < 4)
	{
		mlx_destroy_image(cub->mlx_ptr, cub->tex[i].img);
		i++;
	}
	free(cub->tex);
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

int	mouse_events(int key, t_cub *cub)
{
	static int	value = 0;
	int	res;

//	printf("%d\n", cub);
	printf("eeee\n");
	res = cub->phangle;
	printf("fffff\n");
	if (value == 0)
	{
		
		value = key;
		//printf("%d\n", cub->phangle);
	}
	else
	{
		printf("guh\n");
		res += value - key;
		if (res <= 0)
			res += 360;
		if (res > 360)
			res -= 360;
		cub->dirX = -1 * -sin(((double)res * M_PI) / 180);
	      	cub->dirY = -1 * cos(((double)res * M_PI) / 180);
		cub->planeX = 1 * cos(((double)res * M_PI) / 180);
		cub->planeY = 1 * sin(((double)res * M_PI) / 180);
		value = key;
	}
	printf("ici lol\n");
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
