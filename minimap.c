/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:31:14 by ltressen          #+#    #+#             */
/*   Updated: 2023/08/31 17:44:24 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_background(t_cub *cub, int color)
{
    int	i;
    int	j;

    i = HEIGHT / 25;
    while (i < (HEIGHT / 4))
    {
        j = WIDTH / 25;
        while (j < WIDTH / 5)
        {
            pxl_to_img(cub, j++, i, color);
        }
        ++i;
    }
}

void	render_walls(t_cub *cub, int color)
{

}

void	minimap(t_cub *cub)
{
	render_background(cub, rgba_to_int(53, 48, 220, 0.5));
	//render_walls(cub, rgba_to_int(53, 48, 220, 0.9));
}
