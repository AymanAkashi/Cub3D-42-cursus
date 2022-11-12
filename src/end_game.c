/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:31:28 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/11/12 16:57:12 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	get_image_next(t_cub *cub, int *imgs, void	**img, int width)
{
	int	height;

	if ((*imgs) == 6)
		(*img) = mlx_xpm_file_to_image(cub->mlx, "textures/endgame/end7.xpm",
				&width, &height);
	else if ((*imgs) == 7)
		(*img) = mlx_xpm_file_to_image(cub->mlx, "textures/endgame/end10.xpm",
				&width, &height);
	else if ((*imgs) == 8)
		(*img) = mlx_xpm_file_to_image(cub->mlx, "textures/endgame/end11.xpm",
				&width, &height);
	else if ((*imgs) == 9)
		(*img) = mlx_xpm_file_to_image(cub->mlx, "textures/endgame/end14.xpm",
				&width, &height);
	else if ((*imgs) == 10)
		(*img) = mlx_xpm_file_to_image(cub->mlx, "textures/endgame/end16.xpm",
				&width, &height);
	else if ((*imgs) == 11)
		(*img) = mlx_xpm_file_to_image(cub->mlx, "textures/endgame/end17.xpm",
				&width, &height);
	else if ((*imgs) == 12)
		(*img) = mlx_xpm_file_to_image(cub->mlx, "textures/endgame/end19.xpm",
				&width, &height);
}

void	get_image(t_cub *cub, int *imgs, void	**img)
{
	int	width;
	int	height;

	width = 0;
	if ((*imgs) == 0)
		(*img) = mlx_xpm_file_to_image(cub->mlx, "textures/endgame/end1.xpm",
				&width, &height);
	else if ((*imgs) == 1)
		(*img) = mlx_xpm_file_to_image(cub->mlx, "textures/endgame/end2.xpm",
				&width, &height);
	else if ((*imgs) == 2)
		(*img) = mlx_xpm_file_to_image(cub->mlx, "textures/endgame/end3.xpm",
				&width, &height);
	else if ((*imgs) == 3)
		(*img) = mlx_xpm_file_to_image(cub->mlx, "textures/endgame/end4.xpm",
				&width, &height);
	else if ((*imgs) == 4)
		(*img) = mlx_xpm_file_to_image(cub->mlx, "textures/endgame/end5.xpm",
				&width, &height);
	else if ((*imgs) == 5)
		(*img) = mlx_xpm_file_to_image(cub->mlx, "textures/endgame/end6.xpm",
				&width, &height);
	else
		get_image_next(cub, imgs, img, width);
}

int	see_you_later(t_cub *cub)
{
	mlx_clear_window(cub->mlx, cub->win);
	mlx_destroy_window(cub->mlx, cub->win);
	free_data(cub);
	(yellow(), printf("See you Later :) \n"), reset());
	exit(EXIT_SUCCESS);
}

int	sprite_endgame(t_cub *cub)
{
	static int	imgs;
	static int	frames;
	void		*img;

	img = NULL;
	if (imgs == 12)
	{
		sleep (1);
		see_you_later(cub);
	}
	if (frames == 0)
	{
		frames = 6;
		imgs++;
	}
	get_image(cub, &imgs, &img);
	frames--;
	if (imgs <= 12 && img)
	{
		mlx_clear_window(cub->mlx, cub->win);
		mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
		mlx_put_image_to_window(cub->mlx, cub->win, img, WIN_WIDTH / 2,
			WIN_HEIGHT / 2);
	}
	return (EXIT_SUCCESS);
}

int	end_game(t_cub *cub)
{
	int	width;
	int	height;

	cub->img = mlx_xpm_file_to_image(cub->mlx, "textures/endgame/bg.xpm",
			&width, &height);
	if (!cub->img)
	{
		(red(), printf("Cube3D: Error file doesn't open\n"), reset());
		return (EXIT_FAILURE);
	}
	mlx_loop_hook(cub->mlx, sprite_endgame, cub);
	return (EXIT_SUCCESS);
}
