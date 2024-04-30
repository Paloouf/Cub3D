/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:52:12 by ltressen          #+#    #+#             */
/*   Updated: 2023/10/12 14:50:23 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_map(t_cub *cub, int i, int j)
{
	if (!(cub->map[i] && cub->map[i + 1]
			&& (cub->map[i - 1][j] && cub->map[i + 1][j]
		&& cub->map[i][j - 1] && cub->map[i][j + 1])
			&& ((cub->map[i][j + 1] == '1' || cub->map[i][j + 1] == '0'
			|| cub->map[i][j + 1] == 'D' || cub->map[i][j + 1] == 'C' ||
			cub->map[i][j + 1] == 'B' || cub->map[i][j + 1] == 'V' ||
			cub->map[i][j + 1] == cub->map[(int)cub->posy][(int)cub->posx])
			&& (cub->map[i][j - 1] == '1' || cub->map[i][j - 1] == '0'
			|| cub->map[i][j - 1] == 'D' || cub->map[i][j - 1] == 'C' ||
			cub->map[i][j - 1] == 'B' || cub->map[i][j - 1] == 'V' ||
			cub->map[i][j - 1] == cub->map[(int)cub->posy][(int)cub->posx])
			&& (cub->map[i + 1][j] == '1' || cub->map[i + 1][j] == '0'
			|| cub->map[i + 1][j] == 'D' || cub->map[i + 1][j] == 'C' ||
			cub->map[i + 1][j] == 'B' || cub->map[i + 1][j] == 'V' ||
			cub->map[i + 1][j] == cub->map[(int)cub->posy][(int)cub->posx])
			&& (cub->map[i - 1][j] == '1' || cub->map[i - 1][j] == '0'
			|| cub->map[i - 1][j] == 'D' || cub->map[i - 1][j] == 'C' ||
			cub->map[i - 1][j] == 'B' || cub->map[i - 1][j] == 'V' ||
			cub->map[i - 1][j] == cub->map[(int)cub->posy][(int)cub->posx]))))
		return (ft_error("Error : Map isn't a valid map\n"));
	return (0);
}

int	check_map_deux(t_cub *cub, int i, int j)
{
	if ((i == 0 || i == cub->hgt) && (cub->map[i][j] != '1'
		&& cub->map[i][j] != ' ' && cub->map[i][j] != '\t'
		&& cub->map[i][j] != '\n'))
		return (ft_error("Error: Invalid Map\n"));
	if ((j == 0 || j == (int)ft_strlen(cub->map[i]))
		&& (cub->map[i][j] != '1' && cub->map[i][j] != ' '
		&& cub->map[i][j] != '\t' && cub->map[i][j] != '\n'))
		return (ft_error("Error: Invalid Map\n"));
	else if (((i > 0 && j > 0) && (cub->map[i][j] == '0'
			|| cub->map[i][j] == cub->map[(int)cub->posy]
		[(int)cub->posx]
		|| cub->map[i][j] == 'B' || cub->map[i][j] == 'V'
		|| cub->map[i][j] == 'C')))
		if (check_map(cub, i, j) == 1)
			return (1);
	if ((i > 0 && j > 0) && cub->map[i][j] == 'D')
		if (check_door(cub, i, j) == 1)
			return (1);
	if (check_player(cub) == 1)
		return (1);
	return (0);
}

int	check(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	flood_fill(cub, (int)cub->posx, (int)cub->posy);
	while (cub->map[i])
	{
		j = -1;
		while (cub->map[i][++j])
		{
			if (check_map_deux(cub, i, j) == 1)
				return (1);
		}
		i++;
	}
	if (!cub->east[0] || !cub->south[0] || !cub->west[0] || !cub->north[0]
		|| !cub->flag_cl || !cub->flag_fl)
		return (ft_error("Missing information\n"));
	return (0);
}

int	check_door(t_cub *cub, int i, int j)
{
	if (!((cub->map[i - 1][j] && cub->map[i + 1][j]
		&& cub->map[i][j - 1] && cub->map[i][j + 1])
		&& ((cub->map[i][j + 1] == '1' && cub->map[i][j - 1] == '1')
		|| (cub->map[i + 1][j] == '1' && cub->map[i - 1][j] == '1'))))
		return (ft_error("Error: Invalid Door\n"));
	return (0);
}

int	ft_error(char *str)
{
	while (*str)
		write(2, str++, 1);
	return (1);
}
