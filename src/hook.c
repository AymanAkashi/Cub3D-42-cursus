/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 21:13:43 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/11/12 16:57:01 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	hook_start(t_cub *cub)
{
	cub->img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	cub->addr = (unsigned int *) mlx_get_data_addr(cub->img, &cub->bpp,
			&cub->size_line, &cub->endian);
	set_hide_mouse(KEY_Q, cub);
	mlx_hook(cub->win, 17, 0, see_you_later, cub);
	mlx_hook(cub->win, 02, 0, input, cub);
	mlx_hook(cub->win, 03, 0, input_release, cub);
	mlx_hook(cub->win, 06, 0, mouse_move, cub);
	mlx_mouse_hook(cub->win, mouse_click, cub);
	mlx_loop_hook(cub->mlx, loop, cub);
}

int	loop(void *param)
{
	t_cub	*cub;
	int		width;
	int		height;
	void	*img;

	width = 180;
	height = 180;
	cub = (t_cub *)param;
	render(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
	img = mlx_xpm_file_to_image(cub->mlx, "textures/compass.xpm",
			&width, &height);
	if (!img)
	{
		(red(), printf("Cube3D: Error file doesn't open\n"), reset());
		exit(EXIT_FAILURE);
	}
	mlx_put_image_to_window(cub->mlx, cub->win, img, 0, WIN_HEIGHT - 180);
	return (EXIT_SUCCESS);
}
