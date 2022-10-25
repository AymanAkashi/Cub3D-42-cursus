/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 21:16:02 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/25 21:51:06 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_blackground(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->win_height)
	{
		j = 0;
		while (j < cub->win_width)
		{
			cub->x = j;
			cub->y = i;
			put_pixel(0x003289A8, cub);
			j++;
		}
		i++;
	}
}

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
				draw_block(j * BLOCK_SIZE, i * BLOCK_SIZE, cub, 0x00FFFFFF);
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
	draw_blackground(cub);
	update_player(cub->player, cub);
	draw_walls(cub);
	draw_circle(cub, x, y, 0x00FF0000);
	dda(cub, (t_pos){x, y}, (t_pos){x + cos(cub->player->rot_angle)
		* 22, y + sin(cub->player->rot_angle) * 22});
	mlx_clear_window(cub->mlx, cub->win);
}
