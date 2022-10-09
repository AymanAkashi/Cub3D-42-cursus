/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 12:59:43 by moseddik          #+#    #+#             */
/*   Updated: 2022/10/09 17:56:17 by aaggoujj         ###   ########.fr       */
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
	return (compass);
}

//******************************Print List of compass*************************//
void	print_list(t_compass *list)
{
	t_compass	*tmp;
	char		*str[] = {"NO", "SO", "WE", "EA"};

	tmp = list;
	while (tmp)
	{
		printf("type: %s, path: %s\n", str[tmp->type], tmp->path);
		tmp = tmp->next;
	}
}
//****************************************************************************//

void	scan_file(int fd, t_cub *cub, int c)
{
	char		*line;
	t_compass	*compass;

	compass = NULL;
	line = get_next_line(fd);
	while (line)
	{
		compass = scan_line(line);
		if (compass)
		{
			if (!check_order(compass->type, &c) || !check_path(compass->path))
				error_infomation(c);
			ft_d_lstadd_back(&cub->compass, compass);
			c++;
		}
		if (c == 4)
			break ;
		line = get_next_line(fd);
	}
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
	print_list(cub->compass);
	close(fd);
}
