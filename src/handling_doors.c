/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_doors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 03:59:31 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/11/10 19:51:31 by aaggoujj         ###   ########.fr       */
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