/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:25:39 by ltressen          #+#    #+#             */
/*   Updated: 2023/10/12 15:04:54 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_deux(t_cub *cub)
{
	if (cub->tex)
		free(cub->tex);
	if (cub->spr_order)
		free(cub->spr_order);
	if (cub->spr)
		free(cub->spr);
	if (cub->cam)
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

void	free_all(t_cub *cub)
{
	int	i;

	i = -1;
	if (cub->img.image)
		mlx_destroy_image(cub->mlx_ptr, cub->img.image);
	if (cub->map)
	{
		while (cub->map[++i])
		{
			free(cub->mapcpy[i]);
			free(cub->map[i]);
		}
		free(cub->mapcpy);
		free(cub->map);
	}
	i = 0;
	while (i < 15)
	{
		if (cub->tex[i].img)
			mlx_destroy_image(cub->mlx_ptr, cub->tex[i].img);
		i++;
	}
	free_deux(cub);
	exit(0);
}

void	parse_reset(t_cub *cub)
{
	int	i;
	int	j;
	int	count_spr;

	j = -1;
	count_spr = 0;
	while (cub->map[++j])
	{
		i = -1;
		while (cub->map[j][++i])
		{
			if (cub->map[j][i] == 'd')
				cub->map[j][i] = 'D';
			if (cub->map[j][i] == 'C')
			{
				cub->spr[count_spr].x = i + 0.3;
				cub->spr[count_spr].y = j + 0.3;
				cub->spr[count_spr].tex = 10;
				cub->spr[count_spr].transf = 0;
				count_spr++;
			}
			if (cub->map[j][i] == 'B' || cub->map[j][i] == 'V')
				count_spr++;
		}
	}
}

int	close_cross(t_cub *cub)
{
	free_all(cub);
	return (0);
}
