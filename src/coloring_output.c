/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 13:13:38 by moseddik          #+#    #+#             */
/*   Updated: 2023/12/18 13:57:10 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdio.h>

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
