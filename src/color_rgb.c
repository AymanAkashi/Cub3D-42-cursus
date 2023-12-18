/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:54:16 by aaggoujj          #+#    #+#             */
/*   Updated: 2023/12/18 13:57:10 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	put_pixel(int color, t_cub *cub)
{
	if (cub->y < WIN_HEIGHT && cub->x < WIN_WIDTH && cub->y >= 0 && cub->x >= 0)
	cub->addr[(int)cub->y * WIN_WIDTH + (int)cub->x] = color;
}

int	create_trgb(int t, t_color color)
{
	return (t << 24 | color._r << 16 | color._g << 8 | color._b);
}
