/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:03:40 by hallison          #+#    #+#             */
/*   Updated: 2025/08/22 17:14:17 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACER_H
# define RAYTRACER_H

# include "includes/libft.h"
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <mlx.h>
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

typedef enum e_error
{
	ERROR_NOFILE,
	ERROR_FILENAME,
	ERROR_OPEN,
} t_error;

typedef struct s_ambient
{
	float ratio; // range [0.0, 1.0]
	unsigned int rgb[3]; // [0-255]
} t_ambient;

typedef struct s_camera
{
	float view[3]; // zB. -50.0,0,20
	float vector[3]; // range [-1,1]
	unsigned int	fov; // field of view, range [0,180]
} t_camera;

typedef struct s_light
{
	float point[3]; // X, Y, Z
	float brightness; // range [0.0,1.0]
	// for bonus only:
	unsigned int rgb[3];	
} t_light;

typedef struct s_sphere
{
	float center[3]; // signed?
	float diameter;
	unsigned int	rgb[3];
} t_sphere;

typedef struct s_plane
{
	float	point[3]; // coordinates
	float	vectors[3]; // range [-1.1]
	int	rgb[3];
} t_plane;

typedef struct s_cyl
{
	float center[3]; // signed?
	float axis[3]; // range [-1,1], 1 each coordinate
	float diam;
	float	height;
	unsigned int	rgb[3];
} t_cyl;

typedef struct s_data
{
	char	*file_name;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	t_ambient *ambient;
	t_camera *camera;
	t_light *light;
	t_sphere **sphere;
	t_plane **plane;
	t_cyl	**cyl;
} t_data;

#endif
