/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_sphere.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:51:51 by hallison          #+#    #+#             */
/*   Updated: 2025/09/30 20:51:13 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_sphere_color(char *token, t_shape *s)
{
	t_rgb	col_255;

	col_255 = color(0, 0, 0);
	if (rt_atorgb(token, &col_255) != 0)
		return (rt_error("sp: sphere color: invalid input", -1));
	if (!valid_rgb_range(col_255))
		return (rt_error("sp: rgb values must be in range [0,255]", -1));
	s->m->color = color(col_255.r, col_255.g, col_255.b);
	return (0);
}

int	parse_sphere_diameter(char *token, t_shape *s)
{
	float	diameter;
	float	rad;

	diameter = 0;
	if (rt_atof(token, &diameter) != 0)
		return (rt_error("sp: sphere diameter: invalid input", -1));
	rad = diameter / 2;
	s->transform = mmultfree(scaling(rad, rad, rad), s->transform);
	free_matrix(s->invtrans, 4);
	s->invtrans = minvert(s->transform, 4);
	return (0);
}

int	parse_sphere_position(char *token, t_shape *s)
{
	t_tuple	pos;

	pos = point(0, 0, 0);
	if (rt_atof_tuple(token, &pos) != 0)
		return (rt_error("sp: sphere position: invalid input", -1));
	s->transform = mmultfree(translation(pos.x, pos.y, pos.z), s->transform);
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
	if (BONUS == false && tokens[4])
	{
		printf("token = %s\n", tokens[4]);
		return (rt_error("sp: Extraneous args", -1));
	}
	return (0);
}

int	parse_sphere(char **tokens, t_world *world, int *s_i)
{
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
	if (BONUS == true && tokens[4])
	{
		if (parse_shape_bonus("sp", tokens + 4, world->s[*s_i]) != 0)
			return (-1);
	}
	printf("sphere[%i]->specular = %f\n", *s_i, world->s[*s_i]->m->specular);
	(*s_i)++;
	return (0);
}
