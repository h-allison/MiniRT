/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:51:51 by hallison          #+#    #+#             */
/*   Updated: 2025/10/01 18:30:14 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


// TODO Should not seg fault if camera orientation is wrong
// TODO malloc exit
// TODO if c_orient == default up, change something
t_camera	*place_camera(t_tuple c_coords, t_tuple c_orient, float fov)
{
	t_camera	*cam;
	t_tuple		to;
	t_tuple		up;

	cam = camera(WIN_WIDTH, WIN_HEIGHT, DEG2RAD * fov);
	if (!cam)
		exit (1);
	to = tadd(c_coords, c_orient);
	up = vector(0, 1, 0);
	free_matrix(cam->transform, 4);
	cam->transform = view_transform(c_coords, to, up);
	return (cam);
}

// TODO protect NULL return
t_camera	*place_camera_2(t_tuple c_coords, t_tuple c_orient, float fov)
{
	t_camera	*cam;
	float		angle[2];
//	float		**inverted_transform;

//	c_orient = tmult(c_orient, -1);
	cam = camera(WIN_WIDTH, WIN_HEIGHT, DEG2RAD * fov);
	if (!cam)
		exit (1);
	vector_to_rotation(c_orient, angle);
	cam->transform = view_transform(point(0, 0, 0), point(0, 0, 1), vector(0, 1, 0));

	printf("\nBEFORE rotating, camera transform matrix:\n");
	debug_print_matrix(cam->transform);
	printf("\nangle[0] = %f\n", angle[0]);
	printf("angle[1] = %f\n", angle[1]);
	cam->transform = mmultfree(translation(c_coords.x, c_coords.y, c_coords.z), cam->transform);
	cam->transform = mmultfree(rotation_z(angle[0]), cam->transform);
	cam->transform = mmultfree(rotation_y(angle[1]), cam->transform);
//	inverted_transform = minvert(cam->transform, 4);
//	free_matrix(cam->transform, 4);
//	cam->transform = inverted_transform;
	(void)c_coords;
	(void)c_orient;
	return (cam);
}

int	parse_camera_fov(char *token, float *fov)
{
	if (rt_atof(token, fov) != 0)
		return (rt_error("C: field of view: invalid input", -1));
	if (*fov < 0 || *fov > 180)
		return (rt_error("C: field of view: must be in range [0, 180]", -1));
	return (0);
}

static int	mandatory_tokens_found(char **tokens)
{
	if (!tokens[1])
		return (rt_error("C: camera coordinates: missing values", -1));
	if (!tokens[2])
		return (rt_error("C: camera diameter: missing values", -1));
	if (!tokens[3])
		return (rt_error("C: camera color: missing values", -1));
	if (tokens[4])
	{
		printf("token = %s\n", tokens[4]);
		return (rt_error("sp: Extraneous args", -1));
	}
	return (0);
}

int	parse_camera(char **tokens, t_data *data)
{
	t_tuple	coords;
	t_tuple	orient;
	float	field_of_view;

	coords = point(0, 0, 0);
	orient = vector(0, 0, 0);
	field_of_view = 0;
	if (mandatory_tokens_found(tokens) != 0)
		return (-1);
	if (rt_atof_tuple(tokens[1], &coords) != 0)
		return (rt_error("C: camera viewpoint: invalid input", -1));
	if (rt_atof_tuple(tokens[2], &orient) != 0)
		return (rt_error("C: camera orientation: invalid input", -1));
	if (check_v_normalized(orient, "C: camera orientation") != 0)
		return (-1);
	orient = tnorm(orient);
	if (parse_camera_fov(tokens[3], &field_of_view) != 0)
		return (-1);
	orient = tnorm(orient);
	data->cam = place_camera_2(coords, orient, field_of_view);
	printf("\ncamera transform matrix:\n");
	debug_print_matrix(data->cam->transform);
	printf("\n");
	return (0);
}
