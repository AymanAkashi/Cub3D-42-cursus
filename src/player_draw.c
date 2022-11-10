/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:08:41 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/11/10 18:50:04 by aaggoujj         ###   ########.fr       */
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

void	simple_draw(t_pos pos, t_pos pos1, t_cub *cub, t_pos incr_color)
{
	int	j;
	int	nx;
	int	ny;

	j = 0;
	if (incr_color.x == 1)
	{
		while (j < pos1.x)
		{
			cub->x = pos.x + j;
			cub->y = pos.y + pos1.y;
			nx = floor((cub->player->pos.x + j) / BLOCK_SIZE);
			ny = floor((cub->player->pos.y + pos1.y) / BLOCK_SIZE);
			if (ny < 0 || nx < 0 || ny >= cub->win_height / BLOCK_SIZE
				|| nx >= cub->win_width / BLOCK_SIZE || cub->tab[ny] <= nx)
				put_pixel(0x00000000, cub);
			else if (cub->map[ny][nx] == '1')
				put_pixel(0x003D0000, cub);
			else if (cub->map[ny][nx] == 'D')
				put_pixel(0x00FFFFFF, cub);
			else if (cub->map[ny][nx] == ' ')
				put_pixel(0x00000000, cub);
			else
				put_pixel(0x00950101, cub);
			j++;
		}
	}
	else
	{
		while (j > pos1.x)
		{
			cub->x = pos.x + j;
			cub->y = pos.y + pos1.y;
			nx = floor((cub->player->pos.x + j) / BLOCK_SIZE);
			ny = floor((cub->player->pos.y + pos1.y) / BLOCK_SIZE);
			if (ny < 0 || nx < 0 || ny >= cub->win_height / BLOCK_SIZE
				|| nx >= cub->win_width / BLOCK_SIZE || cub->tab[ny] <= nx)
				put_pixel(0x00000000, cub);
			else if (cub->map[ny][nx] == '1')
				put_pixel(0x003D0000, cub);
			else if (cub->map[ny][nx] == 'D')
				put_pixel(0x00FFFFFF, cub);
			else if (cub->map[ny][nx] == ' ')
				put_pixel(0x00000000, cub);
			else
				put_pixel(0x00950101, cub);
			j--;
		}
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

void	draw_circle(t_cub *cub, int x, int y, int color)
{
	float	i;
	float	angle;
	float	x1;
	float	y1;

	i = 0;
	while (i < 360)
	{
		angle = i;
		x1 = RADIUS_M * cos(angle * M_PI / 180);
		y1 = RADIUS_M * sin(angle * M_PI / 180);
		cub->x = x + x1;
		cub->y = y + y1;
		put_pixel(color, cub);
		if (x1 > 0)
			simple_draw((t_pos){x, y},
				(t_pos){x1, y1}, cub, (t_pos){1, color});
		else
			simple_draw((t_pos){x, y},
				(t_pos){x1, y1}, cub, (t_pos){-1, color});
		i += 0.1;
	}
	draw_circle_player(cub, RADIUS_M, WIN_HEIGHT - RADIUS_M, 0x00A5C9CA);
	dda(cub, (t_pos){x, y}, (t_pos){RADIUS_M + cos(cub->player->rot_angle) * 15,
		WIN_HEIGHT - RADIUS_M + sin(cub->player->rot_angle) * 15}, 0x000F3D3E);
}

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
