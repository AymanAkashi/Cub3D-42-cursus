/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:22:28 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/09 14:28:35 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <MLX42.h>
# include "get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
#include <sys/errno.h>

void	parsing(char *map);

// Boolean struct
typedef enum e_bool
{
	_false,
	_true
}	t_bool;

// Coloring output functions
void	red(void);
void	blue(void);
void	yellow(void);
void	purple(void);
void	reset(void);

#endif