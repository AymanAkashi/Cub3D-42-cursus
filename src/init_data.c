/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 22:40:32 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/23 22:49:48 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_player(t_cub	*cub)
{
	cub->player = malloc(sizeof(t_player));
	if (!(cub->player))
	{
		printf("Error\nmalloc failed to allocate player data");
		free_data(cub);
		exit(EXIT_FAILURE);
	}
	cub->player->pos.x = -1;
	cub->player->pos.y = -1;
	cub->player->length = 10;
	cub->player->rot_angle = M_PI / 2; //TODO check direction of rotation by "north" or "south"...
	cub->player->move_speed = 1;
	cub->player->rot_speed = 1 * (M_PI / 180);
	cub->player->turn_dir = 0;
	cub->player->walk_dir = 0;
	cub->player->radius = BLOCK_SIZE/2;
}

void	init_data(t_cub *cub)
{
	cub->celling._r = -1;
	cub->celling._g = -1;
	cub->celling._b = -1;
	cub->floor._r = -1;
	cub->floor._g = -1;
	cub->floor._b = -1;
	cub->compass = NULL;
	cub->map = NULL;
	init_player(cub);
}
