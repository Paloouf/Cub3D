/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:11:02 by ltressen          #+#    #+#             */
/*   Updated: 2023/10/12 14:59:42 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_all(t_cub *cub, int flag)
{
	if (flag == 1)
	{
		cub->east = ft_calloc(1, 1);
		cub->north = ft_calloc(1, 1);
		cub->west = ft_calloc(1, 1);
		cub->south = ft_calloc(1, 1);
	}
	cub->img.image = mlx_new_image(cub->mlx_ptr, WIDTH, HEIGHT);
	cub->img.data_addr = mlx_get_data_addr(cub->img.image,
			&cub->img.bpp, &cub->img.line_len, &cub->img.endian);
	cub->dirx = 0;
	cub->diry = 0;
	cub->planex = 0;
	cub->planey = 0;
	cub->key.forward = 0;
	cub->key.back = 0;
	cub->key.r_left = 0;
	cub->key.r_right = 0;
	cub->key.s_left = 0;
	cub->key.s_right = 0;
	cub->key.open = 0;
	cub->game = 0;
	cub->gameover = 0;
	cub->gamewin = 0;
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
	return (0);
}

void	parse_suite(char *argv, t_cub *cub, int file, int error)
{
	char	*line;
	int		i;

	i = 0;
	file = open(argv, O_RDONLY);
	line = get_next_line(file);
	while (line && line[0] != '1' && line[0] != '0' && line[0] != ' ')
	{
		free(line);
		line = get_next_line(file);
	}
	i = 0;
	while (line)
	{
		add_barrel(cub, i, line);
		cub->map[i] = ft_strdup(line);
		cub->mapcpy[i] = ft_strdup(line);
		free(line);
		line = get_next_line(file);
		i++;
	}
	if (error > 0)
		free_all(cub);
}

int	main(int ac, char **av)
{
	t_cub	cub;
	int		fd;

	if (ac == 2 && WIDTH > 500 && HEIGHT > 500)
	{
		cub.mlx_ptr = mlx_init();
		cub.win_ptr = mlx_new_window(cub.mlx_ptr, WIDTH, HEIGHT, "CubEZ v0.0");
		cub.cam = malloc(sizeof(t_cam) * WIDTH);
		init_all(&cub, 1);
		fd = open(av[1], O_RDONLY);
		if (fd < 0)
			return (ft_error("Error: Cannot Open Map file\n"));
		parse(av[1], &cub, fd, 0);
		init_game(&cub);
		get_img_addr(&cub);
		mlx_hook(cub.win_ptr, 2, 1L << 0, key_events, &cub);
		mlx_hook(cub.win_ptr, 3, 1L << 1, key_release, &cub);
		mlx_mouse_hook(cub.win_ptr, mouse_keys, &cub);
		mlx_hook(cub.win_ptr, MotionNotify,
			PointerMotionMask, mouse_events, &cub);
		mlx_loop_hook(cub.mlx_ptr, the_game, &cub);
		mlx_hook(cub.win_ptr, 17, 0L, close_cross, &cub);
		mlx_loop(cub.mlx_ptr);
	}
	return (0);
}
