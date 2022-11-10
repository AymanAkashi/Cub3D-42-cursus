/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_casting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 07:35:08 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/11/10 15:03:42 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_pos	check_vertical(t_cub *cub, float ray_angle)
{
	float	x_intercept;
	float	y_intercept;
	float	x_step;
	float	y_step;
	float  vertical_wall_hit_x;
	float  vertical_wall_hit_y;

	if (ray_angle == M_PI / 2 || ray_angle == 3 * M_PI / 2)
		return ((t_pos){MAX_INT, MAX_INT});
	x_intercept = floor(cub->player->pos.x / BLOCK_SIZE) * BLOCK_SIZE;
	cub->rays->state = checking_state(ray_angle, 2);
	if (cub->rays->state == facing_right)
		x_intercept += BLOCK_SIZE;
	y_intercept = cub->player->pos.y + (x_intercept - cub->player->pos.x) * tan(ray_angle);
	x_step = BLOCK_SIZE;
	if (cub->rays->state == facing_left)
		x_step *= -1;
	y_step = fabs(BLOCK_SIZE * tan(ray_angle));
	if (checking_state(ray_angle, 1) == facing_up)
		y_step *= -1;
	float next_vert_x = x_intercept;
	float next_vert_y = y_intercept;
	while(next_vert_x >= 0 && next_vert_x <= cub->win_width
		&& next_vert_y >= 0 && next_vert_y <= cub->win_height)
	{
		float x_to_check = next_vert_x;
		if (cub->rays->state == facing_left)
			x_to_check = next_vert_x - 1;
		float y_to_check = next_vert_y;
		if (!check_wall(x_to_check, y_to_check, cub))
		{
			vertical_wall_hit_x = next_vert_x;
			vertical_wall_hit_y = next_vert_y;
			break;
		}
		next_vert_x += x_step;
		next_vert_y += y_step;
	}
	return ((t_pos){next_vert_x, next_vert_y});
}

t_pos	check_horizontal(t_cub *cub, float ray_angle)
{
	float	x_intercept;
	float	y_intercept;
	float	x_step;
	float	y_step;
	float  horizontal_wall_hit_x;
	float  horizontal_wall_hit_y;

	if (ray_angle == 0 || ray_angle == M_PI)
		return ((t_pos){MAX_INT, MAX_INT});
	y_intercept = floor(cub->player->pos.y / BLOCK_SIZE) * BLOCK_SIZE;
	cub->rays->state = checking_state(ray_angle, 1);
	if (cub->rays->state == facing_down)
		y_intercept += BLOCK_SIZE;
	x_intercept = cub->player->pos.x + (y_intercept - cub->player->pos.y) / tan(ray_angle);
	y_step = BLOCK_SIZE;
	if (cub->rays->state == facing_up)
		y_step *= -1;
	x_step = fabs(BLOCK_SIZE / tan(ray_angle));
	if (checking_state(ray_angle, 2) == facing_left)
		x_step *= -1;
	float next_hor_x = x_intercept;
	float next_hor_y = y_intercept;
	while (next_hor_x >= 0 && next_hor_x <= cub->win_width
		&& next_hor_y >= 0 && next_hor_y <= cub->win_height)
	{
		float x_to_check = next_hor_x;
		float y_to_check = next_hor_y;
		if (cub->rays->state == facing_up)
			y_to_check = next_hor_y - 1;
		if (!check_wall(x_to_check, y_to_check, cub))
		{
			horizontal_wall_hit_x = next_hor_x;
			horizontal_wall_hit_y = next_hor_y;
			break ;
		}
		next_hor_x += x_step;
		next_hor_y += y_step;
	}
	return ((t_pos){next_hor_x, next_hor_y});
}

t_pos	finding_distance(t_pos p, t_pos h_p, t_pos v_p, t_cub *cub)
{
	float	h_dist;
	float	v_dist;
	float		ebsilon = 0.0001;

	h_dist = sqrt((p.x - h_p.x) * (p.x - h_p.x) + (p.y - h_p.y) * (p.y - h_p.y));
	v_dist = sqrt((p.x - v_p.x) * (p.x - v_p.x) + (p.y - v_p.y) * (p.y - v_p.y));
	if (h_dist - v_dist <= ebsilon)
	{
		cub->rays->was_hit_vertical = _false;
		return (h_p);
	}
	else
	{
		cub->rays->was_hit_vertical = _true;;
		return (v_p);
	}
}

float normalize_angle(float angle)
{
	angle = remainder(angle, (2 * M_PI));
	if (angle < 0)
		angle = angle + (2 * M_PI);
	return (angle);
}