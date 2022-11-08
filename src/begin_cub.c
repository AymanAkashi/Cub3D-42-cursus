/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 09:56:14 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/11/08 13:32:51 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	put_pixel(int color, t_cub *cub)
{
	if (cub->y < WIN_HEIGHT && cub->x < WIN_WIDTH && cub->y >= 0 && cub->x >= 0)
	cub->addr[(int)cub->y * WIN_WIDTH + (int)cub->x] = color;
}

t_bool	check_circle(int x, int y, int radius, t_cub *cub)
{
	int new_x;
	int new_y;
	int	tile_x;
	int	tile_y;

	new_x = x - radius/2;
	new_y = y - radius/2;
	tile_x = floor(new_x / BLOCK_SIZE);
	tile_y = floor(new_y / BLOCK_SIZE);
	if (cub->map[tile_y] && cub->map[tile_y][tile_x] == '1')
		return (_false);
	new_x = x + radius;
	new_y = y + radius;
	tile_x = floor(new_x / BLOCK_SIZE);
	tile_y = floor(new_y / BLOCK_SIZE);
	if (cub->map[tile_y] && cub->map[tile_y][tile_x] == '1')
		return (_false);
	new_x = x + radius;
	new_y = y - radius;
	tile_x = floor(new_x / BLOCK_SIZE);
	tile_y = floor(new_y / BLOCK_SIZE);
	if (cub->map[tile_y] && cub->map[tile_y][tile_x] == '1')
		return (_false);
	new_x = x - radius;
	new_y = y + radius;
	tile_x = floor(new_x / BLOCK_SIZE);
	tile_y = floor(new_y / BLOCK_SIZE);
	if (cub->map[tile_y] && cub->map[tile_y][tile_x] == '1')
		return (_false);
	return (_true);
}

t_bool	is_wall(int x, int y, t_cub *cub)
{
	int	tile_x;
	int	tile_y;

	if (x < 0 || x > cub->win_width || y < 0 || y > cub->win_height)
		return (_false);
	tile_x = floor(x / BLOCK_SIZE);
	tile_y = floor(y / BLOCK_SIZE);
	if (cub->map[tile_y] && (cub->map[tile_y][tile_x] == '1' || !check_circle(x, y, cub->player->radius, cub)))
		return (_false);
	return (_true);
}

void	get_win_size(t_cub *cub)
{
	int	i;
	int	j;
	int	max_width;

	i = 0;
	max_width = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
			j++;
		if (j > max_width)
			max_width = j;
		i++;
	}
	cub->win_width = (max_width - 1) * BLOCK_SIZE;
	cub->win_height = i * BLOCK_SIZE;
}

int	create_trgb(int t, t_color color)
{
	return (t << 24 | color._r << 16 | color._g << 8 | color._b);
}

int mouse_click(int button, int x, int y, t_cub *cub)
{
	(void)x;
	(void)y;
	if (button == 1 && !cub->mouse_hide)
	{
		mlx_mouse_hide();
		cub->mouse_hide = _true;
	}
	return (0);
}

void	hook_start(t_cub *cub)
{
	cub->img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	cub->addr = (unsigned int *) mlx_get_data_addr(cub->img, &cub->bpp,
			&cub->size_line, &cub->endian);
	set_hide_mouse(KEY_Q,cub);
	mlx_hook(cub->win, 17, 0, end_game, cub);
	mlx_hook(cub->win, 02, 1L << 0, input, cub);
	mlx_hook(cub->win, 03, 1L << 1, input_release, cub);
	mlx_hook(cub->win, 06, 1L << 6, mouse_move, cub);
	mlx_mouse_hook(cub->win, mouse_click, cub);
	mlx_loop_hook(cub->mlx, loop, cub);
}

int mouse_start(int button, int x, int y, t_cub *cub)
{
	int width;
	int height;

	width = WIN_WIDTH / 2;
	height = WIN_HEIGHT / 2;
	if (button == 1 && (x >= width - 200 && x <= width + 200) && (y >= height - 100 && y <= height))
	{
		hook_start(cub);
	}
	if (button == 1 && (x >= width - 110 && x <= width + 110) && (y >= height + 40  && y <= height + 80))
	{
		end_game(cub);
	}
	return (0);
}

int mouse_init(t_cub *cub)
{
	if (mlx_mouse_hook(cub->win, mouse_start, cub) == 0)
		return (0);
	return (1);
}

void	open_image(t_cub *cub, t_compass *tmp)
{
	tmp->img = mlx_xpm_file_to_image(cub->mlx, tmp->path, &cub->compass->width, &cub->compass->height);
	if (!tmp->img)
	{
		red();printf("Cube3D: Error file doesn't open\n");reset();
		exit(1);
	}
}

void	set_image(t_compass *list, t_cub *cub)
{
	t_compass	*tmp;

	tmp = list;
	while(tmp)
	{
		open_image(cub, tmp);
		tmp = tmp->next;
	}
}

int	init_game(t_cub *cub)
{
	void	*img;
	void	*image;
	int     width;
	int     height;

	height = 0;
	width = 0;
	img	= mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	image = mlx_xpm_file_to_image(cub->mlx, "textures/play.xpm", &width, &height);
	mlx_put_image_to_window(cub->mlx, cub->win, image, 0, 0);
	mlx_hook(cub->win, 02, 0, input, cub);
	if (mlx_mouse_hook(cub->win, mouse_start, cub) == 0)
		return (1);
	return (0);
}

void	begin_cub(t_cub *cub)
{
	get_win_size(cub);
	set_angle(cub);
	cub->color_cell = create_trgb(0, cub->celling);
	cub->color_floor = create_trgb(0, cub->floor);
	cub->player->pos.x = cub->player->pos.x * BLOCK_SIZE + BLOCK_SIZE / 2;
	cub->player->pos.y = cub->player->pos.y * BLOCK_SIZE + BLOCK_SIZE / 2;
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	set_image(cub->compass, cub);
	init_game(cub);
	mlx_loop(cub->mlx);
}
