/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:37:51 by jcasades          #+#    #+#             */
/*   Updated: 2023/09/29 11:55:37 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	move (t_cub *cub)
{
	if (cub->key.forward == 1 && cub->map[(int)(cub->posY + (cub->dirY / 5))][(int)(cub->posX + (cub->dirX / 5))] != '1')
	{
		cub->posX += cub->dirX / 10;
		cub->posY += cub->dirY / 10;
	}
	if (cub->key.back == 1 && cub->map[(int)(cub->posY - (cub->dirY / 5))][(int)(cub->posX - (cub->dirX / 5))] != '1')
	{
		cub->posX -= cub->dirX / 10;
		cub->posY -= cub->dirY / 10;
	}
	if (cub->key.s_right == 1 && cub->map[(int)(cub->posY + (cub->dirX / 5))][(int)(cub->posX - (cub->dirY / 5))] != '1')
	{
		cub->posX -= cub->dirY / 10;
		cub->posY += cub->dirX / 10;
	}
	if (cub->key.s_left == 1 && cub->map[(int)(cub->posY - (cub->dirX / 5))][(int)(cub->posX + (cub->dirY / 5))] != '1')
	{
		cub->posX += cub->dirY / 10;
		cub->posY -= cub->dirX / 10;
	}
	if (cub->key.r_left == 1)
	{	
		cub->phangle -= 10;
		if (cub->phangle <= 0)
			cub->phangle += 360;
		cub->dirX = -1 * -sin(((double)cub->phangle * M_PI) / 180);
	      	cub->dirY = -1 * cos(((double)cub->phangle * M_PI) / 180);
		cub->planeX = 1 * cos(((double)cub->phangle * M_PI) / 180);
		cub->planeY = 1 * sin(((double)cub->phangle * M_PI) / 180);
	}
	if (cub->key.r_right == 1)
	{
		cub->phangle += 10;
		if (cub->phangle >= 360)
			cub->phangle -= 360;
		cub->dirX = -1 * (-sin(((double)cub->phangle * M_PI) / (double)180));
	      	cub->dirY = -1 * (cos(((double)cub->phangle * M_PI) / (double)180));
		cub->planeX = 1 * (cos(((double)cub->phangle * M_PI) / (double)180));
		cub->planeY = 1 * (sin(((double)cub->phangle * M_PI) / (double)180));
	}
}
