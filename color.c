/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcasades <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:19:13 by jcasades          #+#    #+#             */
/*   Updated: 2023/09/14 11:53:04 by jcasades         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_color_f(t_cub *cub, int i , int x)
{
	int	red;
	int	green;
	int	blue;

	red = (cub->fl.r_f / (1 + ((i - cub->cam[x].draw_end) / (HEIGHT / 25))));
	blue = (cub->fl.b_f / (1 + ((i - cub->cam[x].draw_end) / (HEIGHT / 25))));
	green = (cub->fl.g_f / (1 + ((i - cub->cam[x].draw_end) / (HEIGHT / 25)))); 
	return(rgba_to_int(red, green, blue, 1));
}

int	ft_color_c(t_cub *cub, int i)
{
        int     red;
        int     green;
        int     blue;

	red = (cub->cl.r_c / (1 + (double)(i / (HEIGHT / 25))));
	blue = (cub->cl.b_c / (1 + (double)(i / (HEIGHT / 25))));
	green = (cub->cl.g_c / (1 + (double)(i / (HEIGHT / 25))));
	return(rgba_to_int(red, green, blue, 1));
}
