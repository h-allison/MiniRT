/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_p.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 11:19:13 by hallison          #+#    #+#             */
/*   Updated: 2025/09/18 17:54:21 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINIRTP_H
# define MINIRTP_H

# include "libft.h"
# include "minirt.h"
# include <stdbool.h>

#define	BONUS false

typedef enum e_element
{
	AMBIENT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYL,
}	t_element;

typedef struct s_tok_ambient
{
	float			ratio; // range [0.0, 1.0]
	unsigned int	rgb[3]; // [0-255]
}	t_tok_ambient;


typedef struct s_tok_camera
{
	float			viewpoint[3]; // zB. -50.0,0,20
	float			vector[3]; // range [-1,1]
	unsigned int	fov; // field of view, range [0,180]
}	t_tok_camera;

typedef struct s_tok_light
{
	float			light_point[3]; // X, Y, Z
	float			brightness; // range [0.0,1.0]
	// for bonus only:
	unsigned int	rgb[3];
}	t_tok_light;

typedef struct s_tok_sphere
{
	float			center[3]; // signed?
	float			diameter;
	unsigned int	rgb[3];
}	t_tok_sphere;

typedef struct s_tok_plane
{
	float	point[3]; // coordinates
	float	vectors[3]; // range [-1.1]
	int		rgb[3];
}	t_tok_plane;

typedef struct s_tok_cyl
{
	float			center[3]; // signed?
	float			axis[3]; // range [-1,1], 1 each coordinate
	float			diam;
	float			height;
	unsigned int	rgb[3];
}	t_tok_cyl;

typedef struct	s_checklist
{
	bool	a_parsed;
	bool	c_parsed;
	bool	l_parsed;
	int		count_light;
	int		count_sphere;
	int		count_cyl;
	int		count_cube;
	int		count_plane;
	int		count_cone;
//	t_light	**light;
//	t_shape	**shape;
}	t_checklist;

#endif
