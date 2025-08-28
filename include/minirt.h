/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:03:40 by hallison          #+#    #+#             */
/*   Updated: 2025/08/28 12:28:18 by hallison         ###   ########.fr       */
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

typedef struct s_rgb
{
	float			r;
	float			g;
	float			b;
}	t_rgb;

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
	mlx_t		*mlx;
	mlx_image_t	*img;
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
t_tuple	create_point(float x, float y, float z);
t_tuple create_vector(float x, float y, float z);
t_rgb	create_color(int r, int g, int b);

//create_matrices.c
void	free_matrix(float **m, int size);
float	**alloc_matrix(int size);
float	**create_id_matrix(void);

//math_float.c
bool	fisequal(float a, float b);

//math_tuples_1.c
bool	tisequal(t_tuple a, t_tuple b);
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

//math_colors.c
t_rgb   cadd(t_rgb c1, t_rgb c2);
t_rgb   csub(t_rgb c1, t_rgb c2);
t_rgb   cscale(t_rgb c1, float s);
t_rgb	cmult(t_rgb c1, t_rgb c2);
int		color_to_hex(t_rgb color);

//math_matrices.c
bool	misequal(float **m1, float **m2, int size);
float	**matrixmult(float **m1, float **m2);
t_tuple tmatrixmult(float **m, t_tuple t);
float	**mtranspose(float **m1, int size);

//math_matrices_2.c
float	mdet_2x2(float **m);
float	**msubmatrix(float **m, int size, int row, int col);
float	mminor3x3(float **m, int row, int col);
float	mcofactor3x3(float **m, int row, int col);
float	mdet(float **m, int size);

//export_ppmm.c
int		canvas_export_ppm(t_data *data);
#endif
