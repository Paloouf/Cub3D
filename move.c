/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:37:51 by jcasades          #+#    #+#             */
/*   Updated: 2023/10/11 11:05:12 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_deux(t_cub *cub)
{
	if (cub->key.s_left == 1 && cub->map[(int)(cub->posY - (cub->dirX / 5))]
		[(int)(cub->posX + (cub->dirY / 5))] != '1' && cub->map[(int)(cub->posY
		- (cub->dirX / 5))][(int)(cub->posX + (cub->dirY / 5))] != 'D' &&
		cub->map[(int)(cub->posY - (cub->dirX / 10))][(int)(cub->posX +
		(cub->dirY / 10))] != 'B')
	{
		cub->posX += cub->dirY / 10;
		cub->posY -= cub->dirX / 10;
	}
	if (cub->key.r_left == 1)
	{
		cub->phangle -= 10;
		if (cub->phangle <= 0)
			cub->phangle += 360;
	}
	if (cub->key.r_right == 1)
	{
		cub->phangle += 10;
		if (cub->phangle >= 360)
			cub->phangle -= 360;
	}
	cub->dirX = -1 * (-sin(((double)cub->phangle * M_PI) / (double)180));
	cub->dirY = -1 * (cos(((double)cub->phangle * M_PI) / (double)180));
	cub->planeX = 1 * (cos(((double)cub->phangle * M_PI) / (double)180));
	cub->planeY = 1 * (sin(((double)cub->phangle * M_PI) / (double)180));
}

void	door_respawn(t_cub *cub, double factor, char c, int i)
{
	(void)i;
	cub->map[(int)(cub->posY + (cub->dirY * factor))][(int)(cub->posX
			+ (cub->dirX * factor))] = c;
}

void	door_move(t_cub *cub)
{
	static int	i = 0;

	if (cub->key.open == 1 && cub->map[(int)(cub->posY + (cub->dirY * 1.5))]
		[(int)(cub->posX + (cub->dirX * 1.5))] == 'D' && i == 0)
		door_respawn(cub, 1.5, 'd', i++);
	else if (cub->key.open == 1 && cub->map[(int)(cub->posY
			+ (cub->dirY / 5))][(int)(cub->posX + (cub->dirX / 5))] == 'D'
			&& i == 0)
		door_respawn(cub, 0.2, 'd', i++);
	else if (cub->key.open == 1 && cub->map[(int)(cub->posY
			+ (cub->dirY * 1.5))][(int)(cub->posX + (cub->dirX * 1.5))]
			== 'd' && i == 0)
		door_respawn(cub, 1.5, 'D', i++);
	else if (cub->key.open == 1 && cub->map[(int)(cub->posY
			+ (cub->dirY / 5))][(int)(cub->posX + (cub->dirX / 5))] == 'd'
			&& i == 0)
		door_respawn(cub, 0.2, 'D', i++);
	if (i >= 0)
		i++;
	if (i == 10)
		i = 0;
}

void	move_un(t_cub *cub)
{
	if (cub->key.s_right == 1 && cub->map[(int)(cub->posY + (cub->dirX / 5))]
		[(int)(cub->posX - (cub->dirY / 5))] != '1' && cub->map[(int)(cub->posY
		+ (cub->dirX / 5))][(int)(cub->posX - (cub->dirY / 5))] != 'D'
		&& cub->map[(int)(cub->posY + (cub->dirX / 10))]
		[(int)(cub->posX - (cub->dirY / 10))] != 'B')
	{
		cub->posX -= cub->dirY / 10;
		cub->posY += cub->dirX / 10;
	}
}

void	move(t_cub *cub)
{
	if (cub->key.open == 1 && cub->map[(int)cub->posY][(int)cub->posX] != 'd')
		door_move(cub);
	if (cub->key.forward == 1 && cub->map[(int)(cub->posY + (cub->dirY / 5))]
		[(int)(cub->posX + (cub->dirX / 5))] != '1' && cub->map[(int)(cub->posY
		+ (cub->dirY / 5))][(int)(cub->posX + (cub->dirX / 5))] != 'D'
		&& cub->map[(int)(cub->posY + (cub->dirY / 10))]
		[(int)(cub->posX + (cub->dirX / 10))] != 'B')
	{
		cub->posX += cub->dirX / 10;
		cub->posY += cub->dirY / 10;
	}
	if (cub->key.back == 1 && cub->map[(int)(cub->posY - (cub->dirY / 5))]
		[(int)(cub->posX - (cub->dirX / 5))] != '1' && cub->map[(int)(cub->posY
		- (cub->dirY / 5))][(int)(cub->posX - (cub->dirX / 5))] != 'D'
		&& cub->map[(int)(cub->posY - (cub->dirY / 10))]
		[(int)(cub->posX - (cub->dirX / 10))] != 'B')
	{
		cub->posX -= cub->dirX / 10;
		cub->posY -= cub->dirY / 10;
	}
	move_un(cub);
	move_deux(cub);
}
