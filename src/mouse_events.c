/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:48:07 by moseddik          #+#    #+#             */
/*   Updated: 2022/12/27 00:14:25 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	mouse_move(int x, int y, void *param)
{
	t_cub	*cub;
	int		x_center;
	int		y_center;
	int		x_diff;

	x_center = WIN_WIDTH / 2;
	y_center = WIN_HEIGHT / 2;
	cub = (t_cub *)param;
	if (cub->mouse_hide)
	{
		mlx_mouse_move(cub->mlx, cub->win, x_center, y_center);
		if (x < 0 || x > WIN_WIDTH || y < 0 || y > WIN_HEIGHT)
			return (1);
		x_diff = x - x_center;
		cub->player->rot_angle += (x_diff * 0.001);
	}
	return (1);
}

int	mouse_release(void	*param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	cub->player->turn_dir = 0;
	return (1);
}

void	set_hide_mouse(int key, t_cub *cub)
{
	if (key == KEY_Q && !cub->mouse_hide)
	{
		mlx_mouse_hide(cub->mlx, cub->win);
		cub->mouse_hide = _true;
	}
	else if (key == KEY_Q && cub->mouse_hide)
	{
		mlx_mouse_show(cub->mlx, cub->win);
		cub->mouse_hide = _false;
	}
}
