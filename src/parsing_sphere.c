/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_sphere.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:51:51 by hallison          #+#    #+#             */
/*   Updated: 2025/09/24 14:15:09 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_sphere_color(char *token, t_shape *s)
{
	t_rgb	col_255;

	col_255 = color(0, 0, 0);
	if (rt_atorgb(token, &col_255) != 0)
		return (rt_error("sp: sphere color: invalid input", -1));
//	printf("Sphere color rgb = %f, %f, %f\n", col_255.r, col_255.g, col_255.b);
	if (!valid_rgb_range(col_255))
		return (rt_error("sp: rgb values must be in range [0,255]", -1));
	s->m->color = color(col_255.r, col_255.g, col_255.b);
//	printf("Sphere color t_rgb = %f, %f, %f\n", s->m->color.r, s->m->color.g, s->m->color.b);
	return (0);
}

int	parse_sphere_diameter(char *token, t_shape *s)
{
	float	diameter;
	
	diameter = 0;
	if (rt_atof(token, &diameter) != 0)
		return (rt_error("sp: sphere diameter: invalid input", -1));
//	printf("Sphere diameter = %f\n", diameter);
	set_transform(s, scaling(diameter, diameter, diameter));
	return (0);
}

int	parse_sphere_position(char *token, t_shape *s)
{
	t_tuple	coords;
	coords = point(0, 0, 0);
	if (rt_atof_tuple(token, &coords) != 0)
		return (rt_error("sp: sphere position: invalid input", -1));
//	printf("\nSphere position = %f, %f, %f, %f\n", coords.x,
//		coords.y, coords.z, coords.w);
	set_transform(s, translation(coords.x, coords.y, coords.z));
	return (0);
}

static int	mandatory_tokens_found(char **tokens)
{
	if (!tokens[1])
		return (rt_error("sp: sphere coordinates: missing values", -1));
	if (!tokens[2])
		return (rt_error("sp: sphere diameter: missing values", -1));
	if (!tokens[3])
		return (rt_error("sp: sphere color: missing values", -1));
	if (tokens[4])
	{
		printf("token = %s\n", tokens[4]);
		return (rt_error("sp: Extraneous args", -1));
	}
	return (0);
}

// TODO remove pl_i and pl_i check later
int	parse_sphere(char **tokens, t_world *world, int *s_i)
{
	static int	sp_i;
	int			i;
	int			(*func[4])(char *tokens, t_shape *shape);
	func[0] = parse_sphere_position;
	func[1] = parse_sphere_diameter;
	func[2] = parse_sphere_color;
	func[3] = NULL;
	if (mandatory_tokens_found(tokens) != 0)
		return (-1);
	i = 0;
	world->s[*s_i] = sphere();
	if (!world->s[*s_i])
		exit(1);
	while (func[i])
	{
		if (func[i](tokens[i + 1], world->s[*s_i]) != 0)
			return (-1);
		i++;
	}
	(*s_i)++;
	sp_i++;
	if (sp_i > (world->checklist->count_sphere))
		return (rt_error("parse_sphere: more spheres encountered than counted", -1));
	return (0);
}
