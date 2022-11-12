/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 21:13:43 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/11/12 13:15:10 by moseddik         ###   ########.fr       */
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

void	hook_start(t_cub *cub)
{
	cub->img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	cub->addr = (unsigned int *) mlx_get_data_addr(cub->img, &cub->bpp,
			&cub->size_line, &cub->endian);
	set_hide_mouse(KEY_Q, cub);
	mlx_hook(cub->win, 17, 0, end_game, cub);
	mlx_hook(cub->win, 02, 1L << 0, input, cub);
	mlx_hook(cub->win, 03, 1L << 1, input_release, cub);
	mlx_hook(cub->win, 06, 1L << 6, mouse_move, cub);
	mlx_mouse_hook(cub->win, mouse_click, cub);
	mlx_loop_hook(cub->mlx, loop, cub);
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
