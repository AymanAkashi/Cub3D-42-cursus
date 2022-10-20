/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 10:08:39 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/20 10:37:48 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	key_esc(mlx_key_data_t keydata, void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		free_data(cub);
		mlx_terminate(cub->mlx);
		exit(EXIT_SUCCESS);
	}
}
