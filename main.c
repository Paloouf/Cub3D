/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:11:02 by ltressen          #+#    #+#             */
/*   Updated: 2023/09/21 14:49:20 by jcasades         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_all(t_cub *cub)
{
	cub->mlx_ptr = mlx_init();
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, WIDTH, HEIGHT, "CubEZ v0.0");
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
	cub->jump = 0;
	cub->crouch = 0;
	cub->fjump = 0;
}

int	the_game(t_cub *cub)
{
	int	x;

	x = 0;
	
	move(cub);
	jump(cub);
	while (x < WIDTH)
		camera(cub, x++);
	minimap(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr,
	cub->img.image, 0, 0);
}
int	main(int ac, char **av)
{
	t_cub	cub;
	int	x;

	
	if (ac == 2)
	{	
		init_all(&cub);
		parse(av[1], &cub);
		init_game(&cub);
		  //img = mlx_xpm_file_to_image(cub.mlx_ptr, cub.north, &img_w, &img_h);
		// mlx_put_image_to_window(cub.mlx_ptr, cub.win_ptr, img, 0, 0);


		cub.cam = malloc(sizeof(t_cam) * WIDTH);
		

	//	mlx_destroy_display(cub.mlx_ptr);
		//free(cub.mlx_ptr);

	//	mlx_mouse_hook(cub.win_ptr, mouse_events, &cub);
		mlx_hook(cub.win_ptr, 2, 1L << 0, key_events, &cub);
		mlx_hook(cub.win_ptr, 3, 1L << 1, key_release, &cub);
		mlx_loop_hook(cub.mlx_ptr, the_game, &cub);
		mlx_hook(cub.win_ptr, 17, 0L, close_cross, &cub);
		mlx_loop(cub.mlx_ptr);
	}
	return (1);
}



