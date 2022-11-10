/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:48:30 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/11/10 19:49:27 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	open_image(t_cub *cub, t_compass *tmp)
{
	tmp->texture.img = mlx_xpm_file_to_image(cub->mlx, tmp->path,
			&tmp->texture.width, &tmp->texture.height);
	if (!tmp->texture.img)
	{
		(red(), printf("Cube3D: Error file doesn't open\n"), reset());
		exit(1);
	}
	tmp->texture.addr = mlx_get_data_addr(tmp->texture.img,
			&tmp->texture.bpp, &tmp->texture.size_line, &tmp->texture.endian);
}

void	open_image_door(t_cub *cub)
{
	cub->texture_door.img = mlx_xpm_file_to_image(cub->mlx, "textures/door.xpm",
			&cub->texture_door.width, &cub->texture_door.height);
	if (!cub->texture_door.img)
	{
		printf("Error\nFailed to load door texture\n");
		exit(1);
	}
	cub->texture_door.addr = mlx_get_data_addr(cub->texture_door.img,
			&cub->texture_door.bpp, &cub->texture_door.size_line,
			&cub->texture_door.endian);
}

