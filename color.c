/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:19:13 by jcasades          #+#    #+#             */
/*   Updated: 2023/10/09 12:05:00 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_color_f(t_cub *cub, int i , int x)
{
	int	red;
	int	green;
	int	blue;

	if (cub->fl.r_f <= 255 && cub->fl.r_f >= 0 || cub->fl.g_f > 256 && cub->fl.g_f > -1 || cub->fl.b_f > 256 && cub->fl.b_f > -1)
	{
		red = cub->fl.r_f;
		blue = cub->fl.b_f;
		green = cub->fl.g_f;
	}
	else
		ft_error("Error: Invalid Color Values\n", cub);
	return(rgba_to_int(red, green, blue, 1));
}

int	ft_color_c(t_cub *cub, int i, int x)
{
        int     red;
        int     green;
        int     blue;
	
	if (x > (WIDTH / 2))
		x = WIDTH - x;
	i += sqrt(10 * x);
	if (cub->cl.r_c <= 255 && cub->cl.r_c >= 0 || cub->cl.g_c > 256 && cub->cl.g_c > -1 || cub->cl.b_c > 256 && cub->cl.b_c > -1)
	{
		red = (cub->cl.r_c / (1 + (double)(i / (HEIGHT / 12))));
		blue = (cub->cl.b_c / (1 + (double)(i / (HEIGHT / 12))));
		green = (cub->cl.g_c / (1 + (double)(i / (HEIGHT / 12))));
	}
	else
		ft_error("Error: Invalid Color Values\n", cub);
	return(rgba_to_int(red, green, blue, 1));
}
