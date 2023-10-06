/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:40:08 by jcasades          #+#    #+#             */
/*   Updated: 2023/10/06 14:49:59 by ltressen         ###   ########.fr       */
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

void	fill_tex(t_cub *cub)
{
	int	i;

	i = 0;
	cub->tex[0].img = mlx_xpm_file_to_image(cub->mlx_ptr, cub->north, &cub->tex[0].img_w, &cub->tex[0].img_h);
	cub->tex[1].img = mlx_xpm_file_to_image(cub->mlx_ptr, cub->south, &cub->tex[1].img_w, &cub->tex[1].img_h);
	cub->tex[2].img = mlx_xpm_file_to_image(cub->mlx_ptr, cub->west, &cub->tex[2].img_w, &cub->tex[2].img_h);
	cub->tex[3].img = mlx_xpm_file_to_image(cub->mlx_ptr, cub->east, &cub->tex[3].img_w, &cub->tex[3].img_h);
	cub->tex[4].img = mlx_xpm_file_to_image(cub->mlx_ptr, "./textures/toro1.xpm", &cub->tex[4].img_w, &cub->tex[4].img_h);
	cub->tex[5].img = mlx_xpm_file_to_image(cub->mlx_ptr, "./textures/toro2.xpm", &cub->tex[5].img_w, &cub->tex[5].img_h);
	cub->tex[6].img = mlx_xpm_file_to_image(cub->mlx_ptr, "./textures/toro3.xpm", &cub->tex[6].img_w, &cub->tex[6].img_h);
	cub->tex[7].img = mlx_xpm_file_to_image(cub->mlx_ptr, "./textures/toro4.xpm", &cub->tex[7].img_w, &cub->tex[7].img_h);
	cub->tex[8].img = mlx_xpm_file_to_image(cub->mlx_ptr, "./textures/toro5.xpm", &cub->tex[8].img_w, &cub->tex[8].img_h);
	cub->tex[9].img = mlx_xpm_file_to_image(cub->mlx_ptr, "./textures/toro6.xpm", &cub->tex[9].img_w, &cub->tex[9].img_h);
	cub->tex[10].img = mlx_xpm_file_to_image(cub->mlx_ptr, "./textures/tonneau.xpm", &cub->tex[10].img_w, &cub->tex[10].img_h);
	cub->tex[11].img = mlx_xpm_file_to_image(cub->mlx_ptr, "./textures/spruce_trapdoor.xpm", &cub->tex[11].img_w, &cub->tex[11].img_h);
	cub->tex[12].img = mlx_xpm_file_to_image(cub->mlx_ptr, "./textures/menu.xpm", &cub->tex[12].img_w, &cub->tex[12].img_h);
	cub->tex[13].img = mlx_xpm_file_to_image(cub->mlx_ptr, "./textures/died.xpm", &cub->tex[13].img_w, &cub->tex[13].img_h);
	cub->tex[14].img = mlx_xpm_file_to_image(cub->mlx_ptr, "./textures/escaped.xpm", &cub->tex[14].img_w, &cub->tex[14].img_h);
	while (i < 15)
	{
			cub->tex[i].addr = (int *)mlx_get_data_addr(cub->tex[i].img, &cub->tex[i].bpp, &cub->tex[i].line_len, &cub->tex[i].endian);
			i++;
	}
}

int	parse_info_deux(t_cub *cub, char *line)
{
	if (!ft_strncmp(line, "WE ", 3))
	{
		if (cub->west[0])
			return (0);
		free(cub->west);
		cub->west = ft_strdup(line + 3);
		cub->west[ft_strlen(cub->west) - 1] = '\0';
	}
	if (!ft_strncmp(line, "EA ", 3))
	{
		if (cub->east[0])
			return (0);
		free(cub->east);
		cub->east = ft_strdup(line + 3);
		cub->east[ft_strlen(cub->east) - 1] = '\0';
	}
	if (!ft_strncmp(line, "F ", 2))
		ft_floor(cub, line + 2);
	if (!ft_strncmp(line, "C ", 2))
		ft_ceiling(cub, line + 2);
	return (1);
}

int	parse_info(t_cub *cub, char *line)
{
	if (line[0] == '\n')
		return (1);
	if (!ft_strncmp(line, "NO ", 3))
	{
		if (cub->north[0])
			return (0);
		free(cub->north);
		cub->north = ft_strdup(line + 3);
		cub->north[ft_strlen(cub->north) - 1] = '\0';
	}
	if (!ft_strncmp(line, "SO ", 3))
	{
		if (cub->south[0])
			return (0);
		free(cub->south);
		cub->south = ft_strdup(line + 3);
		cub->south[ft_strlen(cub->south) - 1] = '\0';
	}
	if (!parse_info_deux(cub, line))
		return (0);
	return (1);
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
	static	int tono = 0;
	int	j;

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

int	parse(char *argv, t_cub *cub)
{	
	int	i;
	int	file;
	char	*line;
	int	barrel;
	int	door;
	
	i = 0;
	barrel = 0;
	door = 0;
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
	cub->tex = malloc(sizeof(t_tex) * 15);
	cub->spr = malloc(sizeof(t_spr) * barrel + 1);
	fill_tex(cub);
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
		add_barrel(cub, i, line);
		cub->map[i] = ft_strdup(line);
		free(line);
		line = get_next_line(file);
		i++;
	}
}
