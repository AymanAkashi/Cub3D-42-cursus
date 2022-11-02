/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 21:16:02 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/11/02 21:54:19 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_block(int x, int y, t_cub *cub, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < BLOCK_SIZE)
	{
		j = 0;
		while (j < BLOCK_SIZE)
		{
			cub->x = x + j;
			cub->y = y + i;
			if (i == 0 || j == 0)
				put_pixel(0x00000000, cub);
			else
				put_pixel(color, cub);
			j++;
		}
		i++;
	}
}

void	draw_walls(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == '1')
				draw_block(j * BLOCK_SIZE, i * BLOCK_SIZE, cub, 0x00000000);
			if (cub->map[i][j] == '0' || cub->map[i][j] == 'N' ||
				cub->map[i][j] == 'S' || cub->map[i][j] == 'E' ||
				cub->map[i][j] == 'W')
				draw_block(j * BLOCK_SIZE, i * BLOCK_SIZE, cub, 0x00FFFFFF);
			j++;
		}
		i++;
	}
}

t_state	checking_state(double ray_angle)
{
	if (ray_angle < 2 * M_PI && ray_angle > M_PI)
		return (facing_up);
	else
		return (facing_down);
}

t_pos	check_horizontal(t_cub *cub, double ray_angle)
{
	double	x_intercept;
	double	y_intercept;
	double	x_step;
	double	y_step;

	y_intercept = floor(cub->player->pos.y / BLOCK_SIZE) * BLOCK_SIZE;
	cub->rays->state = checking_state(ray_angle);
	if (cub->rays->state == facing_down)
		y_intercept += BLOCK_SIZE;
	else
		y_intercept -= 1;
	x_intercept = cub->player->pos.x + fabs(y_intercept - cub->player->pos.y) / tan(ray_angle);
	y_step = BLOCK_SIZE;
	if (cub->rays->state == facing_up)
		y_step *= -1;
	x_step = fabs(y_step / tan(ray_angle));
	if (ray_angle > M_PI/2 && ray_angle < 3 * M_PI/2)
		x_step *= -1;
	while (1)
	{
		if (!is_wall(x_intercept, y_intercept, cub))
			break ;
		x_intercept += x_step;
		y_intercept += y_step;
	}
	return ((t_pos){x_intercept, y_intercept});
}

void cast_ray(t_cub *cub, double ray_angle)
{
	t_pos	h_intersection;

	h_intersection = check_horizontal(cub, ray_angle);
	cub->rays->wall_hit_x = h_intersection.x;
	cub->rays->wall_hit_y = h_intersection.y;
	// blue(), printf("h_intersection.x = %f h_intersection.y = %f\n", h_intersection.x, h_intersection.y),reset();
	// red(), printf("ray_angle = %f\n", ray_angle / (M_PI / 180)), reset();
}

double normalize_angle(double angle)
{
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	if (angle > 2 * M_PI)
		angle = angle - (2 * M_PI);
	return (angle);
}

void	cast_all_rays(t_cub *cub, int x, int y)
{
	int		i;
	int		column_id;
	double	ray_angle;

	i = 0;
	column_id = 0;
	ray_angle = cub->player->rot_angle - (FOV_ANGLE / 2);
	ray_angle = normalize_angle(ray_angle);
	// red(), printf("ray_angle = %f\n", ray_angle / (M_PI / 180)), reset();
	// printf("cub->player->pos_x = %f, cub->player->pos_y = %f\n", cub->player->pos.x, cub->player->pos.y);
	while (i < NUM_RAYS)
	{
		cast_ray(cub, ray_angle);
		dda(cub, (t_pos){x, y}, (t_pos){cub->rays->wall_hit_x, cub->rays->wall_hit_y}, 0x00FF0000);
		ray_angle += FOV_ANGLE / NUM_RAYS;
		column_id++;
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
	draw_walls(cub);
	draw_circle(cub, x, y, 0x00FF0000);
	cast_all_rays(cub, x, y);
	dda(cub, (t_pos){x, y}, (t_pos){x + cos(cub->player->rot_angle)
		* 150, y + sin(cub->player->rot_angle) * 150}, 0x00000000);
	mlx_clear_window(cub->mlx, cub->win);
}
