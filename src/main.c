/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:20:47 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/11/10 15:54:46 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	open_image_door(t_cub *cub)
{
	cub->texture_door.img = mlx_xpm_file_to_image(cub->mlx, "textures/door.xpm",
			&cub->texture_door.width, &cub->texture_door.height);
	if (!cub->texture_door.img)
	{
		printf("Error\nFailed to load door texture\n");
		exit(1);
	}
	cub->texture_door.addr = mlx_get_data_addr(cub->texture_door.img,
			&cub->texture_door.bpp, &cub->texture_door.size_line,
			&cub->texture_door.endian);
}

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
	system("leaks cub3d");
	return (EXIT_SUCCESS);
}
