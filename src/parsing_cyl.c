/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cyl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:27:53 by hallison          #+#    #+#             */
/*   Updated: 2025/09/24 15:16:47 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minirt.h"

int	parse_cyl_color(char *token, t_shape *s)
{
	t_rgb	col_255;

	col_255 = color(0, 0, 0);
	if (rt_atorgb(token, &col_255) != 0)
		return (rt_error("cy: cyl color: invalid input", -1));
//	printf("Sphere color rgb = %f, %f, %f\n", col_255.r, col_255.g, col_255.b);
	if (!valid_rgb_range(col_255))
		return (rt_error("cy: rgb values must be in range [0,255]", -1));
	s->m->color = color(col_255.r, col_255.g, col_255.b);
//	printf("Sphere color t_rgb = %f, %f, %f\n", s->m->color.r, s->m->color.g, s->m->color.b);
	return (0);
}

int	parse_cyl_orientation(char *token, t_shape *s)
{
	t_tuple	v;
	
	v = vector(0, 0, 0);
	if (rt_atof_tuple(token, &v) != 0)
		return (rt_error("cy: cylinder orient: invalid input", -1));
//	printf("Plane orientation = %f, %f, %f, %f\n", v.x,
//		v.y, v.z, v.w);
	if (!btwn_negative_and_positive_1(v))
		return (rt_error("cy: cylinder orientation: must be in range [-1.0, 1.0]", -1));
//	set_transform(s, translation(s, v));
	// TODO set rotation - should it be v.x / 180 passed to rotation_x() etc?
	(void) s;
	return (0);
}

int	parse_cyl_height(char *token, t_shape *s)
{
	float	height;
	
	height = 0;
	if (rt_atof(token, &height) != 0)
		return (rt_error("cy: cyl height: invalid input", -1));
//	printf("Cyl height = %f\n", height);
	set_transform(s, scaling(1, height, 1));
	return (0);
}

int	parse_cyl_diameter(char *token, t_shape *s)
{
	float	diameter;
	
	diameter = 0;
	if (rt_atof(token, &diameter) != 0)
		return (rt_error("cy: cyl diameter: invalid input", -1));
//	printf("Cyl diameter = %f\n", diameter);
	set_transform(s, scaling(diameter, 1, diameter));
	return (0);
}

int	parse_cyl_position(char *token, t_shape *s)
{
	t_tuple	coords;
	coords = point(0, 0, 0);
	if (rt_atof_tuple(token, &coords) != 0)
		return (rt_error("cy: cylinder position: invalid input", -1));
//	printf("\nCyl position = %f, %f, %f, %f\n", coords.x,
//		coords.y, coords.z, coords.w);
	set_transform(s, translation(coords.x, coords.y, coords.z));
	return (0);
}

static int	mandatory_tokens_found(char **tokens)
{
	if (!tokens[1])
		return (rt_error("cy: cylinder coordinates: missing values", -1));
	if (!tokens[2])
		return (rt_error("cy: cylinder orientation: missing values", -1));
	if (!tokens[3])
		return (rt_error("cy: cylinder diameter: missing values", -1));
	if (!tokens[4])
		return (rt_error("cy: cylinder height: missing values", -1));
	if (!tokens[5])
		return (rt_error("cy: cylinder color: missing values", -1));
	if (tokens[6])
	{
		printf("token = %s\n", tokens[4]);
		return (rt_error("cy: Extraneous args", -1));
	}
	return (0);
}

// TODO remove cyl_i and cyl_i check later
int	parse_cyl(char **tokens, t_world *world, int *s_i)
{
	static int	cyl_i;
	int			i;
	int			(*func[6])(char *tokens, t_shape *shape);
	func[0] = parse_cyl_position;
	func[1] = parse_cyl_orientation;
	func[2] = parse_cyl_diameter;
	func[3] = parse_cyl_height;
	func[4] = parse_cyl_color;
	func[5] = NULL;
	if (mandatory_tokens_found(tokens) != 0)
		return (-1);
	i = 0;
	world->s[*s_i] = cylinder();
	if (!world->s[*s_i])
		exit(1);
	while (func[i])
	{
		if (func[i](tokens[i + 1], world->s[*s_i]) != 0)
			return (-1);
		i++;
	}
	(*s_i)++;
	cyl_i++;
	if (cyl_i > (world->checklist->count_cyl))
		return (rt_error("parse_cyl: more cyls encountered than counted", -1));
	return (0);
}
