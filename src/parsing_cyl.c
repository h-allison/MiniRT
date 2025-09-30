/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cyl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:27:53 by hallison          #+#    #+#             */
/*   Updated: 2025/09/30 20:52:15 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_cyl_color(char *token, t_shape *s)
{
	t_rgb	col_255;

	col_255 = color(0, 0, 0);
	if (rt_atorgb(token, &col_255) != 0)
		return (rt_error("cy: cyl color: invalid input", -1));
	if (!valid_rgb_range(col_255))
		return (rt_error("cy: rgb values must be in range [0,255]", -1));
	s->m->color = color(col_255.r, col_255.g, col_255.b);
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
	if (check_v_normalized(v, "cy: cylinder orientation") != 0)
		return (-1);
	vector_to_rotation(v, angle);
	s->transform = mmultfree(rotation_z(angle[0]), s->transform);
	s->transform = mmultfree(rotation_y(angle[1]), s->transform);
	free_matrix(s->invtrans, 4);
	s->invtrans = minvert(s->transform, 4);
	return (0);
}

int	parse_cyl_diam_and_height(char *d_token, char *h_token, t_shape *s)
{
	float	diam;
	float	height;
	float	rad;

	diam = 0;
	if (rt_atof(d_token, &diam) != 0)
		return (rt_error("cy: cyl diam: invalid input", -1));
	rad = diam / 2;
	height = 0;
	if (rt_atof(h_token, &height) != 0)
		return (rt_error("cy: cyl height: invalid input", -1));
	s->transform = mmultfree(scaling(rad, height, rad), s->transform);
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
		return (rt_error("cy: cylinder diam: missing values", -1));
	if (!tokens[4])
		return (rt_error("cy: cylinder height: missing values", -1));
	if (!tokens[5])
		return (rt_error("cy: cylinder color: missing values", -1));
	if (BONUS == false && tokens[6])
	{
		printf("token = %s\n", tokens[4]);
		return (rt_error("cy: Extraneous args", -1));
	}
	return (0);
}

int	parse_cyl(char **tokens, t_world *world, int *s_i)
{
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
	if (parse_cyl_diam_and_height(tokens[3], tokens[4], world->s[*s_i]) != 0)
		return (-1);
	if (parse_cyl_orientation(tokens[2], world->s[*s_i]) != 0)
		return (-1);
	if (parse_cyl_position(tokens[1], world->s[*s_i]) != 0)
		return (-1);
	if (BONUS == true && tokens[6])
	{
		if (parse_shape_bonus("cy", tokens + 6, world->s[*s_i]) != 0)
			return (-1);
	}
	printf("cyl[%i]->specular = %f\n", *s_i, world->s[*s_i]->m->specular);
	(*s_i)++;
	return (0);
}
