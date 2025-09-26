/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_plane.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:51:51 by hallison          #+#    #+#             */
/*   Updated: 2025/09/25 15:18:14 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_plane_color(char *token, t_shape *s)
{
	t_rgb	col_255;

	col_255 = color(0, 0, 0);
	if (rt_atorgb(token, &col_255) != 0)
		return (rt_error("pl: plane color: invalid input", -1));
//	printf("Plane color rgb = %f, %f, %f\n", col_255.r, col_255.g, col_255.b);
	if (!valid_rgb_range(col_255))
		return (rt_error("pl: rgb values must be in range [0,255]", -1));
	s->m->color = color(col_255.r, col_255.g, col_255.b);
//	printf("Plane color t_rgb = %f, %f, %f\n", s->m->color.r, s->m->color.g, s->m->color.b);
	return (0);
}

// TODO apply normal_v to local_normal_at_plane
int	parse_plane_orientation(char *token, t_shape *s)
{
	t_tuple	v;

	v = vector(0, 0, 0);
	if (rt_atof_tuple(token, &v) != 0)
		return (rt_error("pl: plane orient: invalid input", -1));
//	printf("Plane 3D normalized vector = %f, %f, %f, %f\n", v.x,
//		v.y, v.z, v.w);
	if (check_v_normalized(v, "pl: plane orientation") != 0)
		return (-1);
	s->normal_v = v;
	return (0);
}

int	parse_plane_position(char *token, t_shape *s)
{
	t_tuple	coords;
	float	**translation_matrix;

	coords = point(0, 0, 0);
	if (rt_atof_tuple(token, &coords) != 0)
		return (rt_error("pl: plane position: invalid input", -1));
//	printf("\nPlane position = %f, %f, %f, %f\n", coords.x,
//		coords.y, coords.z, coords.w);
	translation_matrix = translation(coords.x, coords.y, coords.z);
	s->transform = mmultfree(translation_matrix, s->transform);
	free_matrix(s->invtrans, 4);
	s->invtrans = minvert(s->transform, 4);
	return (0);
}

static int	mandatory_tokens_found(char **tokens)
{
	if (!tokens[1])
		return (rt_error("pl: plane coordinates: missing values", -1));
	if (!tokens[2])
		return (rt_error("pl: plane orientation: missing values", -1));
	if (!tokens[3])
		return (rt_error("pl: plane color: missing values", -1));
	if (tokens[4])
		return (rt_error("pl: Extraneous args", -1));
	return (0);
}

// TODO remove pl_i and pl_i check later
int	parse_plane(char **tokens, t_world *world, int *s_i)
{
	static int	pl_i;
	int			i;
	int			(*func[4])(char *tokens, t_shape *shape);
	func[0] = parse_plane_position;
	func[1] = parse_plane_orientation;
	func[2] = parse_plane_color;
	func[3] = NULL;
	if (mandatory_tokens_found(tokens) != 0)
		return (-1);
//	i = 0;
	world->s[*s_i] = plane();
	if (!world->s[*s_i])
		exit(1);
	i = 2;
	while (i >= 0)
	{
		if (func[i](tokens[i + 1], world->s[*s_i]) != 0)
			return (-1);
		i--;
	}
	/*
	while (func[i])
	{
		if (func[i](tokens[i + 1], world->s[*s_i]) != 0)
			return (-1);
		i++;
	}
	*/
	(*s_i)++;
	pl_i++;
	if (pl_i > (world->checklist->count_plane))
		return (rt_error("parse_plane: more planes encountered than counted", -1));
	return (0);
}
