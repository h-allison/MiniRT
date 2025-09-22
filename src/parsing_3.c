/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 11:19:08 by hallison          #+#    #+#             */
/*   Updated: 2025/09/18 17:54:06 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_ambient_rgb(char *token, t_world *world)
{
	int		ret;

	ret = 0;
	world->ambient_rgb.r = 0;
	world->ambient_rgb.g = 0;
	world->ambient_rgb.b = 0;
	ret = rt_atorgb(token, &world->ambient_rgb);
	if (ret != 0)
		return(rt_error("A: ambient color: invalid input", -1));
	if (world->ambient_rgb.r < 0 || world->ambient_rgb.r > 255)
		return(rt_error("A: ambient color: rgb not in range 0-255", -1));
	if (world->ambient_rgb.g < 0 || world->ambient_rgb.g > 255)
		return(rt_error("A: ambient color: rgb not in range 0-255", -1));
	if (world->ambient_rgb.b < 0 || world->ambient_rgb.b > 255)
		return(rt_error("A: ambient color: rgb not in range 0-255", -1));
	printf("Ambient color = %f, %f, %f\n", world->ambient_rgb.r, world->ambient_rgb.g, world->ambient_rgb.b);
	return (0);
}

int	parse_ambient_ratio(char *token, t_world *world)
{
	int		ret;

	ret = 0;
	world->ambient_ratio = 0;
	ret = rt_atof(token, &world->ambient_ratio);
	if (ret != 0)
		return(rt_error("A: ambient ratio: invalid input", -1));
	if (world->ambient_ratio < 0 || world->ambient_ratio > 1)
		return(rt_error("A: ambient ratio: must be in range [0.0, 1.0]", -1));
	printf("Ambient ratio = %f\n", world->ambient_ratio);
	return (0);
}

int	parse_ambient(char **tokens, t_world *world)
{
	if (!tokens[1])
		return(rt_error("A: ambient ratio: missing value", -1));
	if (parse_ambient_ratio(tokens[1], world) != 0)
		return (-1);
	if (!tokens[2])
		return(rt_error("A: ambient color: missing values", -1));
	if (parse_ambient_rgb(tokens[2], world) != 0)
		return (-1);
	if (tokens[3])
		return(rt_error("A: too many arguments", -1));
	return(0);
}

int	parse_camera_coords(char *token, t_tuple *coords)
{
	if (rt_atof_tuple(token, &coords) != 0)
		return(rt_error("C: camera viewpoint: invalid input", -1));
	return (0);
}

int	parse_camera_orient(char *token, t_tuple *coords)
{
	if (rt_atof_tuple(token, &coords) != 0)
		return(rt_error("C: camera orientation: invalid input", -1));
	return (0);
}

int	btwn_negative_and_positive_1(t_tuple t)
{
	if (t.x < -1 || t.x > 1)
		return (-1);
	if (t.y < -1 || t.y > 1)
		return (-1);
	if (t.z < -1 || t.z > 1)
		return (-1);
	return (0);
}

// TODO malloc exit

int	place_camera(t_tuple c_coords, t_tuple c_orient, float fov)
{
	t_camera	cam;
	t_tuple		to;
	float		**v_transform;

	cam = malloc(sizeof(t_camera);
	if (!cam)
		exit (1);
	cam = camera(WIN_WIDTH, WIN_HEIGHT, fov);
	to = tadd(c_coords, c_orient);
	up = ray(0, 1, 0); 
	v_transform = view_transform(c_coords, to, up);
	// TODO next: can't use set_transform here
	// but can create a new function or duplicate its
	// behavior for both camera transform and invtrans
}	

int	parse_camera(char **tokens, t_world *world)
{
	t_tuple	c_coords;
	t_tuple	c_orient;
	float	field_of_view;

	camera_cords = point(0, 0, 0);
	camera_orient = ray(0, 0, 0);
	if (!tokens[1])
		return(rt_error("C: camera coordinates: missing values", -1));
	if (parse_camera_coords(tokens[1], &c_cords) != 0)
		return (-1);
	if (!tokens[2])
		return(rt_error("C: camera orientation: missing values", -1));
	if (parse_camera_orient(tokens[2], &c_orient) != 0)
		return (-1);
	if (!(btwn_negative_and_positive_1(c_orient)
		return(rt_error("A: camera orientation: must be in range [-1.0, 1.0]", -1));
	if (!tokens[3])
		return(rt_error("C: field of view: missing value", -1));
	if (parse_camera_fov(tokens[3], &field_of_view) != 0)
		return (-1);
	if (tokens[4])
		return(rt_error("C: too many arguments", -1));
	world->cam = place_camera(c_coords, c_orient, field_of_view);
	return(0);
}

int	parse_singular_element(char **tokens, t_data *data)
{
	if (tokens[0][0] == 'A' && tokens[0][1] == '\0')
	{	
		if (parse_ambient(tokens, data->world) == -1)
			return(-1);
	}
	else if (tokens[0][0] == 'C' && tokens[0][1] == '\0')
	{	
		if (parse_camera(tokens, data->world) == -1)
			return(-1);
	}
	else if (tokens[0][0] == 'L' && tokens[0][1] == '\0')
	   printf("<parse into Light>\n");	
	return(0);	
}

void	init_checklist(t_checklist *checklist)
{
	checklist->a_parsed = false;
	checklist->c_parsed = false;
	checklist->l_parsed = false;
}

int	parse_into_world(char **tokens, t_data *data)
{
	static	int		first_line;
	
	if (first_line == 0)
	{
		data->world = malloc(sizeof(t_world));
		if (!data->world)
			exit (1);
		init_checklist(&data->world->checklist);
		first_line = 1;
	}
	if (tokens[0][0] >= 'A' && tokens[0][0] <= 'Z')
		return (parse_singular_element(tokens, data));
	// when ambient is encountered, save to apply to all objects at the end
	/*
	(void) tokens;
	return (0);
	*/
	return (0);
}
