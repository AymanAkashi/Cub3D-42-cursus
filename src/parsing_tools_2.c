/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:21:07 by moseddik          #+#    #+#             */
/*   Updated: 2022/10/13 14:25:24 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	check_digit(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (!ft_isdigit(args[i][j]) && args[i][j] != ' '
				&& args[i][j] != '\t')
				return (_false);
			j++;
		}
		i++;
	}
	if (i != 3)
		return (_false);
	return (_true);
}

char	*get_str(char *line)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
		i++;
	while (line[i] && line[i] != '\n')
		str = append_char(str, line[i++]);
	if (!str || !check_line(&line[i]))
		error_infomation(0);
	return (str);
}

t_bool	check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
		i++;
	if (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
		return (_false);
	return (_true);
}
