/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:37:51 by jcasades          #+#    #+#             */
/*   Updated: 2023/10/11 14:05:33 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_deux(t_cub *cub)
{
	if (cub->key.s_left == 1 && cub->map[(int)(cub->posy - (cub->dirx / 5))]
		[(int)(cub->posx + (cub->diry / 5))] != '1' && cub->map[(int)(cub->posy
		- (cub->dirx / 5))][(int)(cub->posx + (cub->diry / 5))] != 'D' &&
		cub->map[(int)(cub->posy - (cub->dirx / 10))][(int)(cub->posx +
		(cub->diry / 10))] != 'B')
	{
		cub->posx += cub->diry / 10;
		cub->posy -= cub->dirx / 10;
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
	cub->dirx = -1 * (-sin(((double)cub->phangle * M_PI) / (double)180));
	cub->diry = -1 * (cos(((double)cub->phangle * M_PI) / (double)180));
	cub->planex = 1 * (cos(((double)cub->phangle * M_PI) / (double)180));
	cub->planey = 1 * (sin(((double)cub->phangle * M_PI) / (double)180));
}

void	door_respawn(t_cub *cub, double factor, char c, int i)
{
	(void)i;
	cub->map[(int)(cub->posy + (cub->diry * factor))][(int)(cub->posx
			+ (cub->dirx * factor))] = c;
}

void	door_move(t_cub *cub)
{
	static int	i = 0;

	if (cub->key.open == 1 && cub->map[(int)(cub->posy + (cub->diry * 1))]
		[(int)(cub->posx + (cub->dirx * 1))] == 'D' && i == 0)
		door_respawn(cub, 1, 'd', i++);
	else if (cub->key.open == 1 && cub->map[(int)(cub->posy
			+ (cub->diry / 5))][(int)(cub->posx + (cub->dirx / 5))] == 'D'
			&& i == 0)
		door_respawn(cub, 0.2, 'd', i++);
	else if (cub->key.open == 1 && cub->map[(int)(cub->posy
			+ (cub->diry * 1))][(int)(cub->posx + (cub->dirx * 1))]
			== 'd' && i == 0)
		door_respawn(cub, 1, 'D', i++);
	else if (cub->key.open == 1 && cub->map[(int)(cub->posy
			+ (cub->diry / 5))][(int)(cub->posx + (cub->dirx / 5))] == 'd'
			&& i == 0)
		door_respawn(cub, 0.2, 'D', i++);
	if (i >= 0)
		i++;
	if (i == 10)
		i = 0;
}

void	move_un(t_cub *cub)
{
	if (cub->key.s_right == 1 && cub->map[(int)(cub->posy + (cub->dirx / 5))]
		[(int)(cub->posx - (cub->diry / 5))] != '1' && cub->map[(int)(cub->posy
		+ (cub->dirx / 5))][(int)(cub->posx - (cub->diry / 5))] != 'D'
		&& cub->map[(int)(cub->posy + (cub->dirx / 10))]
		[(int)(cub->posx - (cub->diry / 10))] != 'B')
	{
		cub->posx -= cub->diry / 10;
		cub->posy += cub->dirx / 10;
	}
}

void	move(t_cub *cub)
{
	if (cub->key.open == 1 && cub->map[(int)cub->posy][(int)cub->posx] != 'd')
		door_move(cub);
	if (cub->key.forward == 1 && cub->map[(int)(cub->posy + (cub->diry / 5))]
		[(int)(cub->posx + (cub->dirx / 5))] != '1' && cub->map[(int)(cub->posy
		+ (cub->diry / 5))][(int)(cub->posx + (cub->dirx / 5))] != 'D'
		&& cub->map[(int)(cub->posy + (cub->diry / 10))]
		[(int)(cub->posx + (cub->dirx / 10))] != 'B')
	{
		cub->posx += cub->dirx / 10;
		cub->posy += cub->diry / 10;
	}
	if (cub->key.back == 1 && cub->map[(int)(cub->posy - (cub->diry / 5))]
		[(int)(cub->posx - (cub->dirx / 5))] != '1' && cub->map[(int)(cub->posy
		- (cub->diry / 5))][(int)(cub->posx - (cub->dirx / 5))] != 'D'
		&& cub->map[(int)(cub->posy - (cub->diry / 10))]
		[(int)(cub->posx - (cub->dirx / 10))] != 'B')
	{
		cub->posx -= cub->dirx / 10;
		cub->posy -= cub->diry / 10;
	}
	move_un(cub);
	move_deux(cub);
}
