/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 17:43:27 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/11/10 21:11:56 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_bool	check_path(char	*path)
{
	int		fd;
	int		i;
	char	*src;

	i = 0;
	if (!path)
		return (_false);
	while (path[i] && path[i] != '\n' && path[i] != ' ')
		i++;
	src = ft_calloc(sizeof(char), i + 1);
	ft_memcpy(src, path, i);
	while (path[i] && (path[i] == ' ' || path[i] == '\n'))
		i++;
	if (path[i] != '\0' && path[i] != '\n')
	{
		free(src);
		return (_false);
	}
	fd = open(src, O_RDONLY | O_EXCL);
	free(src);
	if (fd == -1)
		return (_false);
	close(fd);
	return (_true);
}

t_type	check_type(char *str)
{
	if (!ft_strcmp(str, "NO"))
		return (NO);
	else if (!ft_strcmp(str, "SO"))
		return (SO);
	else if (!ft_strcmp(str, "WE"))
		return (WE);
	else if (!ft_strcmp(str, "EA"))
		return (EA);
	else if (!ft_strcmp(str, "F"))
		return (F);
	else if (!ft_strcmp(str, "C"))
		return (C);
	else
		return (-1);
}

char	*get_path(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (!str[i] || str[i] == '\n')
		return ("");
	j = i;
	while (str[j] && str[j] != ' ' && str[j] != '\n')
		j++;
	return (ft_substr(str, i, j - i));
}

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

t_bool	check_newline(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ')
			return (_true);
		i++;
	}
	return (_false);
}
