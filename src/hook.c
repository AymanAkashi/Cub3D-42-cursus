/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 21:13:43 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/25 21:53:59 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	end_game(t_cub *cub)
{
	mlx_clear_window(cub->mlx, cub->win);
	mlx_destroy_window(cub->mlx, cub->win);
	free_data(cub);
	exit(EXIT_SUCCESS);
}

int	loop(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	cub->img = mlx_new_image(cub->mlx, cub->win_width, cub->win_height);
	cub->addr = (unsigned int *) mlx_get_data_addr(cub->img, &cub->bpp,
			&cub->size_line, &cub->endian);
	render(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
	mlx_destroy_image(cub->mlx, cub->img);
	return (EXIT_SUCCESS);
}
