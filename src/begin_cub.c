/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 09:56:14 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/11/04 17:36:51 by moseddik         ###   ########.fr       */
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

	radius = radius * 2 / 3;
	new_x = x - radius;
	new_y = y - radius;
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

void	begin_cub(t_cub *cub)
{
	get_win_size(cub);
	set_angle(cub);
	cub->color_cell = create_trgb(0, cub->celling);
	cub->color_floor = create_trgb(0, cub->floor);
	cub->player->pos.x *= BLOCK_SIZE;
	cub->player->pos.y *= BLOCK_SIZE;
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	cub->img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	cub->addr = (unsigned int *) mlx_get_data_addr(cub->img, &cub->bpp,
			&cub->size_line, &cub->endian);
	mlx_hook(cub->win, 17, 0, end_game, cub);
	mlx_hook(cub->win, 02, 1L << 0, input, cub);
	mlx_hook(cub->win, 03, 1L << 1, input_release, cub);
	mlx_loop_hook(cub->mlx, loop, cub);
	mlx_loop(cub->mlx);
}
