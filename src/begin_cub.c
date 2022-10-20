/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 09:56:14 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/20 09:56:45 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	put_pixel(size_t r, size_t g, size_t b, t_cub *cub)
{
	size_t	i;

	i = 0;
	while (i < cub->img->width * cub->img->height * sizeof(int))
	{
		cub->img->pixels[i] = r;
		cub->img->pixels[i + 1] = g;
		cub->img->pixels[i + 2] = b;
		cub->img->pixels[i + 3] = 255;
		i += sizeof(int);
	}
}

void	begin_cub(t_cub *cub)
{
	cub->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D", _true);
	cub->img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	mlx_loop(cub->mlx);
}