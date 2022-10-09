/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 17:39:49 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/09 17:56:30 by aaggoujj         ###   ########.fr       */
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
	if (c == -1)
		(red(), printf("Cub3D :( Error order of header infomation\n"));
	else
		(red(), printf("Cub3D :( Invalid path\n"));
	exit(EXIT_FAILURE);
}
