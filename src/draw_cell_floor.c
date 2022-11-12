/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cell_floor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:27:59 by moseddik          #+#    #+#             */
/*   Updated: 2022/11/10 22:28:23 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_celling(t_cub *cub)
{
	int		i;
	int		j;

	i = 0;
	while (i < WIN_HEIGHT / 2)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			cub->x = j;
			cub->y = i;
			put_pixel(cub->color_cell, cub);
			j++;
		}
		i++;
	}
}

void	draw_floor(t_cub *cub)
{
	int		i;
	int		j;

	i = WIN_HEIGHT / 2;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			cub->x = j;
			cub->y = i;
			put_pixel(cub->color_floor, cub);
			j++;
		}
		i++;
	}
}
