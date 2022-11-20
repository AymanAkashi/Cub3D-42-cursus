/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:20:47 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/11/12 16:46:17 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_cub	*cub;

	cub = ft_calloc(1, sizeof(t_cub));
	if (ac > 2)
		return (red(), printf("To many arguments\n"), EXIT_FAILURE);
	else if (ac == 1)
		return (red(), printf("Select a map as argument\n"), EXIT_FAILURE);
	parsing(av[1], cub);
	begin_cub(cub);
	free_data(cub);
	return (EXIT_SUCCESS);
}
