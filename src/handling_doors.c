/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_doors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 03:59:31 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/11/10 21:57:33 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	set_door(t_cub *cub)
{
	t_door	*tmp;
	int		i;
	int		j;
	int		index;

	i = 0;
	index = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == 'D')
			{
				tmp = ft_door_new(index++, j, i);
				ft_door_add_back(&cub->door, tmp);
			}
			j++;
		}
		i++;
	}
}

void	open_door_helper(t_cub *cub, t_door *tmp, int px, int py)
{
	while (tmp)
	{
		if ((tmp->x == px && tmp->y == py + 2)
			|| (tmp->x == px + 2 && tmp->y == py)
			|| (tmp->x == px - 2 && tmp->y == py)
			|| (tmp->x == px && tmp->y == py - 2)
			|| (tmp->x == px && tmp->y == py + 1)
			|| (tmp->x == px + 1 && tmp->y == py)
			|| (tmp->x == px - 1 && tmp->y == py)
			|| (tmp->x == px && tmp->y == py - 1))
			cub->map[tmp->y][tmp->x] = 'O';
		tmp = tmp->next;
	}
}

void	open_door(t_cub *cub)
{
	t_door	*tmp;
	int		px;
	int		py;

	tmp = cub->door;
	if (cub->open == 0)
	{
		px = floor(cub->player->pos.x / BLOCK_SIZE);
		py = floor(cub->player->pos.y / BLOCK_SIZE);
		open_door_helper(cub, tmp, px, py);
		cub->open = 1;
	}
	else
	{
		while (tmp)
		{
			cub->map[tmp->y][tmp->x] = 'D';
			tmp = tmp->next;
		}
		cub->open = 0;
	}
}

t_bool	checking_door_open(t_door *door)
{
	t_door	*tmp;

	tmp = door;
	while (tmp)
	{
		if (tmp->is_open == _true)
			return (_true);
		tmp = tmp->next;
	}
	return (_false);
}
