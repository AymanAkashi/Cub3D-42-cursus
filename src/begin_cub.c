/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 09:56:14 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/11/10 19:54:48 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	get_win_size(t_cub *cub)
{
	int	i;
	int	j;
	int	max_width;

	i = 0;
	max_width = 0;
	while (cub && cub->map[i])
		i++;
	cub->tab = ft_calloc(i, sizeof(int));
	i = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j] && cub->map[i][j] != '\n')
			j++;
		cub->tab[i] = j;
		if (j > max_width)
			max_width = j;
		i++;
	}
	cub->win_width = max_width * BLOCK_SIZE;
	cub->win_height = i * BLOCK_SIZE;
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

void	set_image(t_compass *list, t_cub *cub)
{
	t_compass	*tmp;

	tmp = list;
	while (tmp)
	{
		open_image(cub, tmp);
		tmp = tmp->next;
	}
}

int	init_input(int key, void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (key == KEY_ESCAPE)
		end_game(cub);
	if (key == KEY_ENTER)
		hook_start(cub);
	return (0);
}

int	init_game(t_cub *cub)
{
	void	*image;
	int		width;
	int		height;

	height = WIN_HEIGHT / 2;
	width = WIN_WIDTH;
	image = mlx_xpm_file_to_image(cub->mlx, "textures/play2.xpm",
			&width, &height);
	if (image == NULL)
	{
		(red(), printf("Cube3D: Error file doesn't open\n"), reset());
		exit(1);
	}
	mlx_put_image_to_window(cub->mlx, cub->win, image, 0, 0);
	mlx_hook(cub->win, 02, 0, init_input, cub);
	if (mlx_mouse_hook(cub->win, mouse_start, cub) == 0)
		return (1);
	return (0);
}

void	begin_cub(t_cub *cub)
{
	int	width;
	int	height;

	width = WIN_WIDTH;
	height = WIN_HEIGHT / 2;
	get_win_size(cub);
	set_angle(cub);
	set_door(cub);
	cub->color_cell = create_trgb(0, cub->celling);
	cub->color_floor = create_trgb(0, cub->floor);
	cub->player->pos.x = cub->player->pos.x * BLOCK_SIZE + BLOCK_SIZE / 2;
	cub->player->pos.y = cub->player->pos.y * BLOCK_SIZE + BLOCK_SIZE / 2;
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	open_image_door(cub);
	set_image(cub->compass, cub);
	init_game(cub);
	mlx_loop(cub->mlx);
}
