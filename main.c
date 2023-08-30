/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:11:02 by ltressen          #+#    #+#             */
/*   Updated: 2023/08/30 17:04:53 by ltressen         ###   ########.fr       */
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
	
	// void	*img;
	// char 	*path = "./textures/wall.xpm";
	// int	img_w;
	// int	img_h;
	
	if (ac == 1)
	{
		cub.mlx_ptr = mlx_init();
		cub.win_ptr = mlx_new_window(cub.mlx_ptr, WIDTH, HEIGHT, "CubEZ v0.0");
		// img = mlx_xpm_file_to_image(cub.mlx_ptr, path, &img_w, &img_h);
		minimap(&cub);
		//mlx_put_image_to_window(cub.mlx_ptr, cub.win_ptr,
		//cub.img.data_addr, 0, 0);
		mlx_key_hook(cub.win_ptr, key_events, &cub);
		mlx_hook(cub.win_ptr, 17, 0L, close_cross, &cub);
		mlx_loop(cub.mlx_ptr);
		mlx_destroy_display(cub.mlx_ptr);
		free(cub.mlx_ptr);
	}
	return (1);
}

void	pxl_to_img(t_cub *cub, int x, int y, unsigned int color)
{
	char	*pixel;
	int		i;

	i = cub->img.bpp - 8;
	pixel = cub->img.data_addr
		+ (y * cub->img.line_len + x * (cub->img.bpp / 8));
	while (i >= 0)
	{
		if (cub->img.endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (cub->img.bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void	render_background(t_cub *cub, int color)
{
    int	i;
    int	j;

    i = 0;
    while (i < HEIGHT / 10)
    {
        j = 0;
        while (j < WIDTH / 10)
        {
            pxl_to_img(cub, j++, i, color);
        }
        ++i;
    }
}

void	minimap(t_cub *cub)
{
	render_background(cub, MNMP_BACKGROUND);
}
