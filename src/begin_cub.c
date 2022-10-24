/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 09:56:14 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/23 22:48:19 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	put_pixel(size_t r, size_t g, size_t b, t_cub *cub)
{
	size_t	i;

	i = 0;
	while (i < cub->img->width * cub->img->height * sizeof(int))
	{
		cub->img->pixels[i] = r;
		cub->img->pixels[i + 1] = g;
		cub->img->pixels[i + 2] = b;
		cub->img->pixels[i + 3] = 255;
		i += sizeof(int);
	}
}

void	put_pixel_p(size_t r, size_t g, size_t b, t_cub *cub)
{
	size_t	i;

	i = 0;
	while (i < cub->player_img->width * cub->player_img->height * sizeof(int))
	{
		cub->player_img->pixels[i] = r;
		cub->player_img->pixels[i + 1] = g;
		cub->player_img->pixels[i + 2] = b;
		cub->player_img->pixels[i + 3] = 255;
		i += sizeof(int);
	}
}

void	render(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == '1')
			{
				cub->img = mlx_new_image(cub->mlx, BLOCK_SIZE, BLOCK_SIZE);
				put_pixel(255, 255, 255, cub);
				mlx_image_to_window(cub->mlx, cub->img, j * BLOCK_SIZE, i * BLOCK_SIZE);
			}
			j++;
		}
		i++;
	}
}

void	draw_circle(t_cub *cub, int x, int y, int color)
{
	double i, angle, x1, y1;
        (void)color;
	for(i = 0; i < 360; i += 0.1)
	{
		angle = i;
		x1 = cub->player->radius * cos(angle * M_PI / 180);
		y1 = cub->player->radius * sin(angle * M_PI / 180);
		if (x1 > 0)
			for(int j = 0; j < x1; j++)
				mlx_put_pixel(cub->player_img, x + j, y + y1, 0x000000FF);
		else
			for(int j = 0; j > x1; j--)
				mlx_put_pixel(cub->player_img, x + j, y + y1, 0x000000FF);
	}
}

void	dda(t_cub *cub, int X0, int Y0, int X1, int Y1)
{
    int dx = X1 - X0;
    int dy = Y1 - Y0;

    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;

    float X = X0;
    float Y = Y0;
    for (int i = 0; i <= steps; i++) {
        mlx_put_pixel(cub->player_img, X,Y, 0xFF0000FF);
        X += Xinc;
        Y += Yinc;
    }
}

void	update_player(t_player *player, t_cub *cub)
{
	int	move_step;
	int move_side;
	(void)cub;

	player->rot_angle += player->turn_dir * player->rot_speed;

	move_side = player->walk_side * player->move_speed;
	move_step = player->walk_dir * player->move_speed;

	player->last_pos.x = player->pos.x;
	player->last_pos.y = player->pos.y;
	if (move_side)
	{
		player->pos.x += cos(player->rot_angle - M_PI / 2) * move_side;
		player->pos.y += sin(player->rot_angle - M_PI / 2) * move_side;
	}
	if (move_step)
	{
		player->pos.x += cos(player->rot_angle) * move_step;
		player->pos.y += sin(player->rot_angle) * move_step;
	}
	cub->player_img->instances[0].x += cub->player->pos.x - player->last_pos.x;
	cub->player_img->instances[0].y += cub->player->pos.y - player->last_pos.y;
}

void	render_player(void *param)
{
	t_cub	*cub;

	cub = (void *)param;
	cub->player_img = mlx_new_image(cub->mlx, BLOCK_SIZE, BLOCK_SIZE);
	cub->line = mlx_new_image(cub->mlx, BLOCK_SIZE, BLOCK_SIZE);
	draw_circle(cub, cub->player->radius, cub->player->radius, 0x000000FF);
	mlx_image_to_window(cub->mlx, cub->player_img,
		cub->player->pos.x * BLOCK_SIZE, cub->player->pos.y * BLOCK_SIZE);
}

void	update_map(void	*param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	render(cub);
}

void	begin_cub(t_cub *cub)
{
	cub->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D", _true);
	cub->player->last_pos.x = cub->player->pos.x;
	cub->player->last_pos.y = cub->player->pos.y;

	update_map(cub);
	render_player(cub);
	mlx_loop_hook(cub->mlx, &move, cub);

	// Draw map and player

	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
}
