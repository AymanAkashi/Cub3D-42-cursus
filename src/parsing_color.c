/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:12:33 by moseddik          #+#    #+#             */
/*   Updated: 2022/10/16 22:26:09 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_vergul(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}

static void	ft_new_color(t_color *color, t_type type, char **colors)
{
	color->type = type;
	color->_r = ft_atoi(colors[0]);
	color->_g = ft_atoi(colors[1]);
	color->_b = ft_atoi(colors[2]);
}

t_color	get_color_value(char *str, t_type type)
{
	t_color	color;
	char	**colors;
	int		i;

	i = 0;
	if (count_vergul(str) != 2)
		error_infomation(3);
	colors = ft_split(str, ' ');
	while (colors[i])
		i++;
	if (i != 1)
		error_infomation(3);
	colors = ft_split(str, ',');
	if (!check_digit(colors))
		error_infomation(3);
	if (!colors || !colors[0] || !colors[1] || !colors[2])
		error_infomation(0);
	ft_new_color(&color, type, colors);
	if (!(color._r >= 0 && color._r <= 255)
		|| !(color._g >= 0 && color._g <= 255)
		|| !(color._b >= 0 && color._b <= 255))
		error_infomation(3);
	return (color);
}

t_color	get_color(char *line)
{
	int		i;
	char	*str;
	char	*tmp;
	t_color	color;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	tmp = append_char(NULL, line[i++]);
	str = get_str(&line[i]);
	color = get_color_value(str, check_type(tmp));
	free(str);
	free(tmp);
	if ((int)color.type == -1)
		error_infomation(-1);
	return (color);
}

void	parse_color(t_cub *cub, int *c, char *line)
{
	t_color	color;
	char	type;
	int		i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	type = line[i];
	if (check_newline(line))
	{
		color = get_color(line);
		if (type == 'F')
			cub->floor = color;
		else
			cub->celling = color;
		(*c)++;
	}
}
