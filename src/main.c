/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:20:47 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/09 17:55:43 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_cub	*cub;

	(void)av;
	cub = ft_calloc(1, sizeof(t_cub));
	if (ac > 2)
		return (red(), printf("To many arguments\n"), EXIT_FAILURE);
	else if (ac == 1)
		return (red(), printf("Select a map as argument\n"), EXIT_FAILURE);
	parsing(av[1], cub);
	printf("Cube3D is loading...\n");
	return (EXIT_SUCCESS);
}
