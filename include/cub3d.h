/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:22:28 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/13 14:20:15 by moseddik         ###   ########.fr       */
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

// main struct data
typedef struct s_cub
{
	t_compass	*compass;
	char		**map;
	t_color		floor;
	t_color		celling;
}	t_cub;

void		parsing(char *map, t_cub *cub);
// Boolean struct
typedef enum e_bool
{
	_false,
	_true
}	t_bool;

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

// cub tools functions
char		*append_char(char *str, char c);

// parsing functions
void		error_file(int fd);
void		error_infomation(int c);
t_bool		check_path(char	*path);
t_type		check_type(char *str);
char		*get_path(char *str);
int			check_format(char *file);
void		parse_color(t_cub *cub, int *c, char *line);
int			count_vergul(char *str);
t_color		get_color_value(char *str, t_type type);
t_color		get_color(char *line);
t_bool		check_newline(char *line);
t_bool		check_digit(char **args);
char		*get_str(char *line);




#endif