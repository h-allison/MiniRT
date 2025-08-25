/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:03:40 by hallison          #+#    #+#             */
/*   Updated: 2025/08/25 07:25:07 by matthias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include "libft.h"
#include <MLX42/MLX42.h>
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>

# define TRUE 1
# define FALSE 0

# define X 0
# define Y 1
# define Z 2

# define R 0
# define G 1
# define B 2

# define EPSILON 0.0001

typedef enum e_error
{
	ERROR_WRONG_ARGS,
	ERROR_FILENAME,
	ERROR_OPEN,
	ERROR_WRONG_CHARS,
}	t_error;

typedef struct s_ambient
{
	float			ratio; // range [0.0, 1.0]
	unsigned int	rgb[3]; // [0-255]
}	t_ambient;

typedef struct s_tuple
{
	float			x;
	float			y;
	float			z;
	float			w;
}	t_tuple;

typedef struct s_camera
{
	float			viewpoint[3]; // zB. -50.0,0,20
	float			vector; // range [-1,1]
	unsigned int	fov; // field of view, range [0,180]
}	t_camera;

typedef struct s_light
{
	float			light_point[3]; // X, Y, Z
	float			brightness; // range [0.0,1.0]
	// for bonus only:
	unsigned int	rgb[3];	
}	t_light;

typedef struct s_sphere
{
	float			center[3]; // signed?
	float			diameter;
	unsigned int	rgb[3];
}	t_sphere;

typedef struct s_plane
{
	float	point[3]; // coordinates
	float	vectors[3]; // range [-1.1]
	int		rgb[3];
}	t_plane;

typedef struct s_cyl
{
	float			center[3]; // signed?
	float			axis[3]; // range [-1,1], 1 each coordinate
	float			diam;
	float			height;
	unsigned int	rgb[3];
}	t_cyl;

typedef struct s_data
{
	char		*filename;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	t_ambient	*ambient;
	t_camera	*camera;
	t_light		*light;
	t_sphere	**sphere;
	t_plane		**plane;
	t_cyl		**cyl;
}	t_data;

//check_file.c
int		scenefile_check_chars(char *filename);
//file_helpers.c
int		open_file(char *filename);
int		check_rt_filename(char	*filename);
//error_handling.c
void	rt_early_exit(int error);
//parsing.c
int		parse_file(char *filename, t_data *data);
//create_tuples.c
t_tuple	point(float x, float y, float z);
t_tuple vector(float x, float y, float z);
//math_float.c
int		fisequal(float a, float b);
//math_tuples_1.c
int		tisequal(t_tuple a, t_tuple b);
t_tuple	tadd(t_tuple a, t_tuple b);
t_tuple	tsub(t_tuple a, t_tuple b);
t_tuple	tneg(t_tuple a);
//math_tuples_2.c
t_tuple	tmult(t_tuple a, float scalar);
t_tuple	tdiv(t_tuple a, float scalar);
float	tmag(t_tuple a);
t_tuple	tnorm(t_tuple a);
//math_tuples_3.c
float	dot(t_tuple a, t_tuple b);
t_tuple	cross(t_tuple a, t_tuple b);

#endif
