/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:22:28 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/11/07 16:18:22 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "input.h"
# include <../lib/MLX/mlx.h>
# include "../lib/libft/include/libft.h"
# include "get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <sys/errno.h>
# include <math.h>

# define BLOCK_SIZE 16
# define WIN_WIDTH 1080
# define WIN_HEIGHT 720
# define RADIUS_MAP 80
# define FOV 60
# define FOV_ANGLE (FOV * (M_PI / 180))
# define NUM_RAYS (WIN_WIDTH)

# define MAX_INT 2147483647

// state enum
typedef enum e_state
{
	facing_up,
	facing_down,
	facing_left,
	facing_right
}	t_state;

typedef enum e_bool
{
	_false,
	_true
}	t_bool;

// rays data
typedef struct s_rays
{
	double	ray_angle;
	double	wall_hit_x;
	double	wall_hit_y;
	double	distance;
	t_bool 	was_hit_vertical;
	t_state	state;
}				t_rays;

// DDA variables
typedef struct s_DDA{
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	steps;
	double	xinc;
	double	yinc;
}				t_DDA;

// enum compass
typedef enum e_type
{
	NO,
	SO,
	WE,
	EA,
	F,
	C
}			t_type;

// Struct for the compass
typedef struct s_compass
{
	t_type				type;
	char				*path;
	struct s_compass	*next;
	struct s_compass	*prev;
}	t_compass;

// Struct for colors
typedef struct s_color
{
	t_type	type;
	int		_r;
	int		_g;
	int		_b;
}	t_color;

typedef struct s_pos
{
	double		x;
	double		y;
}	t_pos;

// Struct for player
typedef struct s_player
{
	char		direction;
	t_pos		pos;
	t_pos		last_pos;
	int			length;
	int			turn_dir;
	int			walk_dir;
	int			walk_side;
	int			radius;
	double		rot_angle;
	double		move_speed;
	double		rot_speed;
}	t_player;

// main struct data
typedef struct s_cub
{
	t_compass		*compass;
	t_rays			*rays;
	char			**map;
	t_color			floor;
	t_color			celling;
	int				color_cell;
	int				color_floor;
	t_player		*player;
	int				win_width;
	int				win_height;
	unsigned int	*addr;
	int				bpp;
	int				size_line;
	int				endian;
	int				pixel;
	double			x;
	double			y;
	void			*wall;
	void			*mlx;
	void			*win;
	void			*img;
	void			*player_img;
	void			*line;
	int				distance_proj_plane;
	int				wall_strip_height;
	t_bool			mouse_hide;
}	t_cub;

void		parsing(char *map, t_cub *cub);

// Init data
void		init_data(t_cub *cub);

// Coloring output functions
void		red(void);
void		blue(void);
void		yellow(void);
void		purple(void);
void		reset(void);

// list compass functions
t_compass	*ft_d_lstnew(char *content, t_type type);
void		ft_d_lstadd_front(t_compass **alst, t_compass *new);
void		ft_d_lstadd_back(t_compass **alst, t_compass *new);
void		ft_d_lstclear(t_compass **lst);
void		ft_d_lstdelone(t_compass *lst);

// cub tools functions
char		*append_char(char *str, char c);

// error management functions
void		error_file(int fd, t_cub *cub);
void		error_infomation(int c, t_cub *cub);
void		error_map(int c, t_cub *cub);

// parsing functions
t_bool		check_path(char	*path);
t_type		check_type(char *str);
char		*get_path(char *str);
int			check_format(char *file);
void		parse_color(t_cub *cub, int *c, char *line);
int			count_vergul(char *str);
t_color		get_color_value(char *str, t_type type, t_cub *cub);
t_color		get_color(char *line, t_cub *cub);
t_bool		check_newline(char *line);
t_bool		check_digit(char **args);
char		*get_str(char *line, t_cub *cub);
t_bool		check_line(char *line);

// Parsing map functions
void		parsing_map(char *line, t_cub *cub, int fd);
int			check_line_map(char *line);
t_bool		check_char(char *line);
void		check_map(char **map, t_cub *cub);
char		*gnl_line(char *line, int fd);
t_bool		player_posistion(char c);

//free data functions
void		free_tab(char **tab);
void		free_data(t_cub *cub);

// begin cub functions
void		begin_cub(t_cub *cub);
void		init_player(t_cub	*cub);
void		set_angle(t_cub *cub);

// Events functions
void		key_esc(void *param);
void		move_player(void *param);
void		move(void *param);
void		update_player(t_player *player, t_cub *cub);
void		render_player(void *param);
void		hook(void *param);
t_bool		check_pos(int x, int y, char **map);
void		draw_circle(t_cub *cub, int x, int y, int color);
void		dda(t_cub *cub, t_pos p0, t_pos p1, int color);

// Hook functions
int			mouse_hook(int x, int y, void *param);
int			mouse_release(void	*param);
void		set_hide_mouse(int key, t_cub *cub);
int			end_game(t_cub *cub);
void		move_key(int key, t_cub *cub);
int			input_release(int key, t_cub *cub);
int			input(int key, t_cub *cub);
int			loop(void *param);
void		render(t_cub *cub);
t_bool		is_wall(int x, int y, t_cub *cub);
void		put_pixel(int color, t_cub *cub);
void		cast_all_rays(t_cub *cub, int x, int y);;
int			ft_atoi_base(char *str, char *base);
double		normalize_angle(double angle);

#endif