/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:37:09 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/27 20:55:24 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape	*triangle(t_tuple p1, t_tuple p2, t_tuple p3)
{
	t_tri	*tri;
	t_shape	*t;
	
	tri = malloc(sizeof(t_tri));
	tri->p1 = p1;
	tri->p2 = p2;
	tri->p3 = p3;
	tri->e1 = tsub(p2, p1);
	tri->e2 = tsub(p3, p1);
	tri->normal = tnorm(cross(tri->e2, tri->e1));
	t = malloc(sizeof(t_shape));
	t->parent = NULL;
	t->group = NULL;
	t->triangle = tri;
	t->transform = create_id_matrix();
	t->invtrans = minvert(t->transform, 4);
	t->local_normal_at = local_normal_at_triangle;
	t->local_intersect = local_intersect_triangle;
	t->m = material();
	return (t);
}

t_tuple	local_normal_at_triangle(t_shape *s, t_tuple local_point)
{
	(void)s;
	(void)local_point;
	return (s->triangle->normal);
}

t_intersection	*local_intersect_triangle(t_shape *t, t_ray r)
{
	t_intersection	*xs;
	t_tuple			dir_cross_e2;
	t_tuple			p1_to_origin;
	t_tuple			origin_cross_e1;
	float			det;
	float			f;
	float			u;
	float			v;
	float			xt;

	dir_cross_e2 = cross(r.direction, t->triangle->e2);
	det = dot(t->triangle->e1, dir_cross_e2);
	xs = intersections(intersection(0, NULL), intersection(0, NULL));
	if (fabs(det) < EPSILON)
		return (xs);
	f = 1.0 / det;	
	p1_to_origin = tsub(r.origin, t->triangle->p1);
	u = f * dot(p1_to_origin, dir_cross_e2);
	if (u < 0 || u > 1)
		return (xs);
	origin_cross_e1 = cross(p1_to_origin, t->triangle->e1);
	v = f * dot(r.direction, origin_cross_e1);
	if (v < 0 || u + v > 1)
		return (xs);
	xt = f * dot(t->triangle->e2, origin_cross_e1);
	return (intersections(intersection(xt, t), intersection(xt, t)));
}
