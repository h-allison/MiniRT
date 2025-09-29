/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:27:53 by hallison          #+#    #+#             */
/*   Updated: 2025/09/29 20:09:10 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_cone_color(char *token, t_shape *s)
{
	t_rgb	col_255;

	col_255 = color(0, 0, 0);
	if (rt_atorgb(token, &col_255) != 0)
		return (rt_error("cn: cone color: invalid input", -1));
	if (!valid_rgb_range(col_255))
		return (rt_error("cn: rgb values must be in range [0,255]", -1));
	s->m->color = color(col_255.r, col_255.g, col_255.b);
	return (0);
}

int	parse_cone_diam_and_height(char *d_token, char *h_token, t_shape *s)
{
	float	diameter;
	float	height;

	diameter = 0;
	if (rt_atof(d_token, &diameter) != 0)
		return (rt_error("cn: cone diameter: invalid input", -1));
	height = 0;
	if (rt_atof(h_token, &height) != 0)
		return (rt_error("cn: cone height: invalid input", -1));
	s->transform = mmultfree(scaling(diameter, height, diameter), s->transform);
	free_matrix(s->invtrans, 4);
	s->invtrans = minvert(s->transform, 4);
	return (0);
}

static int	mandatory_tokens_found(char **tokens)
{
	if (!tokens[1])
		return (rt_error("cn: cone coordinates: missing values", -1));
	if (!tokens[1])
		return (rt_error("cn: cone coordinates: missing values", -1));
	if (!tokens[2])
		return (rt_error("cn: cone orientation: missing values", -1));
	if (!tokens[3])
		return (rt_error("cn: cone diameter: missing values", -1));
	if (!tokens[4])
		return (rt_error("cn: cone height: missing values", -1));
	if (!tokens[5])
		return (rt_error("cn: cone color: missing values", -1));
	return (0);
}

int	set_cone_min_max(char **tokens, t_shape *s)
{
	float	min;
	float	max;

	if (tokens[6] && tokens[7])
	{
		if (rt_atof(tokens[6], &min) != 0)
			return (rt_error("cn: cone minimum: invalid input", -1));
		if (rt_atof(tokens[7], &max) != 0)
			return (rt_error("cn: cone maximum: invalid input", -1));
		s->minimum = min;
		s->maximum = max;
	}
	else
	{
		s->minimum = -0.5;
		s->maximum = 0.5;
	}
	return (0);
}

// TODO remove cone_i and cone_i check later
int	parse_cone(char **tokens, t_world *world, int *s_i)
{
	static int	cone_i;

	if (mandatory_tokens_found(tokens) != 0)
		return (-1);
	world->s[*s_i] = cone();
	world->s[*s_i]->closed = true;
	if (!world->s[*s_i])
		exit(1);
	if (set_cone_min_max(tokens, world->s[*s_i]) != 0)
		return (-1);
	if (parse_cone_color(tokens[5], world->s[*s_i]) != 0)
		return (-1);
	if (parse_cone_diam_and_height(tokens[3], tokens[4], world->s[*s_i]) != 0)
		return (-1);
	if (parse_cone_orientation(tokens[2], world->s[*s_i]) != 0)
		return (-1);
	if (parse_cone_position(tokens[1], world->s[*s_i]) != 0)
		return (-1);
	(*s_i)++;
	cone_i++;
	if (cone_i > (world->checklist->count_cone))
		return (rt_error("parse_cone: more cones parsed than counted", -1));
	return (0);
}
