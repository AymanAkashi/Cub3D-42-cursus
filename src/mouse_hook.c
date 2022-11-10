/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:42:39 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/11/10 19:44:46 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	mouse_click(int button, int x, int y, t_cub *cub)
{
	(void)x;
	(void)y;
	if (button == 1 && !cub->mouse_hide)
	{
		mlx_mouse_hide();
		cub->mouse_hide = _true;
	}
	return (0);
}

int	mouse_start(int button, int x, int y, t_cub *cub)
{
	int	width;
	int	height;

	width = WIN_WIDTH / 2;
	height = WIN_HEIGHT / 2;
	if (button == 1 && (x >= width - 200 && x <= width + 200)
		&& (y >= height - 100 && y <= height))
		hook_start(cub);
	if (button == 1 && (x >= width - 110 && x <= width + 110)
		&& (y >= height + 40 && y <= height + 80))
		end_game(cub);
	return (0);
}

int	mouse_init(t_cub *cub)
{
	if (mlx_mouse_hook(cub->win, mouse_start, cub) == 0)
		return (0);
	return (1);
}
