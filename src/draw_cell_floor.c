/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cell_floor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:27:59 by moseddik          #+#    #+#             */
/*   Updated: 2023/12/18 14:58:40 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_celling(t_cub *cub)
{
	int		i;
	int		j;
	int		shadow;

	i = 0;
	while (i < g_ss)
	{
		j = 0;
		shadow = i * 240 / g_ss;
		shadow <<= 24;
		while (j < WIN_WIDTH)
		{
			cub->x = j;
			cub->y = i;
			int color = shadow | cub->color_cell;
			put_pixel(color, cub);
			j++;
		}
		i++;
	}
}

void	draw_floor(t_cub *cub)
{
	int		i;
	int		j;
	int shadow;

	i = g_ss;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		shadow = (WIN_HEIGHT - i) * 200 / WIN_HEIGHT;
		shadow <<= 24;
		while (j < WIN_WIDTH)
		{
			cub->x = j;
			cub->y = i;
			int color = shadow | cub->color_floor;
			put_pixel(color, cub);
			j++;
		}
		i++;
	}
}
