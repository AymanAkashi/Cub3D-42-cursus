/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 21:13:43 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/11/10 17:40:49 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	end_game(t_cub *cub)
{
	mlx_clear_window(cub->mlx, cub->win);
	mlx_destroy_window(cub->mlx, cub->win);
	free_data(cub);
	(yellow(), printf("See you Later :) \n"), reset());
	exit(EXIT_SUCCESS);
}

int	loop(void *param)
{
	t_cub	*cub;
	// int	widht;
	// int	height;

	// height = WIN_HEIGHT - 100;
	// widht = 0;
	cub = (t_cub *)param;
	render(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
	// void	*img;
	// img = mlx_xpm_file_to_image(cub->mlx, "textures/map.xpm", &widht, &height);
	// mlx_put_image_to_window(cub->mlx, cub->win, img, 0, WIN_HEIGHT - 100);
	return (EXIT_SUCCESS);
}
