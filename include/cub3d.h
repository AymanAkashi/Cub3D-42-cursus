/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:22:28 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/11/12 13:14:28 by moseddik         ###   ########.fr       */
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

# define BLOCK_SIZE 32
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define RADIUS_M 80
# define FOV 60
# define NUM_RAYS (WIN_WIDTH)
# define RADUIS_ANGLE 50

# define MAX_INT 2147483647

// check true or false enum
typedef enum e_bool
{
	_false,
	_true
}	t_bool;

typedef struct s_pos
{
	float		x;
	float		y;
}	t_pos;

// state enum
typedef enum e_state
{
	facing_up,
	facing_down,
	facing_left,
	facing_right
}	t_state;

typedef struct s_door{
	int				index;
	int				x;
	int				y;
	t_bool			is_open;
	t_bool			active;
	struct s_door	*next;
}	t_door;

// rays data
typedef struct s_rays
{
	int		index;
	float	ray_angle;
	float	wall_hit_x;
	float	wall_hit_y;
	float	distance;
	t_pos	intersection;
	t_bool	was_hit_vertical;
	int		y_texture;
	double	x_texture;
	float	y_offset;
	float	x_offset;
	t_bool	was_door;
	t_bool	was_open;
	t_bool	door_hit_vertical;
	int		x_door;
	int		y_door;
	t_state	state;
}				t_rays;

typedef struct s_hit_pos
{
	float	x_intercept;
	float	y_intercept;
	float	x_step;
	float	y_step;
	float	wall_hit_x;
	float	wall_hit_y;
	float	next_x;
	float	next_y;
	float	x_to_check;
	float	y_to_check;
}	t_hit_pos;

// DDA variables
typedef struct s_DDA{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	steps;
	float	xinc;
	float	yinc;
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

// struct for textures
typedef struct s_texture
{
	void			*img;
	char			*addr;
	int				bpp;
	int				size_line;
	int				endian;
	int				width;
	int				height;
}				t_texture;

// Struct for the compass
typedef struct s_compass
{
	t_type				type;
	char				*path;
	t_texture			texture;
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
	float		rot_angle;
	float		move_speed;
	float		move_speed_side;
	float		rot_speed;
}	t_player;

// main struct data
typedef struct s_cub
{
	float			fov_angle;
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
	float			x;
	float			y;
	void			*wall;
	void			*mlx;
	void			*win;
	void			*img;
	void			*player_img;
	void			*line;
	t_texture		texture_door;
	t_texture		texture_open_door;
	int				distance_proj_plane;
	int				wall_strip_height;
	t_bool			mouse_hide;
	t_bool			on_space;
	t_bool			on_dis;
	t_door			*door;
	int				*tab;
	int				x_door;
	int				y_door;
	int				open;
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
void		open_image_door(t_cub *cub);

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
void		checking_valid_map(char **map, int i, int j, t_cub *cub);

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
int			mouse_move(int x, int y, void *param);
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
void		cast_all_rays(t_cub *cub);
int			ft_atoi_base(char *str, char *base);
float		normalize_angle(float angle);

void		ft_door_add_back(t_door **lst, t_door *new);
t_door		*ft_door_new(int index, int x, int y);
void		search_door(t_door *lst, int x, int y, float distance);
void		checking_door(t_cub *cub);
t_door		*get_door(t_door *door, int x, int y);

t_pos		check_vertical(t_cub *cub, float ray_angle);
t_pos		check_horizontal(t_cub *cub, float ray_angle);
t_pos		finding_distance(t_pos p, t_pos h_p, t_pos v_p, t_cub *cub);
float		normalize_angle(float angle);
t_state		checking_state(float ray_angle, int check);
t_bool		check_wall(int x, int y, t_cub *cub);

int			mouse_click(int button, int x, int y, t_cub *cub);
int			mouse_start(int button, int x, int y, t_cub *cub);
int			mouse_init(t_cub *cub);
void		hook_start(t_cub *cub);
t_bool		check_circle_next(int x, int y, int radius, t_cub *cub);
t_bool		check_circle(int x, int y, int radius, t_cub *cub);
t_bool		is_wall(int x, int y, t_cub *cub);
void		open_image(t_cub *cub, t_compass *tmp);
void		open_image_door(t_cub *cub);
void		open_door(t_cub *cub);

void		set_door(t_cub *cub);

int			create_trgb(int t, t_color color);
void		put_pixel(int color, t_cub *cub);
t_texture	set_color(t_cub *cub);
float		get_x_intersection(t_cub *cub);
void		draw_celling(t_cub *cub);
void		draw_floor(t_cub *cub);
void		add_textures(t_cub *cub, t_texture texture);
void		draw_circle_player(t_cub *cub, int x, int y, int color);
void		simple_draw_line(t_pos pos, t_pos pos1, t_cub *cub,
				t_pos incr_color);

#endif