/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:40:08 by jcasades          #+#    #+#             */
/*   Updated: 2023/10/12 14:55:57 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	parse_info_deux(t_cub *cub, char *line, int i)
{
	while (ft_strlen(line) > 2 && line[3 + i] && line[3 + i] == ' ')
		i++;
	if (!ft_strncmp(line, "WE ", 3))
	{
		if (cub->west[0])
			return (ft_error("Error: Texture Duplicate\n"));
		free(cub->west);
		cub->west = ft_strdup(line + 3 + i);
		cub->west[ft_strlen(cub->west) - 1] = '\0';
	}
	if (!ft_strncmp(line, "EA ", 3))
	{
		if (cub->east[0])
			return (ft_error("Error: Texture Duplicate\n"));
		free(cub->east);
		cub->east = ft_strdup(line + 3 + i);
		cub->east[ft_strlen(cub->east) - 1] = '\0';
	}
	if (!ft_strncmp(line, "F ", 2))
		if (ft_floor(cub, line + 2) == 1)
			return (1);
	if (!ft_strncmp(line, "C ", 2))
		if (ft_ceiling(cub, line + 2) == 1)
			return (1);
	return (0);
}

int	parse_info(t_cub *cub, char *line, int i)
{
	if (line[0] == '\n')
		return (0);
	if (!ft_strncmp(line, "NO ", 3))
	{
		if (cub->north[0])
			return (ft_error("Error: Texture Duplicate\n"));
		free(cub->north);
		while (line[3 + i] == ' ')
			i++;
		cub->north = ft_strdup(line + 3 + i);
		cub->north[ft_strlen(cub->north) - 1] = '\0';
	}
	if (!ft_strncmp(line, "SO ", 3))
	{
		if (cub->south[0])
			return (ft_error("Error: Texture Duplicate\n"));
		free(cub->south);
		while (line[3 + i] == ' ')
			i++;
		cub->south = ft_strdup(line + 3 + i);
		cub->south[ft_strlen(cub->south) - 1] = '\0';
	}
	if (parse_info_deux(cub, line, 0) == 1)
		return (1);
	return (0);
}

int	check_barrel(char *line)
{
	int	i;
	int	barrel;

	barrel = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == 'C' || line[i] == 'B' || line[i] == 'V')
			barrel++;
		i++;
	}
	return (barrel);
}

void	add_barrel(t_cub *cub, int i, char *line)
{
	static int	tono = 0;
	int			j;

	j = 0;
	while (line[j])
	{
		cub->spr[tono].type = line[j];
		if (line[j] == 'C')
		{
			cub->spr[tono].x = j + 0.3;
			cub->spr[tono].y = i + 0.3;
			cub->spr[tono].tex = 10;
			cub->spr[tono].transf = 0;
			tono++;
		}
		if (line[j] == 'B' || line[j] == 'V')
		{
			cub->spr[tono].x = j + 0.5;
			cub->spr[tono].y = i + 0.5;
			cub->spr[tono].tex = 10;
			tono++;
		}
		j++;
	}
	return ;
}

void	parse(char *argv, t_cub *cub, int file, int i)
{
	static int		error = 0;
	char			*line;
	static int		barrel = 0;

	line = get_next_line(file);
	cub->flag_cl = 0;
	cub->flag_fl = 0;
	while (line && line[0] != '1' && line[0] != '0' && line[0] != ' ')
	{
		error += parse_info(cub, line, 0);
		free(line);
		line = get_next_line(file);
	}
	while (line)
	{
		barrel += check_barrel(line);
		free (line);
		i++;
		line = get_next_line(file);
	}
	if (fill_tex(cub, barrel, i) == 1)
		error += 1;
	cub->hgt = i;
	close(file);
	parse_suite(argv, cub, file, error);
}
