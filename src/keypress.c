/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 10:08:39 by aaggoujj          #+#    #+#             */
/*   Updated: 2023/12/18 13:57:10 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_door	*get_door(t_door *door, int x, int y)
{
	t_door	*tmp;

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
	int		px;
	int		py;
	t_door	*tmp;

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
	if (key == KEY_UP || key == KEY_DOWN || key == KEY_S || key == KEY_W)
	{
		if (cub->pos_weapon > 45)
			cub->dir_weapon = -1;
		else if (cub->pos_weapon <= 0)
		{
			cub->pos_weapon = 0;
			cub->dir_weapon = 1;
		}
		cub->pos_weapon += (15 * cub->dir_weapon);
	}
	if (key == KEY_SPACE && check_player(cub))
	{
		open_door(cub);
	}
}

int	input_release(int key, t_cub *cub)
{
	(void)cub;
	if (key == KEY_W || key == KEY_S || key == KEY_UP || key == KEY_DOWN)
	{
		cub->player->walk_dir = 0;
		cub->pos_weapon = 0;
	}
	if (key == KEY_A || key == KEY_D)
		cub->player->walk_side = 0;
	if (key == KEY_LEFT || key == KEY_RIGHT)
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
