/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:20:47 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/09 11:53:27 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	(void)av;
	if (ac > 2)
		return (printf("To many arguments\n"), EXIT_FAILURE);
	else if (ac == 1)
		return (printf("Please select a map as argument\n"), EXIT_FAILURE);
	printf("Cube3D is loading...\n");
	return (EXIT_SUCCESS);
}
