/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_casting_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 21:49:03 by moseddik          #+#    #+#             */
/*   Updated: 2023/12/18 14:00:33 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

float	normalize_angle(float angle)
{
	angle = remainder(angle, (2 * M_PI));
	if (angle < 0)
		angle = angle + (2 * M_PI);
	return (angle);
}

float	get_x_intersection(t_cub *cub)
{
	if (cub->rays->was_hit_vertical)
		return (cub->rays->intersection.y);
	else
		return (cub->rays->intersection.x);
}

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

void	cast_ray(t_cub *cub, float ray_angle)
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

void	cast_all_rays(t_cub *cub)
{
	float		ray_angle;
	t_texture	texture	;

	cub->rays->index = 0;
	cub->player->rot_angle = normalize_angle(cub->player->rot_angle);
	ray_angle = normalize_angle(cub->player->rot_angle - (cub->fov_angle / 2));
	cub->distance_proj_plane = (WIN_WIDTH / 2) / tan(cub->fov_angle / 2);
	while (cub->rays->index <= NUM_RAYS)
	{
		cast_ray(cub, ray_angle);
		cub->rays->distance = cub->rays->distance
			* cos(ray_angle - cub->player->rot_angle);
		cub->wall_strip_height = (BLOCK_SIZE / cub->rays->distance)
			* cub->distance_proj_plane;
		cub->rays->ray_angle = ray_angle;
		if (cub->rays->was_door && cub->rays->was_hit_vertical)
			texture = cub->texture_door;
		else
			texture = set_color(cub);
		add_textures(cub, texture, cub->rays->distance);
		ray_angle += cub->fov_angle / NUM_RAYS;
		cub->rays->index++;
	}
}
