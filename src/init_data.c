/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 22:40:32 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/16 22:40:46 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
	cub->player.x = -1;
	cub->player.y = -1;
}
