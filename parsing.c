/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:40:08 by jcasades          #+#    #+#             */
/*   Updated: 2023/08/31 18:19:10 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_floor(t_cub *cub, char *line)
{
	cub->fl.r_f = ft_atoi_du_pauvre(line, 1);
	cub->fl.g_f = ft_atoi_du_pauvre(line, 2);
	cub->fl.b_f = ft_atoi_du_pauvre(line, 3);
}

void	ft_ceiling(t_cub *cub, char *line)
{
	cub->cl.r_c = ft_atoi_du_pauvre(line, 1);
	cub->cl.g_c = ft_atoi_du_pauvre(line, 2);
	cub->cl.b_c = ft_atoi_du_pauvre(line, 3);
}

int	parse_info(t_cub *cub, char *line)
{
	if (line[0] == '\n')
		return (1);
	if (!ft_strncmp(line, "NO ", 3))
	{
		if (cub->north[0])
			return (0);
		cub->north = ft_strdup(line + 3);
	}
	if (!ft_strncmp(line, "SO ", 3))
	{
		if (cub->south[0])
			return (0);
		cub->south = ft_strdup(line + 3);
	}
	if (!ft_strncmp(line, "WE ", 3))
	{
		if (cub->west[0])
			return (0);
		cub->west = ft_strdup(line + 3);
	}
	if (!ft_strncmp(line, "EA ", 3))
	{
		if (cub->east[0])
			return (0);
		cub->east = ft_strdup(line + 3);
	}
	if (!ft_strncmp(line, "F ", 2))
	{
		ft_floor(cub, line + 2);
	}
	if (!ft_strncmp(line, "C ", 2))
	{
		ft_ceiling(cub, line + 2);
	}
	return (1);
}

int	parse(char *argv, t_cub *cub)
{	
	int	i;
	int	file;
	char	*line;
	
	i = 0;
	file = open(argv, O_RDONLY);
	line = get_next_line(file);
	while (line && line[0] != '1' && line[0] != '0' && line[0] != ' ')
	{
		if (parse_info(cub, line) == 0)
			return (0);
		free(line);
		line = get_next_line(file);
	}
	while (line)
	{
		free (line);
		i++;
		line = get_next_line(file);
	}
	cub->map = malloc((sizeof (char *)) * i - 1);
	cub->hgt = i - 1;
	close(file);
	file = open(argv, O_RDONLY);
	line = get_next_line(file);
	while (line && line[0] != '1' && line[0] != '0' && line[0] != ' ')
	{
		free(line);
		line = get_next_line(file);
	}
	i = 0;
	while (line)
	{
		cub->map[i] = ft_strdup(line);
		free(line);
		line = get_next_line(file);
		i++;
	}
}
