/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:08:41 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/11/12 17:34:55 by aaggoujj         ###   ########.fr       */
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

void	simple_draw_helper(t_cub *cub, int *j, t_pos pos1)
{
	int	nx;
	int	ny;

	nx = floor((cub->player->pos.x + *j) / BLOCK_SIZE);
	ny = floor((cub->player->pos.y + pos1.y) / BLOCK_SIZE);
	if (ny < 0 || nx < 0 || ny >= cub->win_height / BLOCK_SIZE
		|| nx >= cub->win_width / BLOCK_SIZE || cub->tab[ny] <= nx)
		put_pixel(0x00000000, cub);
	else if (cub->map[ny][nx] == '1')
		put_pixel(0x00003566, cub);
	else if (cub->map[ny][nx] == 'D')
		put_pixel(0x00001d3d, cub);
	else if (cub->map[ny][nx] == ' ')
		put_pixel(0x00000000, cub);
	else
		put_pixel(0x00ffc300, cub);
	*j = *j + 1;
}

void	simple_draw_helper_2(t_cub *cub, int *j, t_pos pos1)
{
	int	nx;
	int	ny;

	nx = floor((cub->player->pos.x + *j) / BLOCK_SIZE);
	ny = floor((cub->player->pos.y + pos1.y) / BLOCK_SIZE);
	if (ny < 0 || nx < 0 || ny >= cub->win_height / BLOCK_SIZE
		|| nx >= cub->win_width / BLOCK_SIZE || cub->tab[ny] <= nx)
		put_pixel(0x00000000, cub);
	else if (cub->map[ny][nx] == '1')
		put_pixel(0x00003566, cub);
	else if (cub->map[ny][nx] == 'D')
		put_pixel(0x00001d3d, cub);
	else if (cub->map[ny][nx] == ' ')
		put_pixel(0x00000000, cub);
	else
		put_pixel(0x00ffc300, cub);
	*j = *j - 1;
}

void	simple_draw(t_pos pos, t_pos pos1, t_cub *cub, t_pos incr_color)
{
	int	j;

	j = 0;
	if (incr_color.x == 1)
	{
		while (j < pos1.x)
		{
			cub->x = pos.x + j;
			cub->y = pos.y + pos1.y;
			simple_draw_helper(cub, &j, pos1);
		}
	}
	else
	{
		while (j > pos1.x)
		{
			cub->x = pos.x + j;
			cub->y = pos.y + pos1.y;
			simple_draw_helper_2(cub, &j, pos1);
		}
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
