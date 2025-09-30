/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cube.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:27:53 by hallison          #+#    #+#             */
/*   Updated: 2025/09/30 16:50:01 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_cube_color(char *token, t_shape *s)
{
	t_rgb	col_255;

	col_255 = color(0, 0, 0);
	if (rt_atorgb(token, &col_255) != 0)
		return (rt_error("cb: cube color: invalid input", -1));
	if (!valid_rgb_range(col_255))
		return (rt_error("cb: rgb values must be in range [0,255]", -1));
	s->m->color = color(col_255.r, col_255.g, col_255.b);
	return (0);
}

int	parse_cube_diam_and_height(char *d_token, char *h_token, t_shape *s)
{
	float	diam;
	float	ht;
	float	rad;

	diam = 0;
	if (rt_atof(d_token, &diam) != 0)
		return (rt_error("cb: cube diameter: invalid input", -1));
	rad = diam / 2;
	ht = 0;
	if (rt_atof(h_token, &ht) != 0)
		return (rt_error("cb: cube height: invalid input", -1));
	s->transform = mmultfree(scaling(rad, rad, rad), s->transform);
	free_matrix(s->invtrans, 4);
	s->invtrans = minvert(s->transform, 4);
	return (0);
}

static int	mandatory_tokens_found(char **tokens)
{
	if (!tokens[1])
		return (rt_error("cb: cube coordinates: missing values", -1));
	if (!tokens[2])
		return (rt_error("cb: cube orientation: missing values", -1));
	if (!tokens[3])
		return (rt_error("cb: cube diameter: missing values", -1));
	if (!tokens[4])
		return (rt_error("cb: cube height: missing values", -1));
	if (!tokens[5])
		return (rt_error("cb: cube color: missing values", -1));
	if (tokens[6])
	{
		printf("token = %s\n", tokens[4]);
		return (rt_error("cube: Extraneous args", -1));
	}
	return (0);
}

// TODO remove cube_i check later
int	parse_cube(char **tokens, t_world *world, int *s_i)
{
	static int	cube_i;

	if (mandatory_tokens_found(tokens) != 0)
		return (-1);
	world->s[*s_i] = cube();
	if (!world->s[*s_i])
		exit(1);
	if (parse_cube_color(tokens[5], world->s[*s_i]) != 0)
		return (-1);
	if (parse_cube_diam_and_height(tokens[3], tokens[4], world->s[*s_i]) != 0)
		return (-1);
	if (parse_cube_orientation(tokens[2], world->s[*s_i]) != 0)
		return (-1);
	if (parse_cube_position(tokens[1], world->s[*s_i]) != 0)
		return (-1);
	(*s_i)++;
	cube_i++;
	if (cube_i > (world->checklist->count_cube))
		return (rt_error("parse_cube: more cubes than counted", -1));
	return (0);
}
