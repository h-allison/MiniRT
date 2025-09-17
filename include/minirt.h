/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:53:42 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/17 21:55:57 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include <MLX42/MLX42.h>
# include <math.h>
# include <float.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>

# define WIN_WIDTH 1024
# define WIN_HEIGHT 768

# define MAX_RECURSION 10
# define OFFSET	 0.001
# define EPSILON 0.0001

# define DEG2RAD 0.017453292519943
# define RAD2DEG 57.295779513082
/*# define DEG2RAD  M_PI / 180.0
# define RAD2DEG 180.0 / M_PI*/

typedef enum e_error
{
	ERROR_WRONG_ARGS,
	ERROR_FILENAME,
	ERROR_OPEN,
	ERROR_WRONG_CHARS,
}	t_error;

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

typedef struct s_pattern t_pattern;

typedef struct s_pattern
{
	t_rgb			a;
	t_rgb			b;
	float			**transform;
	float			**invtrans;
	t_rgb			(*pattern_at)(t_pattern *, t_tuple);
	bool			status;
}	t_pattern;

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
	t_pattern		pattern;
	float			ambient;	
	float			diffuse;
	float			specular;
	float			shininess;
	float			reflective;
	float			transparency;
	float			refractive_index;
}	t_material;

typedef struct s_light
{
	t_rgb			intensity;
	t_tuple			position;
	bool			last;
}	t_light;

typedef struct s_ray
{
	t_tuple			origin;
	t_tuple			direction;
}	t_ray;

typedef struct s_shape t_shape;
typedef struct s_intersection t_intersection;

typedef struct s_shape
{
	int				type;
	t_tuple			(*local_normal_at)(t_shape *, t_tuple);
	t_intersection	*(*local_intersect)(t_shape *);
	float			**transform;
	float			**invtrans;
	t_material		m;
	t_ray			saved_ray;
	float			minimum;
	float			maximum;
	bool			closed;
}	t_shape;

typedef struct s_containers
{
	t_shape				*content;
	struct s_containers	*next;
} t_containers;

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

typedef struct s_comps
{
	float			t;
	t_shape			*object;
	t_tuple			point;
	t_tuple			over_point;
	t_tuple			under_point;
	t_tuple			eyev;
	t_tuple			normalv;
	t_tuple			reflectv;
	float			n1;
	float			n2;
	bool			inside;
}	t_comps;

typedef struct s_world
{
	t_shape			*s;
	t_light			*light;
}	t_world;

typedef struct s_largs
{
	t_shape			*shape;
	t_material		material;
	t_tuple			point;
	t_light			light;
	t_tuple			eyev;
	t_tuple			normalv;
	bool			in_shadow;
}	t_largs;

typedef struct s_intersection
{
	t_shape			*object;
	float			t;
}	t_intersection;

typedef struct s_data
{
	char		*filename;
	mlx_t		*mlx;
	mlx_image_t	*img;
}	t_data;

typedef struct s_tminmax
{
	float	xtmin;
	float	ytmin;
	float	ztmin;
	float	xtmax;
	float	ytmax;
	float	ztmax;
}	t_tminmax;

//check_file.c
int				scenefile_check_chars(char *filename);

//file_helpers.c
int				open_file(char *filename);
int				check_rt_filename(char	*filename);

//error_handling.c
void			rt_early_exit(int error);

//mlx_handling.c
int				mlx_handling(t_data *data);
void			ft_hook(void *param);
void			img_wipe(t_data *data, t_rgb color);

//parsing.c
int				parse_file(char *filename, t_data *data);

//rendering.c
void			render(void *param);

//create_objects.c
t_pattern		pattern(void);
t_material		material(void);
t_shape			create_test_shape(void);
t_pattern		create_test_pattern(void);
t_shape			glass_sphere(void);
t_shape			sphere(void);
t_shape			plane(void);
t_shape			cube(void);
t_shape			cylinder(void);
t_shape			cone(void);
t_light			point_light(t_tuple position, t_rgb intensity);
t_world			default_world(void);
t_world			default_world_2(void);
t_world			default_world_3(void);
t_world			default_world_4(void);
t_world			default_world_5(void);
t_camera		camera(float hsize, float vsize, float field_of_view);

//create_tuples.c
t_tuple			point(float x, float y, float z);
t_tuple			vector(float x, float y, float z);
t_rgb			color(float r, float g, float b);

//create_matrices.c
void			free_matrix(float **m, int size);
float			**alloc_matrix(int size);
float			**create_id_matrix(void);

//math_float.c
bool			fisequal(float a, float b);

//math_tuples_1.c
bool			tisequal(t_tuple a, t_tuple b);
t_tuple			tadd(t_tuple a, t_tuple b);
t_tuple			tsub(t_tuple a, t_tuple b);
t_tuple			tneg(t_tuple a);

//math_tuples_2.c
t_tuple			tmult(t_tuple a, float scalar);
t_tuple			tdiv(t_tuple a, float scalar);
float			tmag(t_tuple a);
t_tuple			tnorm(t_tuple a);

//math_tuples_3.c
float			dot(t_tuple a, t_tuple b);
t_tuple			cross(t_tuple a, t_tuple b);

