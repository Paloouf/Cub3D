/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:40:08 by jcasades          #+#    #+#             */
/*   Updated: 2023/08/31 15:59:50 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_info(t_cub *cub, char *line)
{
	printf("yo\n");
	if (line[0] == '\n')
		return (1);
	printf("wawa\n");
	if (!ft_strncmp(line, "NO ", 3))
	{
		if (cub->north)
			return (0);
		printf("wwwwwwwwwwwwwww\n");
		cub->north = ft_strdup(line + 3);
	}
	if (!ft_strncmp(line, "SO ", 3))
	{
		printf("xdddddddddd\n");
		if (cub->south)
			return (0);
		cub->south = ft_strdup(line + 3);
	}
	if (!ft_strncmp(line, "WE ", 3))
	{
		if (cub->west)
			return (0);
		cub->west = ft_strdup(line + 3);
	}
	if (!ft_strncmp(line, "EA ", 3))
	{
		if (cub->east)
			return (0);
		cub->east = ft_strdup(line);
	}
	printf("%s \n %s \n %s \n %s\n", cub->north, cub->south, cub->east, cub->west);
	return (1);
}

void	parse(char *argv, t_cub *cub)
{	
	int	i;
	int	file;
	char	*line;
	
	i = 0;
	file = open(argv, O_RDONLY);
	line = get_next_line(file);
	printf("mdrrrrrrrrr\n");
	while (line && line[0] != '1' && line[0] != '0' && line[0] != ' ')
	{
		if (parse_info(cub, line) == 0)
			return ;
		free(line);
		line = get_next_line(file);
	}
	printf("xddddddd\n");
	while (line)
	{
		free (line);
		i++;
		line = get_next_line(file);
	}
	cub->map = malloc((sizeof(char *)) * i - 1);
	cub->hgt = i - 1;
	close(file);
	file = open(argv, O_RDONLY);
	line = get_next_line(file);
	while (line && line[0] != '1' && line[0] != '0' && line[0] != ' ')
	{
		free(line);
		line = get_next_line(file);
	}
	//while (line)	
}	