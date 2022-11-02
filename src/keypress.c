/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 10:08:39 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/11/02 22:03:13 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	move_key(int key, t_cub *cub)
{
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

int	input(int key, t_cub *cub)
{
	(void)cub;
	if (key == KEY_ESCAPE)
		end_game(cub);
	else
		move_key(key, cub);
	return (1);
}
