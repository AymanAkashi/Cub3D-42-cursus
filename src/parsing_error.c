/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 17:39:49 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/16 22:12:15 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	error_file(int fd)
{
	if (fd == -1)
		(red(), printf("Cub3D :( %s\n", strerror(errno)), reset());
	else
		(red(), printf("Cub3D :( Invalid file format\n"), reset());
	exit(EXIT_FAILURE);
}

void	error_infomation(int c)
{
	if (c == 0)
		(red(), printf("Cub3D :( Missing information\n"), reset());
	else if (c == 3)
		(red(), printf("Cub3D :( Color not Valid\n"), reset());
	else if (c == -1)
		(red(), printf("Cub3D :( Error information\n"), reset());
	else
		(red(), printf("Cub3D :( Invalid path\n"));
	exit(EXIT_FAILURE);
}

void	error_map(int c)
{
	if (c == 0)
		(red(), printf("Cub3D :( Invalid map\n"), reset());
	else if (c == 1)
		(red(), printf("Cub3D :( Map not found\n"), reset());
	exit(EXIT_FAILURE);
}
