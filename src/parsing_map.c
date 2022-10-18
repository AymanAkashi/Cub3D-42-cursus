/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:52:54 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/18 13:09:07 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

char	*gnl_line(char *line, int fd)
{
	if (line)
		free(line);
	return (get_next_line(fd));
}

t_bool	check_char(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] != ' ' && line[i] != '\n'
			&& line[i] != '0' && line[i] != '1' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
			return (_false);
	}
	return (_true);
}

int	check_line_map(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\n'))
		i++;
	if (line[i] && check_char(&line[i]))
		return (1);
	if (!line || !line[i])
		return (0);
	else
		return (-1);
}

char	**dynamique_tab(char **tab, char *line)
{
	char	**new_tab;
	int		i;

	i = 0;
	if (!line)
		return (NULL);
	if (!tab || !tab[0])
	{
		new_tab = malloc(sizeof(char *) * 2);
		new_tab[0] = ft_strdup(line);
		new_tab[1] = NULL;
		return (new_tab);
	}
	while (tab[i])
		i++;
	new_tab = malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (tab[++i])
		new_tab[i] = ft_strdup(tab[i]);
	new_tab[i] = ft_strdup(line);
	new_tab[i + 1] = NULL;
	free_tab(tab);
	return (new_tab);
}

void	parsing_map(char *line, t_cub *cub, int fd)
{
	int	i;
	int	c;

	i = 0;
	while (line)
	{
		c = check_line_map(line);
		if (c == 1)
		{
			while (line)
			{
				if (check_line_map(line) == 1)
					cub->map = dynamique_tab(cub->map, line);
				else
					error_map(0, cub);
				line = gnl_line(line, fd);
			}
		}
		else if (c == -1)
			error_map(0, cub);
		line = gnl_line(line, fd);
	}
	if (c == 0)
		error_map(1, cub);
}
