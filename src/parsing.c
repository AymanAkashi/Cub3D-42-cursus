/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 12:59:43 by moseddik          #+#    #+#             */
/*   Updated: 2022/11/08 13:43:45 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_compass	*scan_line(char *line, t_cub *cub)
{
	int			i;
	char		*content;
	t_compass	*compass;

	i = 0;
	content = NULL;
	while (line[i] && (line[i] == ' ' || line[i] == '\n'))
		i++;
	if (!line || !line[i])
		return (NULL);
	while (line[i] && line[i] != ' ' && line[i] != '\n')
		content = append_char(content, line[i++]);
	compass = ft_d_lstnew(get_path(&line[i]), check_type(content));
	if ((int)check_type(content) == -1)
		error_infomation(-1, cub);
	free(content);
	return (compass);
}

int	check_state(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\n'))
		i++;
	if (!line[i])
		return (0);
	else if (line[i] == 'F' || line[i] == 'C')
		return (1);
	else if (line[i] == 'N' || line[i] == 'S'
		|| line[i] == 'W' || line[i] == 'E')
		return (2);
	else
		return (-1);
}

t_bool	parse_compass(t_cub *cub, int *c, char *line)
{
	t_compass	*compass;

	compass = NULL;
	if (check_state(line) == 2)
		compass = scan_line(line, cub);
	else if (check_state(line) == 1)
		parse_color(cub, c, line);
	else if (check_state(line) == 0)
		return (_false);
	else
		error_infomation(-1, cub);
	if (compass && check_state(line) == 2)
	{
		ft_d_lstadd_back(&cub->compass, compass);
		(*c)++;
	}
	if (*c == 6)
		return (_true);
	return (_false);
}

void	scan_file(int fd, t_cub *cub, int c)
{
	char		*line;

	line = NULL;
	line = gnl_line(line, fd);
	while (line)
	{
		if (parse_compass(cub, &c, line) == _true)
		{
			line = gnl_line(line, fd);
			break ;
		}
		line = gnl_line(line, fd);
	}
	parsing_map(line, cub, fd);
	check_map(cub->map, cub);
}

void	parsing(char *map, t_cub *cub)
{
	int			c;
	int			fd;

	c = 0;
	fd = open(map, O_RDONLY | O_EXCL);
	init_data(cub);
	if (fd == -1 || !check_format(map))
		error_file(fd, cub);
	scan_file(fd, cub, c);
	close(fd);
}