//math_colors.c
t_rgb			cadd(t_rgb c1, t_rgb c2);
t_rgb			csub(t_rgb c1, t_rgb c2);
t_rgb			cscale(t_rgb c1, float s);
t_rgb			cmult(t_rgb c1, t_rgb c2);
int				color_to_hex(t_rgb color);

//math_matrices_1.c
bool			misequal(float **m1, float **m2, int size);
float			matrixdot(float **m, int y, t_tuple t);
float			**mtranspose(float **m1, int size);
float			**mtransposefree(float **m, int size);

//math_matrices_2.c
float			**matrixmult(float **m1, float **m2);
float			**mmultfree(float **m1, float **m2);
t_tuple			tmatrixmult(float **m, t_tuple t);
t_tuple			tmmultfree(float **m, t_tuple t);

//math_matrices_3.c
float			**msubmatrix(float **m, int size, int row, int col);
float			mminor3x3(float **m, int row, int col);
float			mcofactor3x3(float **m, int row, int col);
float			mcofactor4x4(float **m, int size, int row, int col);

//math_matrices_4.c
float			mdet2x2(float **m);
float			mdet3x3(float **m, int size);
float			mdet(float **m, int size);
float			**minvert(float **m, int size);
float			**minvert_free(float **m, int size);
bool			minvertable(float **m, int size);

//math_transform.c
float			**translation(float x, float y, float z);
float			**scaling(float x, float y, float z);
float			**rotation_x(float r);
float			**rotation_y(float r);
float			**rotation_z(float r);

//math_transform_2.c
float			**shearing(float *shear);

//math_shading.c
t_tuple			local_normal_at_sphere(t_shape *s, t_tuple local_point);
t_tuple			local_normal_at_plane(t_shape *s, t_tuple local_point);
t_tuple			local_normal_at_cube(t_shape *s, t_tuple local_point);
t_tuple			local_normal_at_cyl(t_shape *s, t_tuple local_point);
t_tuple			local_normal_at_cone(t_shape *s, t_tuple local_point);
t_tuple			local_normal_at(t_shape *s, t_tuple local_point);
t_tuple			normal_at(t_shape *s, t_tuple p);
t_tuple			reflect(t_tuple in, t_tuple normal);
t_rgb			lighting(t_largs *largs);

//math_shading_2.c
t_rgb			shade_hit(t_world *w, t_comps *comps, int remaining);
t_rgb			color_at(t_world *w, t_ray *r, int remaining);
bool			is_shadowed(t_world *world, int i, t_tuple point);

//math_rays.c
t_ray			ray(t_tuple point, t_tuple vector);
t_tuple			position(t_ray ray, float t);
t_ray			transform(t_ray r, float **m);
void			set_transform(t_shape *s, float **t);
t_ray			ray_for_pixel(t_camera *c, float px, float py);

//math_intersections.c
t_intersection	*local_intersect_sphere(t_shape *s);
t_intersection	*local_intersect_plane(t_shape *s);
t_intersection	*local_intersect_cube(t_shape *s);
float			maxf(float a, float b, float c);
void			swapf(float *a, float *b);
t_intersection	*local_intersect_cyl(t_shape *s);
t_intersection	*local_intersect_cone(t_shape *s);
t_intersection	*local_intersect(t_shape *s);
t_intersection	*intersect(t_shape *s, t_ray r);
t_intersection	intersection(float t, t_shape *s);
t_intersection	*intersections(t_intersection i1, t_intersection i2);
t_intersection	*hit(t_intersection *xs);

//math_intersections_2.c
t_intersection	*intersect_world(t_world *w, t_ray *r);
t_comps			prepare_computations(t_intersection *i, t_ray *r, t_intersection *xs);

//math_view.c
float			**view_transform(t_tuple from, t_tuple to, t_tuple up);

//export_ppm.c
int				canvas_export_ppm(t_data *data);

//patterns.c
t_pattern		stripe_pattern(t_rgb a, t_rgb b);
t_rgb			stripe_at(t_pattern *pat, t_tuple point);
t_rgb			stripe_at_object(t_pattern *pat, t_shape *object, t_tuple point);
t_pattern		gradient_pattern(t_rgb a, t_rgb b);
t_rgb			gradient_at(t_pattern *gradient, t_tuple point);
t_pattern		ring_pattern(t_rgb a, t_rgb b);
t_rgb			ring_at(t_pattern *ring, t_tuple point);
t_pattern		checkers_pattern(t_rgb a, t_rgb b);
t_rgb			checkers_at(t_pattern *checkers, t_tuple point);
t_rgb			pattern_at(t_pattern *pat, t_tuple point);
t_rgb			pattern_at_shape(t_pattern *pat, t_shape *shape, t_tuple point);
void			set_pattern_transform(t_pattern *pat, float **t);

//reflection.c
t_rgb			reflected_color(t_world *w, t_comps *comps, int remaining);
t_rgb			refracted_color(t_world *w, t_comps *comps, int remaining);
float			schlick(t_comps *comps);

//free.c
int				free_matrices_and_ret(t_shape *p, int ret);

//world_scenes.c
t_world			default_world_6(void);
t_world			default_world_cyl(void);
#endif
