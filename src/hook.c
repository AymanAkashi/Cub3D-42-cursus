/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 21:13:43 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/12/27 01:22:57 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	hook_start(t_cub *cub)
{
	cub->img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	cub->addr = (unsigned int *) mlx_get_data_addr(cub->img, &cub->bpp,
			&cub->size_line, &cub->endian);
	set_hide_mouse(KEY_Q, cub);
	mlx_hook(cub->win, 17, 0, see_you_later, cub);
	mlx_hook(cub->win, 02, 1L<<0, input, cub);
	mlx_hook(cub->win, 03, 1L<<1, input_release, cub);
	mlx_hook(cub->win, 6, 1L<<6, mouse_move, cub);
	mlx_mouse_hook(cub->win, mouse_click, cub);
	mlx_loop_hook(cub->mlx, loop, cub);
	return (EXIT_SUCCESS);
}

int	loop(void *param)
{
	t_cub	*cub;
	
	cub = (t_cub *)param;
	render(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
	return (EXIT_SUCCESS);
}
