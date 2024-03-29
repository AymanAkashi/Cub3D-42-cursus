/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 21:12:38 by moseddik          #+#    #+#             */
/*   Updated: 2023/12/18 13:57:10 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_position_player(t_cub *cub, int i, int j, char c)
{
	cub->player->pos.x = j;
	cub->player->pos.y = i;
	cub->player->direction = c;
}

void	check_map(char **map, t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	while (map && map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (check_char(map[i]) == _false)
				error_map(0, cub);
			if (player_posistion(map[i][j]) && cub->player->pos.x == -1)
				set_position_player(cub, i, j, map[i][j]);
			else if (player_posistion(map[i][j]) && cub->player->pos.x != -1)
				error_map(0, cub);
			if (map[i][j] == '0' || player_posistion(map[i][j])
				|| map[i][j] == 'D')
				checking_valid_map(map, i, j, cub);
		}
	}
	if (cub->player->pos.x == -1 || map[i - 1][j - 1] == '\n')
		error_map(0, cub);
}
