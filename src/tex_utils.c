/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:36:53 by ltressen          #+#    #+#             */
/*   Updated: 2023/10/11 13:03:53 by jcasades         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	fill_tex_utils(t_cub *cub)
{
	cub->tex[0].img = mlx_xpm_file_to_image(cub->mlx_ptr, cub->north,
			&cub->tex[0].img_w, &cub->tex[0].img_h);
	cub->tex[1].img = mlx_xpm_file_to_image(cub->mlx_ptr, cub->south,
			&cub->tex[1].img_w, &cub->tex[1].img_h);
	cub->tex[2].img = mlx_xpm_file_to_image(cub->mlx_ptr, cub->west,
			&cub->tex[2].img_w, &cub->tex[2].img_h);
	cub->tex[3].img = mlx_xpm_file_to_image(cub->mlx_ptr, cub->east,
			&cub->tex[3].img_w, &cub->tex[3].img_h);
	cub->tex[4].img = mlx_xpm_file_to_image(cub->mlx_ptr,
			"./textures/toro1.xpm", &cub->tex[4].img_w, &cub->tex[4].img_h);
	cub->tex[5].img = mlx_xpm_file_to_image(cub->mlx_ptr,
			"./textures/toro2.xpm", &cub->tex[5].img_w, &cub->tex[5].img_h);
	cub->tex[6].img = mlx_xpm_file_to_image(cub->mlx_ptr,
			"./textures/toro3.xpm", &cub->tex[6].img_w, &cub->tex[6].img_h);
	cub->tex[7].img = mlx_xpm_file_to_image(cub->mlx_ptr,
			"./textures/toro4.xpm", &cub->tex[7].img_w, &cub->tex[7].img_h);
	cub->tex[8].img = mlx_xpm_file_to_image(cub->mlx_ptr,
			"./textures/toro5.xpm", &cub->tex[8].img_w, &cub->tex[8].img_h);
	cub->tex[9].img = mlx_xpm_file_to_image(cub->mlx_ptr,
			"./textures/toro6.xpm", &cub->tex[9].img_w, &cub->tex[9].img_h);
	cub->tex[10].img = mlx_xpm_file_to_image(cub->mlx_ptr,
			"./textures/tonneau.xpm", &cub->tex[10].img_w, &cub->tex[10].img_h);
}

int	fill_tex(t_cub *cub, int barrel, int i)
{
	cub->tono = barrel;
	cub->spr_order = malloc(sizeof(int *) * cub->tono);
	cub->map = ft_calloc(i + 1, sizeof(char *));
	cub->mapcpy = ft_calloc(i + 1, sizeof(char *));
	cub->tex = malloc(sizeof(t_tex) * 15);
	cub->spr = malloc(sizeof(t_spr) * barrel + 1);
	fill_tex_utils(cub);
	cub->tex[11].img = mlx_xpm_file_to_image(cub->mlx_ptr,
			"./textures/door.xpm", &cub->tex[11].img_w, &cub->tex[11].img_h);
	cub->tex[12].img = mlx_xpm_file_to_image(cub->mlx_ptr,
			"./textures/menu.xpm", &cub->tex[12].img_w, &cub->tex[12].img_h);
	cub->tex[13].img = mlx_xpm_file_to_image(cub->mlx_ptr,
			"./textures/died.xpm", &cub->tex[13].img_w, &cub->tex[13].img_h);
	cub->tex[14].img = mlx_xpm_file_to_image(cub->mlx_ptr,
			"./textures/escaped.xpm", &cub->tex[14].img_w, &cub->tex[14].img_h);
	i = 0;
	while (i < 15)
	{
		if (!cub->tex[i].img)
			return (ft_error("Error: Invalid Textures\n"));
		cub->tex[i].addr = (int *)mlx_get_data_addr(cub->tex[i].img,
				&cub->tex[i].bpp, &cub->tex[i].line_len, &cub->tex[i].endian);
		i++;
	}
	return (0);
}

void	flood_fill(t_cub *cub, int x, int y)
{
	if (y == -1 || !cub->mapcpy[y] || !cub->mapcpy[y][x])
		return ;
	if (cub->mapcpy[y][x] == '1' || cub->mapcpy[y][x] == 'F')
		return ;
	cub->mapcpy[y][x] = 'F';
	if (cub->map[y][x] == ' ')
		cub->map[y][x] = '0';
	flood_fill(cub, x + 1, y);
	flood_fill(cub, x - 1, y);
	flood_fill(cub, x, y + 1);
	flood_fill(cub, x, y - 1);
}
