/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 21:13:43 by aaggoujj          #+#    #+#             */
/*   Updated: 2023/12/18 13:57:10 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MacTypes.h>
#include <assert.h>
#include "../include/cub3d.h"

void	hook_start(t_cub *cub)
{
	int width;
	int height;

	cub->img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	cub->addr = (unsigned int *) mlx_get_data_addr(cub->img, &cub->bpp,
			&cub->size_line, &cub->endian);
	cub->weopon = mlx_xpm_file_to_image(cub->mlx, "textures/ak47.xpm",
			&width, &height);
	cub->zoomWeapon = mlx_xpm_file_to_image(cub->mlx, "textures/zoomAk47.xpm",
			&width, &height);
	cub->scop = mlx_xpm_file_to_image(cub->mlx, "textures/scop.xpm",
			&width, &height);


	if (!cub->weopon || !cub->zoomWeapon || !cub->scop)
	{
		(red(), printf("Cube3D: Error file doesn't open\n"), reset());
		exit(EXIT_FAILURE);
	}
	cub->defaultWeapon = cub->weopon;
	cub->compass_img = mlx_xpm_file_to_image(cub->mlx, "textures/compass.xpm",
			&width, &height);
	if (!cub->compass_img)
	{
		(red(), printf("Cube3D: Error file doesn't open\n"), reset());
		exit(EXIT_FAILURE);
	}
	set_hide_mouse(KEY_Q, cub);
	mlx_hook(cub->win, 17, 0, see_you_later, cub);
	mlx_hook(cub->win, 02, 0, input, cub);
	mlx_hook(cub->win, 03, 0, input_release, cub);
	mlx_hook(cub->win, 06, 0, mouse_move, cub);
	mlx_mouse_hook(cub->win, mouse_click, cub);
	mlx_loop_hook(cub->mlx, loop, cub);
}

void	line_draw(int x, int y, int width, int height, int color, t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			cub->x = x + j;
			cub->y = y + i;
			put_pixel(color, cub);
			j++;
		}
		i++;
	}
}


int	loop(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	render(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->compass_img, 0, WIN_HEIGHT - 180);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->defaultWeapon, WIN_WIDTH/2 - 580/2, WIN_HEIGHT - 350 + cub->pos_weapon);
	if (cub->defaultWeapon == cub->zoomWeapon){
		mlx_put_image_to_window(cub->mlx, cub->win, cub->scop, WIN_WIDTH/2 - 35, WIN_HEIGHT/2 - 35);
	}
	return (EXIT_SUCCESS);
}
