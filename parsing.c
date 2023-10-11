/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:40:08 by jcasades          #+#    #+#             */
/*   Updated: 2023/10/11 10:53:14 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_tex_utils(t_cub *cub)
{
	cub->tex[0].img = mlx_xpm_file_to_image(cub->mlx_ptr, cub->north,
			&cub->tex[0].img_w, &cub->tex[0].img_h);
	cub->tex[1].img = mlx_xpm_file_to_image(cub->mlx_ptr, cub->south,
			&cub->tex[1].img_w, &cub->tex[1].img_h);
	cub->tex[2].img = mlx_xpm_file_to_image(cub->mlx_ptr, cub->west,
			&cub->tex[2].img_w, &cub->tex[2].img_h);
	cub->tex[3].img = mlx_xpm_file_to_image(cub->mlx_ptr, cub->east,
			&cub->tex[3].img_w, &cub->tex[3].img_h);
	cub->tex[4].img = mlx_xpm_file_to_image(cub->mlx_ptr,
			"./textures/toro1.xpm", &cub->tex[4].img_w, &cub->tex[4].img_h);
	cub->tex[5].img = mlx_xpm_file_to_image(cub->mlx_ptr,
			"./textures/toro2.xpm", &cub->tex[5].img_w, &cub->tex[5].img_h);
	cub->tex[6].img = mlx_xpm_file_to_image(cub->mlx_ptr,
			"./textures/toro3.xpm", &cub->tex[6].img_w, &cub->tex[6].img_h);
	cub->tex[7].img = mlx_xpm_file_to_image(cub->mlx_ptr,
			"./textures/toro4.xpm", &cub->tex[7].img_w, &cub->tex[7].img_h);
	cub->tex[8].img = mlx_xpm_file_to_image(cub->mlx_ptr,
			"./textures/toro5.xpm", &cub->tex[8].img_w, &cub->tex[8].img_h);
	cub->tex[9].img = mlx_xpm_file_to_image(cub->mlx_ptr,
			"./textures/toro6.xpm", &cub->tex[9].img_w, &cub->tex[9].img_h);
	cub->tex[10].img = mlx_xpm_file_to_image(cub->mlx_ptr,
			"./textures/tonneau.xpm", &cub->tex[10].img_w, &cub->tex[10].img_h);
}

int	fill_tex(t_cub *cub)
{
	int	i;

	i = 0;
	fill_tex_utils(cub);
	cub->tex[11].img = mlx_xpm_file_to_image(cub->mlx_ptr,
			"./textures/door.xpm", &cub->tex[11].img_w, &cub->tex[11].img_h);
	cub->tex[12].img = mlx_xpm_file_to_image(cub->mlx_ptr,
			"./textures/menu.xpm", &cub->tex[12].img_w, &cub->tex[12].img_h);
	cub->tex[13].img = mlx_xpm_file_to_image(cub->mlx_ptr,
			"./textures/died.xpm", &cub->tex[13].img_w, &cub->tex[13].img_h);
	cub->tex[14].img = mlx_xpm_file_to_image(cub->mlx_ptr,
			"./textures/escaped.xpm", &cub->tex[14].img_w, &cub->tex[14].img_h);
	while (i < 15)
	{
		if (!cub->tex[i].img)
			return (ft_error("Error: Invalid Textures\n"));
		cub->tex[i].addr = (int *)mlx_get_data_addr(cub->tex[i].img,
				&cub->tex[i].bpp, &cub->tex[i].line_len, &cub->tex[i].endian);
		i++;
	}
	return (0);
}

int	parse_info_deux(t_cub *cub, char *line)
{
	int	i;

	i = 0;
	if (!ft_strncmp(line, "WE ", 3))
	{
		if (cub->west[0])
			return (ft_error("Error: Texture Duplicate\n"));
		free(cub->west);
		while (line[3 + i] == ' ')
			i++;
		cub->west = ft_strdup(line + 3 + i);
		cub->west[ft_strlen(cub->west) - 1] = '\0';
	}
	if (!ft_strncmp(line, "EA ", 3))
	{
		if (cub->east[0])
			return (ft_error("Error: Texture Duplicate\n"));
		free(cub->east);
		while (line[3 + i] == ' ')
			i++;
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

int	parse_info(t_cub *cub, char *line)
{
	int	i;

	i = 0;
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
	if (parse_info_deux(cub, line) == 1)
		return (1);
	return (0);
}

int	check_barrel(char *line, char c)
{
	int	i;
	int	barrel;

	barrel = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == c)
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

void	flood_fill(t_cub *cub, int x, int y)
{
	if (y == -1 || !cub->mapcpy[y] || !cub->mapcpy[y][x])
		return ;
	if (cub->mapcpy[y][x] == '1' || cub->mapcpy[y][x] == 'F')
		return ;
	cub->mapcpy[y][x] = 'F';
	if (cub->map[y][x] == ' ')
		cub->map[y][x] = '0';
	flood_fill(cub, x + 1, y);
	flood_fill(cub, x - 1, y);
	flood_fill(cub, x, y + 1);
	flood_fill(cub, x, y - 1);
}

int	parse(char *argv, t_cub *cub, int i)
{
	int		error;
	int		file;
	char	*line;
	int		barrel;
	int		door;

	error = 0;
	barrel = 0;
	door = 0;
	file = open(argv, O_RDONLY);
	if (file < 0)
		error = ft_error("Error: Cannot Open Map file\n");
	line = get_next_line(file);
	while (line && line[0] != '1' && line[0] != '0' && line[0] != ' ')
	{
		error = parse_info(cub, line);
		free(line);
		line = get_next_line(file);
	}
	while (line)
	{
		barrel += check_barrel(line, 'C');
		barrel += check_barrel(line, 'B');
		barrel += check_barrel(line, 'V');
		free (line);
		i++;
		line = get_next_line(file);
	}
	cub->tono = barrel;
	cub->spr_order = malloc(sizeof(int *) * cub->tono);
	cub->map = ft_calloc(i + 1, sizeof(char *));
	cub->mapcpy = ft_calloc(i + 1, sizeof(char *));
	cub->tex = malloc(sizeof(t_tex) * 15);
	cub->spr = malloc(sizeof(t_spr) * barrel + 1);
	if (fill_tex(cub) == 1)
		error = 1;
	cub->hgt = i;
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
		add_barrel(cub, i, line);
		cub->map[i] = ft_strdup(line);
		cub->mapcpy[i] = ft_strdup(line);
		free(line);
		line = get_next_line(file);
		i++;
	}
	if (error == 1)
		free_all(cub);
}
