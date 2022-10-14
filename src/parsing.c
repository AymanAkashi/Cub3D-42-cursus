/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 12:59:43 by moseddik          #+#    #+#             */
/*   Updated: 2022/10/14 17:05:27 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_compass	*scan_line(char *line)
{
	int			i;
	char		*content;
	t_compass	*compass;

	i = 0;
	content = NULL;
	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
		i++;
	if (!line || !line[i])
		return (NULL);
	while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
		content = append_char(content, line[i++]);
	compass = ft_d_lstnew(get_path(&line[i]), check_type(content));
	if ((int)check_type(content) == -1)
		error_infomation(-1);
	return (compass);
}

//******************************Print List of compass*************************//
void	print_list(t_compass *list, t_cub *cub)
{
	t_compass	*tmp;
	char		*str[] = {"NO", "SO", "WE", "EA", "F", "C"};

	tmp = list;
	while (tmp)
	{
		printf("type: %s, path: %s\n", str[tmp->type], tmp->path);
		tmp = tmp->next;
	}
	printf("type %s == color: %d, %d, %d\n",str[cub->floor.type], cub->floor._r, cub->floor._g, cub->floor._b);
	printf("type %s == color: %d, %d, %d\n",str[cub->celling.type], cub->celling._r, cub->celling._g, cub->celling._b);
	for(int i = 0; cub->map[i]; i++)
		printf("%s", cub->map[i]);
}
//****************************************************************************//

int	check_state(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
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
		compass = scan_line(line);
	else if (check_state(line) == 1)
		parse_color(cub, c, line);
	else if (check_state(line) == 0)
		return (_false);
	else
		error_infomation(-1);
	if (compass && check_state(line) == 2)
	{
		if (!check_path(compass->path))
			error_infomation(*c);
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

	line = get_next_line(fd);
	while (line)
	{
		if (parse_compass(cub, &c, line) == _true)
		{
			line = get_next_line(fd);
			break ;
		}
		line = get_next_line(fd);
	}
	while (line)
	{
		c = (check_line_map(line));
		if (c == 1)
		{
			parsing_map(line, cub, fd);
			break ;
		}
		else if (c == -1)
			error_map(0);
		line = get_next_line(fd);
	}
	check_map(cub->map);
}

void	parsing(char *map, t_cub *cub)
{
	int			c;
	int			fd;

	c = 0;
	fd = open(map, O_RDONLY | O_EXCL);
	if (fd == -1 || !check_format(map))
		error_file(fd);
	scan_file(fd, cub, c);
	print_list(cub->compass, cub);
	close(fd);
}
