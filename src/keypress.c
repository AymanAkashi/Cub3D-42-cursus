/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 10:08:39 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/11/10 16:01:19 by aaggoujj         ###   ########.fr       */
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

t_door *get_door(t_door *door, int x, int y)
{
	t_door *tmp;

	tmp = door;
	while (tmp)
	{
		if (tmp->x == x && tmp->y == y)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_bool	check_player(t_cub *cub)
{
	int	px;
	int	py;
	t_door *tmp;

	tmp = cub->door;
	px = floor(cub->player->pos.x / BLOCK_SIZE);
	py = floor(cub->player->pos.y / BLOCK_SIZE);
	while (tmp)
	{
		
		if ((tmp->x == px && tmp->y == py))
			return (_false);
		tmp = tmp->next;
	}
	return (_true);
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
	if (key == KEY_SPACE && check_player(cub))
	{
		if (cub->open == 0)
		{
			int px;
			int py;

			int	DD;
		
			DD = 2;
			px = floor(cub->player->pos.x / BLOCK_SIZE);
			py = floor(cub->player->pos.y / BLOCK_SIZE);
			t_door *tmp = cub->door;
			while (tmp)
			{
				if ((tmp->x == px && tmp->y == py + DD) || (tmp->x == px + DD && tmp->y == py) || (tmp->x == px - DD && tmp->y == py) || (tmp->x == px && tmp->y == py - DD)
					|| (tmp->x == px && tmp->y == py + 1) || (tmp->x == px + 1 && tmp->y == py) || (tmp->x == px - 1 && tmp->y == py) || (tmp->x == px && tmp->y == py - 1))
					cub->map[tmp->y][tmp->x] = 'O';
				tmp = tmp->next;
			}
			cub->open = 1;
		}
		else
		{
			t_door *tmp = cub->door;
			while (tmp)
			{
				cub->map[tmp->y][tmp->x] = 'D';
				tmp = tmp->next;
			}
			cub->open = 0;
		} 
	}
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

int	mouse_move(int x, int y, void *param)
{
	t_cub	*cub;
	int		x_center;
	int		y_center;
	int		x_diff;
	int		y_diff;

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
	t_cub	*cub;

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
		move_key(key, cub);
	return (1);
}
