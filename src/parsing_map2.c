/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:02:56 by aaggoujj          #+#    #+#             */
/*   Updated: 2023/12/18 13:57:10 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_bool	is_not_zero(char c)
{
	if (c != '1' && c != 'N' && c != 'S'
		&& c != 'W' && c != 'E' && c != '0' && c != 'D' && c != 'C')
		return (_false);
	return (_true);
}

int	len_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	checking_valid_map(char **map, int i, int j, t_cub *cub)
{
	if (j == 0 || j == (int)ft_strlen(map[i]) || map[i][j + 1] == '\0')
		error_map(0, cub);
	if (i == 0 || i == len_tab(map))
		error_map(0, cub);
	if (i - 1 >= 0 && !is_not_zero(map[i - 1][j]))
		error_map(0, cub);
	if (i + 1 < len_tab(map) && !is_not_zero(map[i + 1][j]))
		error_map(0, cub);
	if (j - 1 >= 0 && !is_not_zero(map[i][j - 1]))
		error_map(0, cub);
	if (j + 1 < (int)ft_strlen(map[i]) && !is_not_zero(map[i][j + 1]))
		error_map(0, cub);
}

t_bool	player_posistion(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (_true);
	return (_false);
}
