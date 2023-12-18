/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 17:44:32 by aaggoujj          #+#    #+#             */
/*   Updated: 2023/12/18 13:57:10 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*append_char(char *str, char c)
{
	char	*new;
	int		i;

	if (!str)
	{
		new = ft_calloc(sizeof(char), 2);
		new[0] = c;
		return (new);
	}
	i = -1;
	new = ft_calloc(sizeof(char), (ft_strlen(str) + 2));
	while (str[++i])
		new[i] = str[i];
	new[i] = c;
	free(str);
	return (new);
}
