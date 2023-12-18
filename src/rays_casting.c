/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_casting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 07:35:08 by aaggoujj          #+#    #+#             */
/*   Updated: 2023/12/18 13:57:10 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_vertical_next(t_hit_pos *hit, t_cub *cub, float ray_angle)
{
	hit->x_intercept = floor(cub->player->pos.x / BLOCK_SIZE) * BLOCK_SIZE;
	cub->rays->state = checking_state(ray_angle, 2);
	if (cub->rays->state == facing_right)
		hit->x_intercept += BLOCK_SIZE;
	hit->y_intercept = cub->player->pos.y + (hit->x_intercept
			- cub->player->pos.x) * tan(ray_angle);
	hit->x_step = BLOCK_SIZE;
	if (cub->rays->state == facing_left)
		hit->x_step *= -1;
	hit->y_step = fabs(BLOCK_SIZE * tan(ray_angle));
	if (checking_state(ray_angle, 1) == facing_up)
		hit->y_step *= -1;
	hit->next_x = hit->x_intercept;
	hit->next_y = hit->y_intercept;
}

t_pos	check_vertical(t_cub *cub, float ray_angle)
{
	t_hit_pos	hit;

	if (ray_angle == M_PI_2 || ray_angle == 3 * M_PI_2)
		return ((t_pos){MAX_INT, MAX_INT});
	check_vertical_next(&hit, cub, ray_angle);
	while (hit.next_x >= 0 && hit.next_x <= cub->win_width
		&& hit.next_y >= 0 && hit.next_y <= cub->win_height)
	{
		hit.x_to_check = hit.next_x;
		if (cub->rays->state == facing_left)
			hit.x_to_check = hit.next_x - 1;
		hit.y_to_check = hit.next_y;
		if (!check_wall(hit.x_to_check, hit.y_to_check, cub))
		{
			hit.wall_hit_x = hit.next_x;
			hit.wall_hit_y = hit.next_y;
			break ;
		}
		hit.next_x += hit.x_step;
		hit.next_y += hit.y_step;
	}
	return ((t_pos){hit.next_x, hit.next_y});
}

void	check_horizontal_next(t_hit_pos *hit, t_cub *cub, float ray_angle)
{
	hit->y_intercept = floor(cub->player->pos.y / BLOCK_SIZE) * BLOCK_SIZE;
	cub->rays->state = checking_state(ray_angle, 1);
	if (cub->rays->state == facing_down)
		hit->y_intercept += BLOCK_SIZE;
	hit->x_intercept = cub->player->pos.x + (hit->y_intercept
			- cub->player->pos.y) / tan(ray_angle);
	hit->y_step = BLOCK_SIZE;
	if (cub->rays->state == facing_up)
		hit->y_step *= -1;
	hit->x_step = fabs(BLOCK_SIZE / tan(ray_angle));
	if (checking_state(ray_angle, 2) == facing_left)
		hit->x_step *= -1;
	hit->next_x = hit->x_intercept;
	hit->next_y = hit->y_intercept;
}

t_pos	check_horizontal(t_cub *cub, float ray_angle)
{
	t_hit_pos	hit;

	if (ray_angle == 0 || ray_angle == M_PI)
		return ((t_pos){MAX_INT, MAX_INT});
	check_horizontal_next(&hit, cub, ray_angle);
	while (hit.next_x >= 0 && hit.next_x <= cub->win_width
		&& hit.next_y >= 0 && hit.next_y <= cub->win_height)
	{
		hit.x_to_check = hit.next_x;
		hit.y_to_check = hit.next_y;
		if (cub->rays->state == facing_up)
			hit.y_to_check = hit.next_y - 1;
		if (!check_wall(hit.x_to_check, hit.y_to_check, cub))
		{
			hit.wall_hit_x = hit.next_x;
			hit.wall_hit_y = hit.next_y;
			break ;
		}
		hit.next_x += hit.x_step;
		hit.next_y += hit.y_step;
	}
	return ((t_pos){hit.next_x, hit.next_y});
}

t_pos	finding_distance(t_pos p, t_pos h_p, t_pos v_p, t_cub *cub)
{
	float	h_dist;
	float	v_dist;
	float	ebsilon;

	ebsilon = 0.0001;
	h_dist = sqrt((p.x - h_p.x) *(p.x - h_p.x) + (p.y - h_p.y) * (p.y - h_p.y));
	v_dist = sqrt((p.x - v_p.x) *(p.x - v_p.x) + (p.y - v_p.y) * (p.y - v_p.y));
	if (h_dist - v_dist <= ebsilon)
	{
		cub->rays->was_hit_vertical = _false;
		return (h_p);
	}
	else
	{
		cub->rays->was_hit_vertical = _true;
		return (v_p);
	}
}
