/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:30:08 by ltressen          #+#    #+#             */
/*   Updated: 2023/08/31 15:30:19 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_events(int key, t_cub *cub)
{
	if (key == XK_Escape)
	{
		exit(0);
	}
	return (0);
}

int	close_cross(t_cub *cub)
{
	//free_all(cub);
	exit(EXIT_SUCCESS);
	return (0);
}
