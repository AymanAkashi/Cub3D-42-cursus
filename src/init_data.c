/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 22:40:32 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/20 09:55:46 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	init_player(t_cub	*cub)
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
	cub->player->rot_angle = 0;
	cub->player->move_speed = 2.0;
	cub->player->rot_speed = 1.5 * (M_PI / 180);
	cub->player->turn_dir = 0;
	cub->player->walk_dir = 0;
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
