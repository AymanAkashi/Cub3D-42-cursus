/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 21:16:02 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/11/10 22:29:50 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_bool	check_wall(int x, int y, t_cub *cub)
{
	int	tile_x;
	int	tile_y;

	if (x < 0 || x > cub->win_width || y < 0 || y > cub->win_height)
		return (_false);
	tile_x = floor(x / BLOCK_SIZE);
	tile_y = floor(y / BLOCK_SIZE);
	cub->rays->was_door = _false;
	cub->rays->x_door = -1;
	cub->rays->y_door = -1;
	if (cub->map[tile_y] && tile_x < cub->tab[tile_y]
		&& (cub->map[tile_y][tile_x] == '1' || cub->map[tile_y][tile_x] == 'D'))
	{
		if (cub->map[tile_y][tile_x] == 'D')
		{
			cub->rays->was_door = _true;
			cub->rays->x_door = tile_x;
			cub->rays->y_door = tile_y;
			cub->rays->was_open = _true;
		}
		return (_false);
	}
	return (_true);
}

t_texture	search_color(t_cub *cub, t_type type)
{
	t_compass	*tmp;

	tmp = cub->compass;
	while (tmp)
	{
		if (tmp->type == type)
			return (tmp->texture);
		tmp = tmp->next;
	}
	return (cub->compass->texture);
}

t_texture	set_color_helper(t_cub *cub, t_state state1, t_state state2)
{
	if (!cub->rays->was_hit_vertical && state1 == facing_up
		&& state2 == facing_left)
		return (search_color(cub, NO));
	else if (!cub->rays->was_hit_vertical && state1 == facing_up
		&& state2 == facing_right)
		return (search_color(cub, NO));
	else if (cub->rays->was_hit_vertical && state1 == facing_up
		&& state2 == facing_right)
		return (search_color(cub, WE));
	else if (cub->rays->was_hit_vertical && state1 == facing_down
		&& state2 == facing_right)
		return (search_color(cub, WE));
	else if (!cub->rays->was_hit_vertical && state1 == facing_down
		&& state2 == facing_right)
		return (search_color(cub, SO));
	else if (!cub->rays->was_hit_vertical && state1 == facing_down
		&& state2 == facing_left)
		return (search_color(cub, SO));
	else if (cub->rays->was_hit_vertical && state1 == facing_down
		&& state2 == facing_left)
		return (search_color(cub, EA));
	return (search_color(cub, EA));
}

t_texture	set_color(t_cub *cub)
{
	t_state	state1;
	t_state	state2;

	state1 = checking_state(cub->rays->ray_angle, 1);
	state2 = checking_state(cub->rays->ray_angle, 2);
	return (set_color_helper(cub, state1, state2));
}

void	render(t_cub *cub)
{
	int	x;
	int	y;

	x = cub->player->pos.x;
	y = cub->player->pos.y;
	update_player(cub->player, cub);
	draw_celling(cub);
	draw_floor(cub);
	cast_all_rays(cub);
	draw_circle(cub, RADIUS_M, WIN_HEIGHT - RADIUS_M, 0x00000000);
	mlx_clear_window(cub->mlx, cub->win);
}
