/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:49:31 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/29 18:13:37 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape	*plane(void)
{
	t_shape	*s;

	s = malloc(sizeof(t_shape));
	s->parent = NULL;
	s->group = NULL;
	s->triangle = NULL;
	s->transform = create_id_matrix();
	s->invtrans = minvert(s->transform, 4);
	s->local_normal_at = local_normal_at_plane;
	s->local_intersect = local_intersect_plane;
	s->m = material();
	return (s);
}

t_tuple	local_normal_at_plane(t_shape *s, t_tuple local_point)
{
	(void)s;
	(void)local_point;
	return (vector(0, 1, 0));
}

t_intersection	*local_intersect_plane(t_shape *s, t_ray r)
{
	t_intersection	*xs;
	float			t;

	if (fabs(r.direction.y) < EPSILON)
		xs = intersections(intersection(0, NULL), intersection(0, NULL));
	else
	{
		t = -r.origin.y / r.direction.y;
		xs = intersections(intersection(t, s), intersection(0, NULL));
	}
	return (xs);
}

