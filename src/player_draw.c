/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:08:41 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/25 22:10:06 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	simple_draw_line(t_pos pos, t_pos pos1, t_cub *cub, t_pos incr_color)
{
	int	j;

	j = 0;
	if (incr_color.x == 1)
	{
		while (j < pos1.x)
		{
			cub->x = pos.x + j;
			cub->y = pos.y + pos1.y;
			put_pixel(incr_color.y, cub);
			j++;
		}
	}
	else
	{
		while (j > pos1.x)
		{
			cub->x = pos.x + j;
			cub->y = pos.y + pos1.y;
			put_pixel(incr_color.y, cub);
			j--;
		}
	}
}

void	draw_circle(t_cub *cub, int x, int y, int color)
{
	double	i;
	double	angle;
	double	x1;
	double	y1;

	i = 0;
	while (i < 360)
	{
		angle = i;
		x1 = cub->player->radius * cos(angle * M_PI / 180);
		y1 = cub->player->radius * sin(angle * M_PI / 180);
		if (x1 > 0)
			simple_draw_line((t_pos){x, y},
				(t_pos){x1, y1}, cub, (t_pos){1, color});
		else
			simple_draw_line((t_pos){x, y},
				(t_pos){x1, y1}, cub, (t_pos){-1, color});
		i += 0.1;
	}
}

void	dda(t_cub *cub, t_pos p0, t_pos p1)
{
	t_DDA	dda;
	int		i;

	dda.dx = p1.x - p0.x;
	dda.dy = p1.y - p0.y;
	if (abs(dda.dx) > abs(dda.dy))
		dda.steps = abs(dda.dx);
	else
		dda.steps = abs(dda.dy);
	dda.xinc = dda.dx / (float)dda.steps;
	dda.yinc = dda.dy / (float)dda.steps;
	dda.x = p0.x;
	dda.y = p0.y;
	i = -1;
	while (++i <= dda.steps)
	{
		cub->x = dda.x;
		cub->y = dda.y;
		put_pixel(0xFF0000FF, cub);
		dda.x += dda.xinc;
		dda.y += dda.yinc;
	}
}

void	update_player(t_player *player, t_cub *cub)
{
	int		move_step;
	int		move_side;
	double	new_x;
	double	new_y;

	player->rot_angle += player->turn_dir * player->rot_speed;
	move_side = player->walk_side * player->move_speed;
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
