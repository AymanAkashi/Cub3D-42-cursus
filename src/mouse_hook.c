/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:42:39 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/12/27 01:18:18 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	mouse_click(int button, int x, int y, t_cub *cub)
{
	(void)x;
	(void)y;
	// printf("button: %d\n", button);
	if (button == 1 && !cub->mouse_hide)
	{
		mlx_mouse_hide(cub->mlx, cub->win);
		cub->mouse_hide = _true;
	}
	return (0);
}
