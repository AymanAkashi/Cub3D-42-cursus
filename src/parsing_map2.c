/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:02:56 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/14 17:04:34 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_bool	is_not_zero(char c)
{
	if (c != '1' && c != 'N' && c != 'S' && c != 'W' && c != 'E' && c != '0')
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

void	checking_valid_map(char **map, int i, int j)
{
	if (j == 0 || j == (int)ft_strlen(map[i]) || map[i][j + 1] == '\0')
		error_map(0);
	if (i == 0 || i == len_tab(map))
		error_map(0);
	if (i - 1 >= 0 && !is_not_zero(map[i - 1][j]))
		error_map(0);
	if (i + 1 < len_tab(map) && !is_not_zero(map[i + 1][j]))
		error_map(0);
	if (j - 1 >= 0 && !is_not_zero(map[i][j - 1]))
		error_map(0);
	if (j + 1 < (int)ft_strlen(map[i]) && !is_not_zero(map[i][j + 1]))
		error_map(0);
}

void	check_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map && map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (check_char(map[i]) == _false)
				error_map(0);
			if (map[i][j] == '0')
				checking_valid_map(map, i, j);
			j++;
		}
		i++;
	}
}
