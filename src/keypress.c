/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 10:08:39 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/11/07 16:03:01 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	set_hide_mouse(int key, t_cub *cub)
{
	if (key == KEY_Q && !cub->mouse_hide)
	{
		mlx_mouse_hide();
		cub->mouse_hide = _true;
	}
	else if (key == KEY_Q && cub->mouse_hide)
	{
		mlx_mouse_show();
		cub->mouse_hide = _false;
	}
}

void	move_key(int key, t_cub *cub)
{
	set_hide_mouse(key, cub);
	if (key == KEY_W || key == KEY_UP)
		cub->player->walk_dir = 1;
	if (key == KEY_S || key == KEY_DOWN)
		cub->player->walk_dir = -1;
	if (key == KEY_A)
		cub->player->walk_side = -1;
	if (key == KEY_D)
		cub->player->walk_side = 1;
	if (key == KEY_LEFT)
		cub->player->turn_dir = -1;
	if (key == KEY_RIGHT)
		cub->player->turn_dir = 1;
}

int	input_release(int key, t_cub *cub)
{
	(void)cub;
	if (key == KEY_W || key == KEY_S || key == KEY_UP || key == KEY_DOWN)
		cub->player->walk_dir = 0;
	if (key == KEY_A || key == KEY_D)
		cub->player->walk_side = 0;
	if (key == KEY_LEFT || key == KEY_RIGHT)
		cub->player->turn_dir = 0;
	return (1);
}

int	mouse_hook(int x, int y, void *param)
{
	t_cub *cub;
	int x_center;
	int y_center;
	int x_diff;
	int y_diff;

	x_center = WIN_WIDTH / 2;
	y_center = WIN_HEIGHT / 2;
	cub = (t_cub *)param;
	if (cub->mouse_hide)
	{
			mlx_mouse_move(cub->win, x_center, y_center);
		if (x < 0 || x > WIN_WIDTH || y < 0 || y > WIN_HEIGHT)
			return (1);
		x_diff = x - x_center;
		y_diff = y - y_center;
		cub->player->rot_angle += (x_diff * 0.001);
	}
	return (1);
}

int	mouse_release(void	*param)
{
	t_cub *cub;

	cub = (t_cub *)param;
	cub->player->turn_dir = 0;
	return (1);
}

int	input(int key, t_cub *cub)
{
	(void)cub;
	if (key == KEY_ESCAPE)
		end_game(cub);
	else
	{
		move_key(key, cub);
	}
	return (1);
}
