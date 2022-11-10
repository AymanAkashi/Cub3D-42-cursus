/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 09:56:14 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/11/10 16:50:57 by aaggoujj         ###   ########.fr       */
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
	int	new_x;
	int	new_y;
	int	tile_x;
	int	tile_y;

	new_x = x - radius / 2;
	new_y = y - radius / 2;
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
	if (cub->map[tile_y] && (cub->map[tile_y][tile_x] == '1' || !check_circle(x,
			y, cub->player->radius, cub) || cub->map[tile_y][tile_x] == 'D'))
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

int	create_trgb(int t, t_color color)
{
	return (t << 24 | color._r << 16 | color._g << 8 | color._b);
}

int	mouse_click(int button, int x, int y, t_cub *cub)
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
	set_hide_mouse(KEY_Q, cub);
	mlx_hook(cub->win, 17, 0, end_game, cub);
	mlx_hook(cub->win, 02, 1L << 0, input, cub);
	mlx_hook(cub->win, 03, 1L << 1, input_release, cub);
	mlx_hook(cub->win, 06, 1L << 6, mouse_move, cub);
	mlx_mouse_hook(cub->win, mouse_click, cub);
	mlx_loop_hook(cub->mlx, loop, cub);
}

int	mouse_start(int button, int x, int y, t_cub *cub)
{
	int	width;
	int	height;

	width = WIN_WIDTH / 2;
	height = WIN_HEIGHT / 2;
	if (button == 1 && (x >= width - 200 && x <= width + 200)
		&& (y >= height - 100 && y <= height))
		hook_start(cub);
	if (button == 1 && (x >= width - 110 && x <= width + 110)
		&& (y >= height + 40 && y <= height + 80))
		end_game(cub);
	return (0);
}

int	mouse_init(t_cub *cub)
{
	if (mlx_mouse_hook(cub->win, mouse_start, cub) == 0)
		return (0);
	return (1);
}

void	open_image(t_cub *cub, t_compass *tmp)
{
	tmp->texture.img = mlx_xpm_file_to_image(cub->mlx, tmp->path,
			&tmp->texture.width, &tmp->texture.height);
	tmp->texture.addr = mlx_get_data_addr(tmp->texture.img,
			&tmp->texture.bpp, &tmp->texture.size_line, &tmp->texture.endian);
	if (!tmp->texture.img)
	{
		(red(), printf("Cube3D: Error file doesn't open\n"), reset());
		exit(1);
	}
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

void	set_door(t_cub *cub)
{
	t_door	*tmp;
	int		i;
	int		j;
	int		index;

	i = 0;
	index = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == 'D')
			{
				tmp = ft_door_new(index++, j, i);
				ft_door_add_back(&cub->door, tmp);
			}
			j++;
		}
		i++;
	}
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
