/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 09:56:14 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/20 10:38:41 by aaggoujj         ###   ########.fr       */
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

void	render(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == '1')
			{
				cub->img = mlx_new_image(cub->mlx, BLOCK_SIZE, BLOCK_SIZE);
				put_pixel(255, 255, 255, cub);
				mlx_image_to_window(cub->mlx, cub->img,
					j * BLOCK_SIZE, i * BLOCK_SIZE);
			}
			j++;
		}
		i++;
	}
}

void	update(void	*param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	render(cub);
}

void	begin_cub(t_cub *cub)
{
	cub->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D", _true);
	cub->img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	mlx_key_hook(cub->mlx, &key_esc, cub);
	mlx_loop_hook(cub->mlx, &update, cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
}
