/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:19:13 by jcasades          #+#    #+#             */
/*   Updated: 2023/10/10 14:58:35 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_color_f(t_cub *cub, int i, int x)
{
	int	red;
	int	green;
	int	blue;

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
