/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:11:02 by ltressen          #+#    #+#             */
/*   Updated: 2023/08/30 15:52:47 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_events(int key, t_cub *cub)
{
	if (key == XK_Escape)
	{
		exit(0);
	}
	return (0);
}

int	close_cross(t_cub *cub)
{
	//free_all(cub);
	exit(EXIT_SUCCESS);
	return (0);
}

int	main(int ac, char **av)
{
	t_cub	cub;

	if (ac == 1)
	{
		cub.mlx_ptr = mlx_init();
		cub.win_ptr = mlx_new_window(cub.mlx_ptr, WIDTH, HEIGHT, "CubEZ v0.0");
		mlx_key_hook(cub.win_ptr, key_events, &cub);
		mlx_hook(cub.win_ptr, 17, 0L, close_cross, &cub);
		mlx_loop(cub.mlx_ptr);
		mlx_destroy_display(cub.mlx_ptr);
		free(cub.mlx_ptr);
	}
	return (1);
}
