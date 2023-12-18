/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:32:11 by moseddik          #+#    #+#             */
/*   Updated: 2023/12/18 14:59:05 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdio.h>

void	add_textures_helper(t_cub *cub, float *wallbottom, float *walltop)
{
	*walltop = g_ss - (cub->wall_strip_height / 2);
	*wallbottom = g_ss + (cub->wall_strip_height / 2);
	if (*walltop < 0)
		*walltop = 0;
	if (*wallbottom > WIN_HEIGHT)
		*wallbottom = WIN_HEIGHT;
	if (*walltop < 0 || *walltop > WIN_HEIGHT)
	{
		*walltop = 0;
		*wallbottom = WIN_HEIGHT;
	}
}

void	add_textures(t_cub *cub, t_texture texture, float distance)
{
	int		i;
	int		*color;
	int		dist_top;
	float	wallbottom;
	float	walltop;
	int mycolor;

	add_textures_helper(cub, &wallbottom, &walltop);
	float x = get_x_intersection(cub);
	if (distance > 200)
		mycolor = 200;
	else{
		mycolor = distance;
	}
	mycolor <<= 24;
	cub->rays->x_texture = (x / BLOCK_SIZE)
		- floor(x / BLOCK_SIZE);
	cub->rays->x_texture *= texture.width;
	i = walltop;
	while (i < wallbottom)
	{
		dist_top = i + (cub->wall_strip_height / 2) - g_ss;
		
		cub->rays->y_texture = dist_top
			* ((float)texture.height / cub->wall_strip_height);
		color = (int *)(texture.addr + cub->rays->y_texture * texture.size_line
				+ (int)cub->rays->x_texture * (texture.bpp / 8));
		int newcolor = mycolor | *color;
		cub->x = cub->rays->index;
		cub->y = i;
		put_pixel(newcolor, cub);
		i++;
	}
}
