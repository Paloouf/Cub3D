/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:19:13 by jcasades          #+#    #+#             */
/*   Updated: 2023/10/12 15:05:11 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_floor(t_cub *cub, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i] == ' ')
		i++;
	while (line[i] != '\n')
	{
		if (!ft_isdigit(line[i]) && line[i] != ',')
			return (ft_error("Error: Invalid Colors\n"));
		if (line[i] == ',')
			j++;
		i++;
	}
	if (j != 2)
		return (ft_error("Error: Invalid Color\n"));
	cub->fl.r_f = ft_atoi_du_pauvre(line, 1);
	cub->fl.g_f = ft_atoi_du_pauvre(line, 2);
	cub->fl.b_f = ft_atoi_du_pauvre(line, 3);
	if (cub->fl.r_f > 255 || cub->fl.g_f > 255 || cub->fl.b_f > 255)
		return (ft_error("Error: Invalid Color Values\n"));
	cub->flag_fl = 1;
	return (0);
}

int	ft_ceiling(t_cub *cub, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i] == ' ')
		i++;
	while (line[i] != '\n')
	{
		if (!ft_isdigit(line[i]) && line[i] != ',')
			return (ft_error("Error: Invalid Colors\n"));
		if (line[i] == ',')
			j++;
		i++;
	}
	if (j != 2)
		return (ft_error("Error: Invalid Color\n"));
	cub->cl.r_c = ft_atoi_du_pauvre(line, 1);
	cub->cl.g_c = ft_atoi_du_pauvre(line, 2);
	cub->cl.b_c = ft_atoi_du_pauvre(line, 3);
	if (cub->cl.r_c > 255 || cub->cl.g_c > 255 || cub->cl.b_c > 255)
		return (ft_error("Error: Invalid Color Values\n"));
	cub->flag_cl = 1;
	return (0);
}

int	ft_color_f(t_cub *cub, int i, int x)
{
	int	red;
	int	green;
	int	blue;

	(void)i;
	(void)x;
	red = cub->fl.r_f;
	blue = cub->fl.b_f;
	green = cub->fl.g_f;
	return (rgba_to_int(red, green, blue, 1));
}

int	ft_color_c(t_cub *cub, int i, int x)
{
	int	red;
	int	green;
	int	blue;

	if (x > (WIDTH / 2))
		x = WIDTH - x;
	i += sqrt(10 * x);
	red = (cub->cl.r_c / (1 + (double)(i / (HEIGHT / 12))));
	blue = (cub->cl.b_c / (1 + (double)(i / (HEIGHT / 12))));
	green = (cub->cl.g_c / (1 + (double)(i / (HEIGHT / 12))));
	return (rgba_to_int(red, green, blue, 1));
}
