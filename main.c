/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:11:02 by ltressen          #+#    #+#             */
/*   Updated: 2023/09/12 14:23:12 by ltressen         ###   ########.fr       */
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
	cub->ceiling = ft_calloc(1, 1);
	cub->floor = ft_calloc(1, 1);
	cub->img.image = mlx_new_image(cub->mlx_ptr, WIDTH, HEIGHT);
	cub->img.data_addr = mlx_get_data_addr(cub->img.image,
		&cub->img.bpp, &cub->img.line_len, &cub->img.endian);
	cub->dirX = 0;
	cub->dirY = 0;
	cub->planeX = 0;
	cub->planeY = 0;
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
		// img = mlx_xpm_file_to_image(cub.mlx_ptr, path, &img_w, &img_h);
		//minimap(&cub);
		cub.cam = malloc(sizeof(t_cam) * WIDTH);
		mlx_put_image_to_window(cub.mlx_ptr, cub.win_ptr,
		cub.img.image, 0, 0);

	//	mlx_destroy_display(cub.mlx_ptr);
		//free(cub.mlx_ptr);
		x = 0;
		while (x < WIDTH)
			camera(&cub, x++);
		mlx_key_hook(cub.win_ptr, key_events, &cub);
		mlx_hook(cub.win_ptr, 17, 0L, close_cross, &cub);
		mlx_loop(cub.mlx_ptr);
	}
	return (1);
}



