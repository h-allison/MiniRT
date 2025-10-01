/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cone.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:49:31 by mmillhof          #+#    #+#             */
/*   Updated: 2025/10/01 23:27:47 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape	*cone(void)
{
	t_shape	*s;

	s = malloc(sizeof(t_shape));
	s->parent = NULL;
	s->group = NULL;
	s->triangle = NULL;
	s->transform = create_id_matrix();
	s->invtrans = minvert(s->transform, 4);
	s->local_normal_at = local_normal_at_cone;
	s->local_intersect = local_intersect_cone;
	s->m = material();
	s->minimum = -FLT_MAX;
	s->maximum = FLT_MAX;
	s->closed = false;
	return (s);
}

t_tuple	local_normal_at_cone(t_shape *s, t_tuple local_point)
{
	float	dist;
	float	y;

	(void)s;
	dist = local_point.x * local_point.x + local_point.z * local_point.z;
	if (dist <= 1 && local_point.y >= s->maximum - EPSILON)
		return (vector(0, 1, 0));
	else if (dist <= 1 && local_point.y <= s->minimum + EPSILON)
		return (vector(0, -1, 0));
	y = sqrtf(dist);
	y *= -(local_point.y > 0);
	return (vector(local_point.x, y, local_point.z));
}
