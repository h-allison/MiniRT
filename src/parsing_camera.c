/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:51:51 by hallison          #+#    #+#             */
/*   Updated: 2025/09/29 16:30:09 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_camera_coords(char *token, t_tuple *coords)
{
	if (rt_atof_tuple(token, coords) != 0)
		return(rt_error("C: camera viewpoint: invalid input", -1));
//	printf("Camera coords = %f, %f, %f, %f\n", coords->x, coords->y, coords->z, coords->w);
	return (0);
}

int	parse_camera_orient(char *token, t_tuple *orient)
{
	if (rt_atof_tuple(token, orient) != 0)
		return(rt_error("C: camera orientation: invalid input", -1));
//	printf("Camera orient = %f, %f, %f, %f\n", orient->x, orient->y, orient->z, orient->w);
	return (0);
}

// TODO malloc exit
t_camera	*place_camera(t_tuple c_coords, t_tuple c_orient, float fov)
{
	t_camera	*cam;
	t_tuple		to;
	t_tuple		up;

	cam = camera(WIN_WIDTH, WIN_HEIGHT, DEG2RAD * fov);
	if (!cam)
		exit (1);
	to = tadd(c_coords, c_orient);
/*	
	if (fisequal(c_orient.x, 0) && fisequal(c_orient.y, 1) && fisequal(c_orient.z, 0))
		up = vector(0, .9, 0);
	else 
		up = vector(0, 1, 0);
*/
	up = vector(0, 1, 0);
	free_matrix(cam->transform, 4);
	cam->transform = view_transform(c_coords, to, up);
	return (cam);
}	

int	parse_camera_fov(char *token, float *fov)
{
	if (rt_atof(token, fov) != 0)
		return(rt_error("C: field of view: invalid input", -1));
	if (*fov < 0 || *fov > 180)
		return(rt_error("C: field of view: must be in range [0, 180]", -1));
	return (0);
}

int	parse_camera(char **tokens, t_data *data)
{
	t_tuple	c_coords;
	t_tuple	c_orient;
	float	field_of_view;

	c_coords = point(0, 0, 0);
	c_orient = vector(0, 0, 0);
	field_of_view = 0;
	if (!tokens[1])
		return(rt_error("C: camera coordinates: missing values", -1));
	if (parse_camera_coords(tokens[1], &c_coords) != 0)
		return (-1);
	if (!tokens[2])
		return(rt_error("C: camera orientation: missing values", -1));
	if (parse_camera_orient(tokens[2], &c_orient) != 0)
		return (-1);
	if (check_v_normalized(c_orient, "C: camera orientation") != 0)
		return (-1);
	c_orient = tnorm(c_orient);
	if (!tokens[3])
		return(rt_error("C: field of view: missing value", -1));
	if (parse_camera_fov(tokens[3], &field_of_view) != 0)
		return (-1);
	if (tokens[4])
		return(rt_error("C: too many arguments", -1));
	data->cam = place_camera(c_coords, c_orient, field_of_view);
	return(0);
}

