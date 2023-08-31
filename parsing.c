/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcasades <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:40:08 by jcasades          #+#    #+#             */
/*   Updated: 2023/08/31 16:26:30 by jcasades         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_info(t_cub *data, char *line)
{
	if (line[0] == '\n')
	{
		ft_printf("backslash");	
		return (1);
	}
	if (!ft_strncmp(line, "NO ", 3))
	{
		if (*data->north)
			return (0);
		data->north = ft_strdup(line + 3);
	}
	if (!ft_strncmp(line, "SO ", 3))
	{
		if (*data->south)
			return (0);
		data->south = ft_strdup(line + 3);
	}
	if (!ft_strncmp(line, "WE ", 3))
	{
		if (*data->west)
			return (0);
		data->west = ft_strdup(line + 3);
	}
	if (!ft_strncmp(line, "EA ", 3))
	{
		if (*data->east)
			return (0);
		data->east = ft_strdup(line + 3);
	}
	if (!ft_strncmp(line, "F ", 2))
	{
		ft_printf("floor");
		if (*data->floor)
			return (0);
		data->east = ft_strdup(line + 2);
	}
	if (!ft_strncmp(line, "C ", 2))
	{
		if (*data->ceiling)
			return (0);
		data->east = ft_strdup(line + 2);
	}
	ft_printf("here\n");
	return (1);
}

int	parse(char *argv, t_cub *data)
{	
	int	i;
	int	file;
	char	*line;
	
	i = 0;
	file = open(argv, O_RDONLY);
	line = get_next_line(file);
	while (line && line[0] != '1' && line[0] != '0' && line[0] != ' ')
	{
		if (parse_info(data, line) == 0)
			return (0);
		free(line);
		line = get_next_line(file);
	}
	ft_printf("here");
	while (line)
	{
		free (line);
		i++;
		line = get_next_line(file);
	}
	data->map = malloc((sizeof (char *)) * i - 1);
	data->hgt = i - 1;
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
		data->map[i] = ft_strdup(line);
		free(line);
		line = get_next_line(file);
		i++;
	}
	ft_printf("%s", data->north);
	ft_printf("%s", data->south);
	ft_printf("%s", data->east);
	ft_printf("%s", data->west);
	ft_printf("%s", data->ceiling);
	ft_printf("%s", data->floor);
	i = 0;
	while (i <= data->hgt)
	{
		ft_printf("%s", data->map[i]);
		i++;
	}
}	
