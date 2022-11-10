/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 21:16:02 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/11/10 16:21:00 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_state	checking_state(float ray_angle, int check)
{
	if (check == 1)
	{
		if (ray_angle < 2 * M_PI && ray_angle > M_PI)
			return (facing_up);
		else
			return (facing_down);
	}
	else
	{
		if (ray_angle < 3 * M_PI / 2 && ray_angle > M_PI / 2)
			return (facing_left);
		else
			return (facing_right);
	}
}


t_bool	check_wall(int x, int y, t_cub *cub)
{
	int	tile_x;
	int	tile_y;

	if (x < 0 || x > cub->win_width || y < 0 || y > cub->win_height)
		return (_false);
	tile_x = floor(x / BLOCK_SIZE);
	tile_y = floor(y / BLOCK_SIZE);
	cub->rays->was_door = _false;
	cub->rays->x_door =	-1;
	cub->rays->y_door = -1;
	if (cub->map[tile_y] && tile_x < cub->tab[tile_y] &&(cub->map[tile_y][tile_x] == '1' || cub->map[tile_y][tile_x] == 'D'))
	{
		if (cub->map[tile_y][tile_x] == 'D')
		{
			cub->rays->was_door = _true;
			cub->rays->x_door =	tile_x;
			cub->rays->y_door = tile_y;
			cub->rays->was_open = _true;
		}
		return (_false);
	}
	return (_true);
}

void cast_ray(t_cub *cub, float ray_angle)
{
	t_pos	h_intersection;
	t_pos	v_intersection;

	h_intersection = check_horizontal(cub, ray_angle);
	v_intersection = check_vertical(cub, ray_angle);
	cub->rays->intersection = finding_distance(cub->player->pos, h_intersection,
		v_intersection, cub);
	cub->rays->distance = sqrt((cub->player->pos.x - cub->rays->intersection.x)
		* (cub->player->pos.x - cub->rays->intersection.x)
		+ (cub->player->pos.y - cub->rays->intersection.y)
		* (cub->player->pos.y - cub->rays->intersection.y));
}

t_texture search_color(t_cub *cub, t_type type)
{
	t_compass	*tmp;

	tmp = cub->compass;
	while (tmp)
	{
		if (tmp->type  == type)
			return (tmp->texture);
		tmp = tmp->next;
	}
	return (cub->compass->texture);
}

t_texture set_color(t_cub *cub)
{
	t_state state1;
	t_state state2;

	state1 = checking_state(cub->rays->ray_angle, 1);
	state2 = checking_state(cub->rays->ray_angle, 2);
	if (!cub->rays->was_hit_vertical && state1 == facing_up && state2 == facing_left)//north
		return (search_color(cub, NO));
	else if (!cub->rays->was_hit_vertical && state1 == facing_up && state2 == facing_right)//north
		return (search_color(cub, NO));
	else if (cub->rays->was_hit_vertical && state1 == facing_up && state2 == facing_right)//west
		return (search_color(cub, WE));
	else if (cub->rays->was_hit_vertical && state1 == facing_down && state2 == facing_right) // WEst
		return (search_color(cub, WE));
	else if (!cub->rays->was_hit_vertical && state1 == facing_down && state2 == facing_right)//south
		return (search_color(cub, SO));
	else if (!cub->rays->was_hit_vertical && state1 == facing_down && state2 == facing_left)//south
		return (search_color(cub, SO));
	else if (cub->rays->was_hit_vertical && state1 == facing_down && state2 == facing_left)//east
		return (search_color(cub, EA));
	return (search_color(cub, EA));
}

float	get_x_intersection(t_cub *cub)
{
	if (cub->rays->was_hit_vertical)
		return (cub->rays->intersection.y);
	else
		return (cub->rays->intersection.x);
}

t_bool	checking_door_open(t_door *door)
{
	t_door	*tmp;

	tmp = door;
	while (tmp)
	{
		if (tmp->is_open == _true)
			return (_true);
		tmp = tmp->next;
	}
	return (_false);
}

t_door	*get_door(t_door *door, int x, int y);

void	cast_all_rays(t_cub *cub)
{
	float		ray_angle;
	float		wallbottom;
	float		walltop;
	int			x;
	int			*color;
	t_texture	texture;

	cub->rays->index = 0;
	cub->player->rot_angle = normalize_angle(cub->player->rot_angle);
	ray_angle = normalize_angle(cub->player->rot_angle - (FOV_ANGLE / 2));
	cub->distance_proj_plane = (WIN_WIDTH / 2) / tan(FOV_ANGLE / 2);
	while (cub->rays->index <= NUM_RAYS)
	{
		cast_ray(cub, ray_angle);
		cub->rays->distance = cub->rays->distance * cos(ray_angle - cub->player->rot_angle);
		cub->wall_strip_height = (BLOCK_SIZE / cub->rays->distance) * cub->distance_proj_plane;
		walltop = (WIN_HEIGHT / 2) - (cub->wall_strip_height / 2);
		wallbottom = (WIN_HEIGHT / 2) + (cub->wall_strip_height / 2);
		if (walltop < 0 || walltop > WIN_HEIGHT)
		{
			walltop = 0;
			wallbottom = WIN_HEIGHT;
		}
		cub->rays->ray_angle = ray_angle;
		if (cub->rays->was_door && cub->rays->was_hit_vertical)
			texture = cub->texture_door;
		else
			texture = set_color(cub);
		cub->rays->x_texture = (get_x_intersection(cub) / BLOCK_SIZE) - floor(get_x_intersection(cub) / BLOCK_SIZE);
		cub->rays->x_texture *= texture.width;
		x =  (int)(cub->rays->x_texture);
		for(int y = walltop; y < wallbottom; y++)
		{
			int	dist_top = y + (cub->wall_strip_height / 2) - (WIN_HEIGHT / 2);
			cub->rays->y_texture = dist_top * ((float)texture.height / cub->wall_strip_height);
			color = (int *)(texture.addr +  cub->rays->y_texture * texture.size_line + x * (texture.bpp / 8));
			cub->x = cub->rays->index;
			cub->y = y;
			put_pixel(*color, cub);
		}
		ray_angle += FOV_ANGLE / NUM_RAYS;
		cub->rays->index++;
	}
}

void	draw_celling(t_cub *cub)
{
	int		i;
	int		j;

	i = 0;
	while (i < WIN_HEIGHT / 2)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			cub->x = j;
			cub->y = i;
			put_pixel(cub->color_cell, cub);
			j++;
		}
		i++;
	}
}

void	draw_floor(t_cub *cub)
{
	int		i;
	int		j;

	i = WIN_HEIGHT / 2;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			cub->x = j;
			cub->y = i;
			put_pixel(cub->color_floor, cub);
			j++;
		}
		i++;
	}
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
	draw_circle(cub, RADIUS_MAP, WIN_HEIGHT - RADIUS_MAP, 0x00000000);
	mlx_clear_window(cub->mlx, cub->win);
}
