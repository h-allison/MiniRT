/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:49:31 by mmillhof          #+#    #+#             */
/*   Updated: 2025/10/02 11:32:30 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape	*cylinder(void)
{
	t_shape	*s;

	s = malloc(sizeof(t_shape));
	s->parent = NULL;
	s->group = NULL;
	s->triangle = NULL;
	s->transform = create_id_matrix();
	s->invtrans = minvert(s->transform, 4);
	s->local_normal_at = local_normal_at_cyl;
	s->local_intersect = local_intersect_cyl;
	s->m = material();
	s->minimum = -FLT_MAX;
	s->maximum = FLT_MAX;
	s->closed = false;
	return (s);
}

t_tuple	local_normal_at_cyl(t_shape *s, t_tuple local_point)
{
	float	dist;

	(void)s;
	dist = local_point.x * local_point.x + local_point.z * local_point.z;
	if (dist < 1 && local_point.y >= s->maximum - EPSILON)
		return (vector(0, 1, 0));
	else if (dist < 1 && local_point.y <= s->minimum + EPSILON)
		return (vector(0, -1, 0));
	return (vector(local_point.x, 0, local_point.z));
}
