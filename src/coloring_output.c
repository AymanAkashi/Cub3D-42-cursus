/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 13:13:38 by moseddik          #+#    #+#             */
/*   Updated: 2022/10/09 13:17:05 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	red(void)
{
	printf("\033[1;31m");
}

void	blue(void)
{
	printf("\033[0;34m");
}

void	yellow(void)
{
	printf("\033[0;33m");
}

void	purple(void)
{
	printf("\033[0;35m");
}

void	reset(void)
{
	printf("\033[0m");
}
