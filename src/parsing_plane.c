/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_plane.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:51:51 by hallison          #+#    #+#             */
/*   Updated: 2025/10/02 14:30:29 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_plane_color(char *token, t_shape *s)
{
	t_rgb	col_255;

	col_255 = color(0, 0, 0);
	if (rt_atorgb(token, &col_255) != 0)
		return (rt_error("pl: plane color: invalid input", -1));
	if (!valid_rgb_range(col_255))
		return (rt_error("pl: rgb values must be in range [0,255]", -1));
	s->m->color = color(col_255.r, col_255.g, col_255.b);
	return (0);
}

int	parse_plane_orientation(char *token, t_shape *s)
{
	t_tuple	v;
	float	angle[2];

	v = vector(0, 0, 0);
	if (rt_atof_tuple(token, &v) != 0)
		return (rt_error("pl: plane orient: invalid input", -1));
	if (check_v_normalized(v, "pl: plane orientation") != 0)
		return (-1);
	v = tnorm(v);
	vector_to_rotation(v, angle);
	s->transform = mmultfree(rotation_z(angle[0]), s->transform);
	s->transform = mmultfree(rotation_y(angle[1]), s->transform);
	free_matrix(s->invtrans, 4);
	s->invtrans = minvert(s->transform, 4);
	return (0);
}

int	parse_plane_position(char *token, t_shape *s)
{
	t_tuple	pos;

	pos = point(0, 0, 0);
	if (rt_atof_tuple(token, &pos) != 0)
		return (rt_error("pl: plane position: invalid input", -1));
	s->transform = mmultfree(translation(pos.x, pos.y, pos.z), s->transform);
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
	if (tokens[4] && BONUS == false)
		return (rt_error("pl: Extraneous args", -1));
	return (0);
}

int	parse_plane(char **tokens, t_world *world, int *s_i)
{
	if (mandatory_tokens_found(tokens) != 0)
		return (-1);
	world->s[*s_i] = plane();
	if (!world->s[*s_i])
		return (-1);
	if (parse_plane_color(tokens[3], world->s[*s_i]) != 0)
		return (-1);
	if (parse_plane_orientation(tokens[2], world->s[*s_i]) != 0)
		return (-1);
	if (parse_plane_position(tokens[1], world->s[*s_i]) != 0)
		return (-1);
	if (BONUS == true && tokens[4])
	{
		if (parse_shape_bonus("pl", tokens + 4, world->s[*s_i]) != 0)
			return (-1);
	}
	(*s_i)++;
	return (0);
}
