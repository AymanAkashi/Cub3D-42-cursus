/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 10:08:39 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/23 22:48:03 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	key_esc(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
	{
		free_data(cub);
		mlx_terminate(cub->mlx);
		exit(EXIT_SUCCESS);
	}
}

void	move_player(void *param)
{
	t_cub 	*cub;

	cub = (void *)param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
		cub->player->walk_dir = 1;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
		cub->player->walk_dir = -1;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
		cub->player->walk_side = -1;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
		cub->player->walk_side = 1;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		cub->player->turn_dir = 1;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
		cub->player->turn_dir = -1;
}

void	move_player_realese(mlx_key_data_t keydata, void *param)
{
	t_cub 	*cub;

	cub = (void *)param;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		cub->player->walk_dir = 0;
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		cub->player->walk_dir = 0;
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		cub->player->walk_side = 0;
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		cub->player->walk_side = 0;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		cub->player->turn_dir = 0;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		cub->player->turn_dir = 0;
}

void	move(void *param)
{
	t_cub 	*cub;

	cub = (void *)param;

	// move player
	move_player(cub);
	mlx_key_hook(cub->mlx, &move_player_realese, cub);
	update_player(cub->player, cub);
	draw_circle(cub, cub->player->radius, cub->player->radius, 0x000000FF);
    	dda(cub, cub->player->radius, cub->player->radius, cub->player->radius + cos(cub->player->rot_angle) * 22 , cub->player->radius + sin(cub->player->rot_angle) * 22);
	key_esc(cub);
}