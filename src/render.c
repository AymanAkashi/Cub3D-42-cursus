/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 21:16:02 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/11/05 11:03:03 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_state	checking_state(double ray_angle, int check)
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
	if (cub->map[tile_y] && (cub->map[tile_y][tile_x] == '1'))
		return (_false);
	tile_x = floor((x - 1) / BLOCK_SIZE);
	tile_y = floor(y / BLOCK_SIZE);
	if (cub->map[tile_y] && (cub->map[tile_y][tile_x] == '1'))
		return (_false);
	tile_x = floor(x / BLOCK_SIZE);
	tile_y = floor((y - 1) / BLOCK_SIZE);
	if (cub->map[tile_y] && (cub->map[tile_y][tile_x] == '1'))
		return (_false);
	tile_x = floor((x + 1) / BLOCK_SIZE);
	tile_y = floor(y / BLOCK_SIZE);
	if (cub->map[tile_y] && (cub->map[tile_y][tile_x] == '1'))
		return (_false);
	tile_x = floor(x / BLOCK_SIZE);
	tile_y = floor((y + 1) / BLOCK_SIZE);
	if (cub->map[tile_y] && (cub->map[tile_y][tile_x] == '1'))
		return (_false);
	return (_true);
}

t_pos	check_vertical(t_cub *cub, double ray_angle)
{
	double	x_intercept;
	double	y_intercept;
	double	x_step;
	double	y_step;

	x_intercept = floor(cub->player->pos.x / BLOCK_SIZE) * BLOCK_SIZE;
	cub->rays->state = checking_state(ray_angle, 2);
	if (cub->rays->state == facing_right)
		x_intercept += BLOCK_SIZE;
	else
		x_intercept -= 1;
	y_intercept = cub->player->pos.y + (x_intercept - cub->player->pos.x) * tan(ray_angle);
	x_step = BLOCK_SIZE;
	if (cub->rays->state == facing_left)
		x_step *= -1;
	y_step = fabs(BLOCK_SIZE * tan(ray_angle));
	if (ray_angle < 2 * M_PI && ray_angle > M_PI)
		y_step *= -1;
	while(1)
	{
		if (!check_wall(x_intercept, y_intercept, cub))
			break ;
		x_intercept += x_step;
		y_intercept += y_step;
	}
	return ((t_pos){x_intercept, y_intercept});
}

t_pos	check_horizontal(t_cub *cub, double ray_angle)
{
	double	x_intercept;
	double	y_intercept;
	double	x_step;
	double	y_step;

	y_intercept = floor(cub->player->pos.y / BLOCK_SIZE) * BLOCK_SIZE;
	cub->rays->state = checking_state(ray_angle, 1);
	if (cub->rays->state == facing_down)
		y_intercept += BLOCK_SIZE;
	else
		y_intercept -= 1;
	x_intercept = cub->player->pos.x + (y_intercept - cub->player->pos.y) / tan(ray_angle);
	y_step = BLOCK_SIZE;
	if (cub->rays->state == facing_up)
		y_step *= -1;
	x_step = fabs(BLOCK_SIZE / tan(ray_angle));
	if (ray_angle > M_PI/2 && ray_angle < 3 * M_PI/2)
		x_step *= -1;
	while (1)
	{
		if (!check_wall(x_intercept, y_intercept, cub))
			break ;
		x_intercept += x_step;
		y_intercept += y_step;
	}
	return ((t_pos){x_intercept, y_intercept});
}

t_pos	finding_distance(t_pos p, t_pos h_p, t_pos v_p)
{
	double	h_dist;
	double	v_dist;

	h_dist = sqrt((p.x - h_p.x) * (p.x - h_p.x) + (p.y - h_p.y) * (p.y - h_p.y));
	v_dist = sqrt((p.x - v_p.x) * (p.x - v_p.x) + (p.y - v_p.y) * (p.y - v_p.y));
	if (h_dist < v_dist)
		return (h_p);
	else
		return (v_p);
}

double normalize_angle(double angle)
{
	if (angle < 0)
		angle = angle + (2 * M_PI);
	if (angle >= 2 * M_PI)
		angle = angle - (2 * M_PI);
	return (angle);
}

void cast_ray(t_cub *cub, double ray_angle)
{
	t_pos	pos_wall;
	t_pos	h_intersection;
	t_pos	v_intersection;

	h_intersection = check_horizontal(cub, ray_angle);
	v_intersection = check_vertical(cub, ray_angle);
	pos_wall = finding_distance(cub->player->pos, h_intersection, v_intersection);
	cub->rays->wall_hit_x = pos_wall.x;
	cub->rays->wall_hit_y = pos_wall.y;
	cub->rays->distance = sqrt((cub->player->pos.x - pos_wall.x) * (cub->player->pos.x - pos_wall.x) + (cub->player->pos.y - pos_wall.y) * (cub->player->pos.y - pos_wall.y));
}

void	cast_all_rays(t_cub *cub, int x, int y)
{
	int		i;
	int		column_id;
	double	ray_angle;

	(void)x;
	(void)y;
	i = 0;
	column_id = 0;
	cub->player->rot_angle = normalize_angle(cub->player->rot_angle);
	ray_angle = normalize_angle(cub->player->rot_angle - (FOV_ANGLE / 2));
	cub->distance_proj_plane = (WIN_WIDTH / 2) / tan(FOV_ANGLE / 2);
	while (i < NUM_RAYS)
	{
		cast_ray(cub, ray_angle);
		cub->rays->distance = cub->rays->distance * cos(ray_angle - cub->player->rot_angle);
		cub->wall_strip_height = (BLOCK_SIZE / cub->rays->distance) * cub->distance_proj_plane;
		dda(cub, (t_pos){i, WIN_HEIGHT/2}, (t_pos){i, WIN_HEIGHT/2 - cub->wall_strip_height/2}, 0x00FF0000);
		dda(cub, (t_pos){i, WIN_HEIGHT/2}, (t_pos){i, WIN_HEIGHT/2 + cub->wall_strip_height/2}, 0x00FF0000);
		ray_angle += FOV_ANGLE / NUM_RAYS;
		column_id++;
		i++;
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
	cast_all_rays(cub, x, y);
	draw_circle(cub, RADIUS_MAP, WIN_HEIGHT - RADIUS_MAP, 0x00000000);
	mlx_clear_window(cub->mlx, cub->win);
}
