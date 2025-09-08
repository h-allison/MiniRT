/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:03:40 by hallison          #+#    #+#             */
/*   Updated: 2025/09/08 15:08:34 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include <MLX42/MLX42.h>
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>

# define WIN_WIDTH 600
# define WIN_HEIGHT 600

# define EPSILON 0.0001
# define DEG2RAD (M_PI / 180.0)
# define RAD2DEG (180.0 / M_PI)

typedef enum e_error
{
	ERROR_WRONG_ARGS,
	ERROR_FILENAME,
	ERROR_OPEN,
	ERROR_WRONG_CHARS,
}	t_error;

typedef enum e_objtype
{	
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYL,
}	t_objtype;

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

typedef struct s_lcalc
{
	t_rgb	effective_color;
	t_rgb	ambient;
	t_rgb	diffuse;
	t_rgb	specular;
	t_tuple	lightv;
	t_tuple	reflectv;
	float	light_dot_normal;
	float	reflect_dot_eye;
	float	factor;
}	t_lcalc;

typedef struct s_material
{
	t_rgb			color;
	float			ambient;	
	float			diffuse;
	float			specular;
	float			shininess;
}	t_material;

typedef struct s_light
{
	t_rgb			intensity;
	t_tuple			position;
}	t_light;

typedef struct s_object
{
	int				objtype;
	float			**transform;
	t_material		m;
}	t_object;


typedef struct s_camera
{
	float			hsize;
	float			vsize;
	float			field_of_view;
	float			half_width;
	float			half_height;
	float			pixel_size;
	float			**transform;
}	t_camera;

typedef	struct s_comps
{
	float			t;
	t_object		*object;
	t_tuple			point;
	t_tuple			eyev;
	t_tuple			normalv;
	bool			inside;
}	t_comps;

typedef struct s_world
{
	t_object	*s;
	t_light		*light;
}	t_world;

typedef struct s_largs
{
	t_material		material;
	t_tuple			point;
	t_light			light;
	t_tuple			eyev;
	t_tuple			normalv;
}	t_largs;

typedef struct s_ray
{
	t_tuple			origin;
	t_tuple			direction;
}	t_ray;

typedef	struct s_intersection
{
	t_object		*object;
	float			t;
}	t_intersection;

typedef struct s_data
{
	char		*filename;
	mlx_t		*mlx;
	mlx_image_t	*img;
}	t_data;

//check_file.c
int		scenefile_check_chars(char *filename);

//file_helpers.c
int		open_file(char *filename);
int		check_rt_filename(char	*filename);

//error_handling.c
void	rt_early_exit(int error);

//mlx_handling.c
int		mlx_handling(t_data *data);
void	ft_hook(void* param);
void	img_wipe(t_data *data, t_rgb color);

//parsing.c
int		parse_file(char *filename, t_data *data);

//rendering.c
void	render(void *param);

//create_objects.c
t_object sphere();
t_light	point_light(t_tuple position, t_rgb intensity);
t_world	default_world();
t_camera	camera(float hsize, float vsize, float field_of_view);

//create_tuples.c
t_tuple	point(float x, float y, float z);
t_tuple	vector(float x, float y, float z);
t_rgb	color(float r, float g, float b);

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
t_rgb	cadd(t_rgb c1, t_rgb c2);
t_rgb	csub(t_rgb c1, t_rgb c2);
t_rgb	cscale(t_rgb c1, float s);
t_rgb	cmult(t_rgb c1, t_rgb c2);
int		color_to_hex(t_rgb color);

//math_matrices_1.c
bool	misequal(float **m1, float **m2, int size);
float	matrixdot(float **m, int y, t_tuple t);
float	**mtranspose(float **m1, int size);
float	**mtransposefree(float **m, int size);

//math_matrices_2.c
float	**matrixmult(float **m1, float **m2);
float	**mmultfree(float **m1, float **m2);
t_tuple	tmatrixmult(float **m, t_tuple t);
t_tuple	tmmultfree(float **m, t_tuple t);

//math_matrices_3.c
float	**msubmatrix(float **m, int size, int row, int col);
float	mminor3x3(float **m, int row, int col);
float	mcofactor3x3(float **m, int row, int col);
float	mcofactor4x4(float **m, int size, int row, int col);

//math_matrices_4.c
float	mdet2x2(float **m);
float	mdet3x3(float **m, int size);
float	mdet(float **m, int size);
float	**minvert(float **m, int size);
bool	minvertable(float **m, int size);

//math_transform.c
float	**translation(float x, float y, float z);
float	**scaling(float x, float y, float z);
float	**rotation_x(float r);
float	**rotation_y(float r);
float	**rotation_z(float r);

//math_transform_2.c
float	**shearing(float *shear);

//math_shading.c
t_tuple	normal_at(t_object *s, t_tuple p);
t_tuple	reflect(t_tuple in, t_tuple normal);
t_rgb	lighting(t_largs *largs);

//math_shading_2.c
t_rgb	shade_hit(t_world *w, t_comps *comps);
t_rgb	color_at(t_world *w, t_ray *r);

//math_rays.c
t_ray	ray(t_tuple point, t_tuple vector);
t_tuple	position(t_ray ray, float t);
t_ray	transform(t_ray r, float **m);
void	set_transform(t_object *s, float **t);
t_ray	ray_for_pixel(t_camera c, float px, float py);

//math_intersections.c
t_intersection	*intersect(t_object *s, t_ray r);
t_intersection	intersection(float t, t_object *s);
t_intersection	*intersections(t_intersection i1, t_intersection i2);
t_intersection	*hit(t_intersection *xs);

//math_intersections_2.c
t_intersection	*intersect_world(t_world *w, t_ray *r);
t_comps prepare_computations(t_intersection *i, t_ray *r);

//math_view.c
float	**view_transform(t_tuple from, t_tuple to, t_tuple up);

//export_ppm.c
int		canvas_export_ppm(t_data *data);

#endif
