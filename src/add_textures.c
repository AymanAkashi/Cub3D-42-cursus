/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:32:11 by moseddik          #+#    #+#             */
/*   Updated: 2022/11/12 12:51:51 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	add_textures_helper(t_cub *cub, float *wallbottom, float *walltop)
{
	*walltop = (WIN_HEIGHT / 2) - (cub->wall_strip_height / 2);
	*wallbottom = (WIN_HEIGHT / 2) + (cub->wall_strip_height / 2);
	if (*walltop < 0 || *walltop > WIN_HEIGHT)
	{
		*walltop = 0;
		*wallbottom = WIN_HEIGHT;
	}
}

void	add_textures(t_cub *cub, t_texture texture)
{
	int		i;
	int		*color;
	int		dist_top;
	float	wallbottom;
	float	walltop;

	add_textures_helper(cub, &wallbottom, &walltop);
	cub->rays->x_texture = (get_x_intersection(cub) / BLOCK_SIZE)
		- floor(get_x_intersection(cub) / BLOCK_SIZE);
	cub->rays->x_texture *= texture.width;
	i = walltop;
	while (i < wallbottom)
	{
		dist_top = i + (cub->wall_strip_height / 2) - (WIN_HEIGHT / 2);
		cub->rays->y_texture = dist_top
			* ((float)texture.height / cub->wall_strip_height);
		color = (int *)(texture.addr + cub->rays->y_texture * texture.size_line
				+ (int)cub->rays->x_texture * (texture.bpp / 8));
		cub->x = cub->rays->index;
		cub->y = i;
		put_pixel(*color, cub);
		i++;
	}
}
