/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:11:02 by ltressen          #+#    #+#             */
/*   Updated: 2023/10/06 12:23:29 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_all(t_cub *cub)
{
	
	cub->east = ft_calloc(1, 1);
	cub->north = ft_calloc(1, 1);
	cub->west = ft_calloc(1, 1);
	cub->south = ft_calloc(1, 1);
	cub->img.image = mlx_new_image(cub->mlx_ptr, WIDTH, HEIGHT);
	cub->img.data_addr = mlx_get_data_addr(cub->img.image,
		&cub->img.bpp, &cub->img.line_len, &cub->img.endian);
	cub->dirX = 0;
	cub->dirY = 0;
	cub->planeX = 0;
	cub->planeY = 0;
	cub->key.forward = 0;
	cub->key.back = 0;
	cub->key.r_left = 0;
	cub->key.r_right = 0;
	cub->key.s_left = 0;
	cub->key.s_right = 0;
	cub->key.crouch = 0;
	cub->key.jump = 0;
	cub->key.shoot = 0;
	cub->key.aim = 0;
	cub->key.fov = 0;
	cub->key.open = 0;
	cub->game = 0;
	cub->gameover = 0;
	cub->menu = 1;
}

int	the_game(t_cub *cub)
{
	int	x;

	x = 0;
	
	move(cub);
	if (cub->img.image)
		mlx_destroy_image(cub->mlx_ptr, cub->img.image);
	cub->img.image = mlx_new_image(cub->mlx_ptr, WIDTH, HEIGHT);
	if (cub->menu == 1)
		menu(cub);
	if (cub->game == 1)
	{
		while (x < WIDTH)
			camera(cub, x++);
		check_sprite(cub);
		sprite(cub);
		minimap(cub);
	}
	if (cub->gameover == 1)
		game_over(cub);
	if (cub->gamewin == 1)
		game_win(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr,
	cub->img.image, 0, 0);
}
int	main(int ac, char **av)
{
	t_cub	cub;
	int	x;

	
	if (ac == 2)
	{
		cub.mlx_ptr = mlx_init();
		cub.win_ptr = mlx_new_window(cub.mlx_ptr, WIDTH, HEIGHT, "CubEZ v0.0");
		init_all(&cub);
		parse(av[1], &cub);
		init_game(&cub);
		cub.cam = malloc(sizeof(t_cam) * WIDTH);
		mlx_hook(cub.win_ptr, 2, 1L << 0, key_events, &cub);
		mlx_hook(cub.win_ptr, 3, 1L << 1, key_release, &cub);
		mlx_loop_hook(cub.mlx_ptr, the_game, &cub);
		mlx_mouse_hook(cub.win_ptr, mouse_keys, &cub);
		mlx_hook(cub.win_ptr, MotionNotify, PointerMotionMask, mouse_events, &cub);
		mlx_hook(cub.win_ptr, 17, 0L, close_cross, &cub);
		mlx_loop(cub.mlx_ptr);
	}
	return (0);
}
