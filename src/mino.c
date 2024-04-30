/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mino.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:24:46 by ltressen          #+#    #+#             */
/*   Updated: 2023/10/12 13:53:57 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	mino_ai_deux(t_cub *cub, int i, double move_x, double move_y)
{
	if (cub->map[(int)(cub->spr[i].y - (move_y * 2))]
		[(int)(cub->spr[i].x - (move_x * 2))] != '1'
		&& cub->map[(int)(cub->spr[i].y - (move_y * 2))]
		[(int)(cub->spr[i].x - (move_x * 2))] != 'D')
	{
		cub->spr[i].x -= move_x;
		cub->spr[i].y -= move_y;
	}
	else if (cub->map[(int)(cub->spr[i].y - (move_y * 2))]
		[(int)(cub->spr[i].x)] != '1' && cub->map[(int)(cub->spr[i].y
		- (move_y * 2))][(int)(cub->spr[i].x)] != 'D')
		cub->spr[i].y -= move_y;
	else if (cub->map[(int)(cub->spr[i].y)][(int)(cub->spr[i].x
		- (move_x * 2))] != '1' && cub->map[(int)(cub->spr[i].y)]
		[(int)(cub->spr[i].x - (move_x * 2))] != 'D')
		cub->spr[i].x -= move_x;
}

void	mino_ai(t_cub *cub, int i, double move_x, double move_y)
{
	move_x = (cub->spr[i].x - cub->posx) / 10;
	if (move_x < cub->speed * -1)
		move_x = -1 * cub->speed;
	if (move_x > cub->speed)
		move_x = cub->speed;
	move_y = (cub->spr[i].y - cub->posy) / 10;
	if (move_y < -1 * cub->speed)
		move_y = -1 * cub->speed;
	if (move_y > cub->speed)
		move_y = cub->speed;
	mino_ai_deux(cub, i, move_x, move_y);
}

void	check_mino(t_cub *cub, int i)
{
	cub->spr[i].dist = (((cub->posx - cub->spr[i].x) * (cub->posx
					- cub->spr[i].x)) + ((cub->posy - cub->spr[i].y)
				* (cub->posy - cub->spr[i].y)));
	if (cub->spr[i].dist < 3 && cub->spr[i].type == 'C')
		cub->spr[i].transf = 1;
	if (cub->spr[i].dist < 0.5 && cub->spr[i].type == 'C')
	{
		cub->game = 0;
		cub->gameover = 1;
	}
	if (cub->spr[i].dist < 0.5 && cub->spr[i].type == 'V')
	{
		cub->game = 0;
		cub->gamewin = 1;
	}
}

void	check_sprite(t_cub *cub)
{
	int			i;
	static int	j = 0;
	double		move_x;
	double		move_y;

	i = 0;
	j++;
	move_x = 0;
	move_y = 0;
	if (j == 6)
		j = 0;
	while (i < cub->tono)
	{
		check_mino(cub, i);
		if (cub->spr[i].type == 'C' && cub->spr[i].transf == 1)
		{
			cub->spr[i].tex = 4 + j;
			mino_ai(cub, i, move_x, move_y);
		}
		i++;
	}
}

void	ft_sort_sprite(t_cub *cub)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (i < cub->tono)
	{
		j = 0;
		count = 0;
		while (j < cub->tono)
		{
			if (cub->spr[j].dist > cub->spr[i].dist)
				count++;
			j++;
		}
		cub->spr_order[count] = i;
		i++;
	}
}
