/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_draw_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:31:30 by moseddik          #+#    #+#             */
/*   Updated: 2023/12/18 15:01:39 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	dda(t_cub *cub, t_pos p0, t_pos p1, int color)
{
	t_DDA	dda;
	int		i;

	dda.dx = p1.x - p0.x;
	dda.dy = p1.y - p0.y;
	if (fabs(dda.dx) > fabs(dda.dy))
		dda.steps = fabs(dda.dx);
	else
		dda.steps = fabs(dda.dy);
	dda.xinc = dda.dx / (float)dda.steps;
	dda.yinc = dda.dy / (float)dda.steps;
	dda.x = p0.x;
	dda.y = p0.y;
	i = -1;
	while (++i <= dda.steps)
	{
		cub->x = round(dda.x);
		cub->y = round(dda.y);
		put_pixel(color, cub);
		dda.x += dda.xinc;
		dda.y += dda.yinc;
	}
}

void	update_player(t_player *player, t_cub *cub)
{
	int		move_step;
	int		move_side;
	float	new_x;
	float	new_y;

	player->rot_angle += player->turn_dir * player->rot_speed;
	move_side = player->walk_side * player->move_speed_side;
	move_step = player->walk_dir * player->move_speed;
	if (move_side)
	{
		new_x = player->pos.x + cos(player->rot_angle + M_PI / 2) * move_side;
		new_y = player->pos.y + sin(player->rot_angle + M_PI / 2) * move_side;
	}
	if (move_step)
	{
		new_x = player->pos.x + cos(player->rot_angle) * move_step;
		new_y = player->pos.y + sin(player->rot_angle) * move_step;
	}
	if (is_wall(new_x, new_y, cub))
	{
		player->pos.x = new_x;
		player->pos.y = new_y;
	}
}

void	draw_circle_player(t_cub *cub, int x, int y, int color)
{
	float	i;
	float	angle;
	float	x1;
	float	y1;

	i = 0;
	while (i < 360)
	{
		angle = i;
		x1 = 4 * cos(angle * M_PI / 180);
		y1 = 4 * sin(angle * M_PI / 180);
		if (x1 > 0)
			simple_draw_line((t_pos){x, y},
				(t_pos){x1, y1}, cub, (t_pos){1, color});
		else
			simple_draw_line((t_pos){x, y},
				(t_pos){x1, y1}, cub, (t_pos){-1, color});
		i += 0.1;
	}
}
