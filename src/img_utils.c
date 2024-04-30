/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:32:49 by ltressen          #+#    #+#             */
/*   Updated: 2023/10/09 11:24:59 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_atoi_du_pauvre(char *str, int i)
{
	while (i > 1)
	{
		if (*str == ',')
		{
			i--;
			str++;
		}
		else
			str++;
	}
	return (ft_atoi(str));
}

void	pxl_to_img(t_cub *cub, int x, int y, unsigned int color)
{
	char	*pixel;
	int		i;

	i = cub->img.bpp - 8;
	pixel = cub->img.data_addr
		+ (y * cub->img.line_len + x * (cub->img.bpp / 8));
	while (i >= 0)
	{
		if (cub->img.endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (cub->img.bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

int	rgba_to_int(int r, int g, int b, float a)
{
	return (((int)(a * 255) << 24) | r << 16 | g << 8 | b);
}
