/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:22:28 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/09 17:58:12 by aaggoujj         ###   ########.fr       */
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
	EA
}			t_type;

// Struct for the compass
typedef struct s_compass
{
	t_type				type;
	char				*path;
	struct s_compass	*next;
	struct s_compass	*prev;
}	t_compass;

//main struct data
typedef struct s_cub
{
	t_compass	*compass;
	char		**map;
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

//list compass functions
t_compass	*ft_d_lstnew(char *content, t_type type);
void		ft_d_lstadd_front(t_compass **alst, t_compass *new);
void		ft_d_lstadd_back(t_compass **alst, t_compass *new);

//cub tools functions
char		*append_char(char *str, char c);

//parsing functions
void		error_file(int fd);
void		error_infomation(int c);
t_bool		check_path(char	*path);
t_bool		check_order(int type, int *c);
t_type		check_type(char *str);
char		*get_path(char *str);
int			check_format(char *file);

#endif