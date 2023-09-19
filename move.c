/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:37:51 by jcasades          #+#    #+#             */
/*   Updated: 2023/09/19 11:23:58 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	jump(t_cub *cub)
{
	if (cub->fjump == 1)
	{
		cub->jump += 80;
		if (cub->jump == 400)
			cub->fjump = 2;
	}
	if (cub->fjump == 2)
	{
		cub->jump -= 20;
		if (cub->jump == 0)
			cub->fjump = 0;
	}
}

void	move (t_cub *cub)
{
	if (cub->key.forward == 1 && cub->map[(int)(cub->posY + (cub->dirY / 10))][(int)cub->posX] != '1' && cub->map[(int)cub->posY][(int)(cub->posX + (cub->dirX / 10))] != '1')
	{
		cub->posX += cub->dirX / 10;
		cub->posY += cub->dirY / 10;
	}
	if (cub->key.back == 1 && cub->map[(int)(cub->posY + (cub->dirY / 10))][(int)cub->posX] != '1' && cub->map[(int)cub->posY][(int)(cub->posX + (cub->dirX / 10))] != '1')
	{
		cub->posX -= cub->dirX / 10;
		cub->posY -= cub->dirY / 10;
	}
	if (cub->key.s_right == 1 && cub->map[(int)(cub->posY + (cub->dirY / 10))][(int)cub->posX] != '1' && cub->map[(int)cub->posY][(int)(cub->posX + (cub->dirX / 10))] != '1')
	{
		cub->posX -= cub->dirY / 10;
		cub->posY += cub->dirX / 10;
	}
	if (cub->key.s_left == 1 && cub->map[(int)(cub->posY + (cub->dirY / 10))][(int)cub->posX] != '1' && cub->map[(int)cub->posY][(int)(cub->posX + (cub->dirX / 10))] != '1')
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
	if (cub->key.crouch == 1 && cub->jump == 0)
		cub->crouch = 120;
	else
		cub->crouch = 0;
	if (cub->key.jump == 1 && cub->crouch == 0 && cub->fjump == 0)
		cub->fjump = 1;
}
