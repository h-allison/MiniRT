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

// 27.09 Switched back to diameter from radius - This matches our previous default_world()
int	parse_sphere_diameter(char *token, t_shape *s)
{
	float	diameter;
//	float	radius;
	
	diameter = 0;
	if (rt_atof(token, &diameter) != 0)
		return (rt_error("sp: sphere diameter: invalid input", -1));
//	radius = diameter / 2;
//	printf("Sphere radius = %f\n", radius);
//	s->transform = mmultfree(scaling(radius, radius, radius), s->transform);
	s->transform = mmultfree(scaling(diameter, diameter, diameter), s->transform);
	free_matrix(s->invtrans, 4);
	s->invtrans = minvert(s->transform, 4);
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
	s->transform = mmultfree(translation(coords.x, coords.y, coords.z), s->transform);
	free_matrix(s->invtrans, 4);
	s->invtrans = minvert(s->transform, 4);
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
	if (mandatory_tokens_found(tokens) != 0)
		return (-1);
	world->s[*s_i] = sphere();
	if (!world->s[*s_i])
		exit(1);
	if (parse_sphere_color(tokens[3], world->s[*s_i]) != 0)
		return (-1);
	if (parse_sphere_diameter(tokens[2], world->s[*s_i]) != 0)
		return (-1);
	if (parse_sphere_position(tokens[1], world->s[*s_i]) != 0)
		return (-1);
	(*s_i)++;
	sp_i++;
	if (sp_i > (world->checklist->count_sphere))
		return (rt_error("parse_sphere: more spheres encountered than counted", -1));
	return (0);
}
