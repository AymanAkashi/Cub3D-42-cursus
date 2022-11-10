/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:46:12 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/11/10 19:47:05 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>


t_bool	check_circle_next(int x, int y, int radius, t_cub *cub)
{
	int	new_x;
	int	new_y;
	int	tile_x;
	int	tile_y;

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
	return (check_circle_next(x, y, radius, cub));
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