/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cyl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:27:53 by hallison          #+#    #+#             */
/*   Updated: 2025/09/29 18:49:14 by hallison         ###   ########.fr       */
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
	float	angle[2];
	
	v = vector(0, 0, 0);
	if (rt_atof_tuple(token, &v) != 0)
		return (rt_error("cy: cylinder orient: invalid input", -1));
	v = tnorm(v);
//	printf("Cyl orientation = %f, %f, %f, %f\n", v.x,
//		v.y, v.z, v.w);
	if (check_v_normalized(v, "cy: cylinder orientation") != 0)
		return (-1);
	vector_to_rotation(v, angle);
	//if (!fisequal(v.x, 0))
	s->transform = mmultfree(rotation_z(angle[0]), s->transform);
	s->transform = mmultfree(rotation_y(angle[1]), s->transform);
	free_matrix(s->invtrans, 4);
	s->invtrans = minvert(s->transform, 4);
	return (0);
}

// TODO went back to using diameter for sphere
// same here?
int	parse_cyl_diameter_and_height(char *d_token, char *h_token, t_shape *s)
{
	float	diameter;
	float	height;

	diameter = 0;
	if (rt_atof(d_token, &diameter) != 0)
		return (rt_error("cy: cyl diameter: invalid input", -1));
//	printf("Cyl diameter = %f\n", diameter);
	height = 0;
	if (rt_atof(h_token, &height) != 0)
		return (rt_error("cy: cyl height: invalid input", -1));
//	printf("Cyl height = %f\n", height);
	s->transform = mmultfree(scaling(diameter / 2 , height, diameter / 2), s->transform);
	free_matrix(s->invtrans, 4);
	s->invtrans = minvert(s->transform, 4);
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
	s->transform = mmultfree(translation(coords.x, coords.y, coords.z), s->transform);
	free_matrix(s->invtrans, 4);
	s->invtrans = minvert(s->transform, 4);
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
	if (mandatory_tokens_found(tokens) != 0)
		return (-1);
	world->s[*s_i] = cylinder();
	world->s[*s_i]->closed = true;
	world->s[*s_i]->minimum = -0.5;
	world->s[*s_i]->maximum = 0.5;
	if (!world->s[*s_i])
		exit(1);
	if (parse_cyl_color(tokens[5], world->s[*s_i]) != 0)
		return (-1);
	if (parse_cyl_diameter_and_height(tokens[3], tokens[4], world->s[*s_i]) != 0)
		return (-1);
	if (parse_cyl_orientation(tokens[2], world->s[*s_i]) != 0)
		return (-1);
	if (parse_cyl_position(tokens[1], world->s[*s_i]) != 0)
		return (-1);
	(*s_i)++;
	cyl_i++;
	if (cyl_i > (world->checklist->count_cyl))
		return (rt_error("parse_cyl: more cyls encountered than counted", -1));
	return (0);
}
