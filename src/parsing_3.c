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

int	parse_camera_coords(char *token, t_camera *cam)
{
	t_tuple	coords;
	
	coords = point(0, 0, 0);
	if (rt_atof_tuple(token, &coords) != 0)
		return(rt_error("C: camera viewpoint: invalid input", -1));
	// place coordinates in camera
	printf("Camera coordinates = %f, %f, %f\n", coords.x, coords.y, coords.z);
	(void) cam;
	return (0);
}

int	parse_camera(char **tokens, t_world *world)
{
//	float	field_of_view;
//	t_tuple	orientation;

	if (!tokens[1])
		return(rt_error("C: camera coordinates: missing values", -1));
	if (parse_camera_coords(tokens[1], world->cam) != 0)
		return (-1);
//	if (!tokens[2])
//		return(rt_error("A: ambient color: missing values", -1));
//	if (parse_ambient_rgb(tokens[2], world) != 0)
//		return (-1);
//	if (tokens[3])
//		return(rt_error("A: too many arguments", -1));
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
//	t_preworld		preworld;
	static	int		first_line;
	
	(void) tokens;
	(void) data;

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
