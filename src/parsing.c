/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 12:59:43 by moseddik          #+#    #+#             */
/*   Updated: 2022/10/09 14:37:08 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	check_format(char *file)
{
	char	*format;
	int		i;
	int		j;

	format = ft_strdup("buc.");
	i = ft_strlen(file) - 1;
	j = -1;
	while (i >= 0 && format[++j] == file[i])
		i--;
	free(format);
	if (j == 4)
		return (_true);
	return (_false);
}

void parsing(char *map)
{
	int		fd;

	fd = open(map, O_RDONLY | O_EXCL);
	if (fd == -1 || !check_format(map))
	{
		if (fd == -1)
			(red(), printf("Cub3D :( %s\n", strerror(errno)), reset());
		else
			(red(), printf("Cub3D :( Invalid file format\n"), reset());
		exit(EXIT_FAILURE);
	}
	char	*line = get_next_line(fd);
	while (line)
	{
		printf("%s",line);
		line = get_next_line(fd);
	}
	printf("\n");
	close(fd);
}