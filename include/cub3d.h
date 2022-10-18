/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:22:28 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/18 13:15:44 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <MLX42.h>
# include "../lib/libft/include/libft.h"
# include "get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <sys/errno.h>

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
	int		x;
	int		y;
}	t_pos;

// main struct data
typedef struct s_cub
{
	t_compass	*compass;
	char		**map;
	t_color		floor;
	t_color		celling;
	t_pos		player;
}	t_cub;

void		parsing(char *map, t_cub *cub);
// Boolean struct
typedef enum e_bool
{
	_false,
	_true
}	t_bool;

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
void	    ft_d_lstclear(t_compass **lst);
void	    ft_d_lstdelone(t_compass *lst);

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

//free data functions
void		free_tab(char **tab);
void		free_data(t_cub *cub);

#endif