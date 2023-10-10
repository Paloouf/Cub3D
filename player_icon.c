/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_icon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcasades <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:31:08 by jcasades          #+#    #+#             */
/*   Updated: 2023/10/10 15:40:08 by jcasades         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	draw_north(t_cub *cub, int i, int j)
{
	while (j < (HEIGHT) / 30)
	{
		i = 0;
		while (i < (HEIGHT) / 30)
		{
			if (!(i <= ((HEIGHT) / 60) - j || i >= ((HEIGHT) / 60) + j))
				pxl_to_img(cub, ((HEIGHT * 5 / 30) + i),
					((HEIGHT * 5) / 30) + j, rgba_to_int(160, 0, 0, 1));
			i++;
		}
		j++;
	}
}

void	draw_west(t_cub *cub, int i, int j)
{
	while (i < (HEIGHT) / 30)
	{
		j = 0;
		while (j < (HEIGHT) / 30)
		{
			if (!(i <= ((HEIGHT) / 60) - j || i >= ((HEIGHT) / 60) + j))
				pxl_to_img(cub, ((HEIGHT * 5 / 30) + j),
					((HEIGHT * 5) / 30) + i, rgba_to_int(160, 0, 0, 1));
			j++;
		}
		i++;
	}
}

void	draw_south(t_cub *cub, int i, int j)
{
	while (j < (HEIGHT) / 30)
	{
		i = 0;
		while (i < (HEIGHT) / 30)
		{
			if (!(i <= ((HEIGHT) / 60) - j || i >= ((HEIGHT) / 60) + j))
				pxl_to_img(cub, ((HEIGHT * 5 / 30) + i),
					((HEIGHT * 5) / 30) + ((HEIGHT / 30) - j),
					rgba_to_int(160, 0, 0, 1));
			i++;
		}
		j++;
	}
}

void	draw_east(t_cub *cub, int i, int j)
{
	while (i < (HEIGHT) / 30)
	{
		j = 0;
		while (j < (HEIGHT) / 30)
		{
			if (!(i <= ((HEIGHT) / 60) - j || i >= ((HEIGHT) / 60) + j))
				pxl_to_img(cub, ((HEIGHT * 5 / 30) + ((HEIGHT / 30) - j)),
					((HEIGHT * 5) / 30) + ((HEIGHT / 30) - i),
					rgba_to_int(160, 0, 0, 1));
			j++;
		}
		i++;
	}
}
