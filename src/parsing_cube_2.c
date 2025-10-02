/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cube_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 20:15:00 by hallison          #+#    #+#             */
/*   Updated: 2025/10/02 15:50:17 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_cube_orientation(char *token, t_shape *s)
{
	t_tuple	v;
	float	**transform;

	v = vector(0, 0, 0);
	if (rt_atof_tuple(token, &v) != 0)
		return (rt_error("cb: cube orient: invalid input", -1));
	if (check_v_normalized(v, "cb: cube orientation") != 0)
		return (-1);
	v = tnorm(v);
	transform = object_transform(v);
	s->transform = mmultfree(transform, s->transform);
	free_matrix(s->invtrans, 4);
	s->invtrans = minvert(s->transform, 4);
	return (0);
}

int	parse_cube_position(char *token, t_shape *s)
{
	t_tuple	pos;

	pos = point(0, 0, 0);
	if (rt_atof_tuple(token, &pos) != 0)
		return (rt_error("cb: cube position: invalid input", -1));
	s->transform = mmultfree(translation(pos.x, pos.y, pos.z), s->transform);
	free_matrix(s->invtrans, 4);
	s->invtrans = minvert(s->transform, 4);
	return (0);
}
