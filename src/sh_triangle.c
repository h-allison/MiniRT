/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_triangle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:37:09 by mmillhof          #+#    #+#             */
/*   Updated: 2025/10/02 12:54:06 by mmillhof         ###   ########.fr       */
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

static void	calc_xs_tri(t_tuple dir_cross_e2, t_shape *t, t_ray r,
		t_intersection *xs)
{
	t_tuple			p1_to_origin;
	t_tuple			origin_cross_e1;
	t_abc			abc;
	float			det;
	float			xt;

	det = dot(t->triangle->e1, dir_cross_e2);
	if (fabs(det) < EPSILON)
		return ;
	abc.a = 1.0 / det;
	p1_to_origin = tsub(r.origin, t->triangle->p1);
	abc.b = abc.a * dot(p1_to_origin, dir_cross_e2);
	if (abc.b < 0 || abc.b > 1)
		return ;
	origin_cross_e1 = cross(p1_to_origin, t->triangle->e1);
	abc.c = abc.a * dot(r.direction, origin_cross_e1);
	if (abc.c < 0 || abc.b + abc.c > 1)
		return ;
	xt = abc.a * dot(t->triangle->e2, origin_cross_e1);
	xs = intersections(intersection(xt, t), intersection(xt, t));
	return ;
}

t_intersection	*local_intersect_triangle(t_shape *t, t_ray r)
{
	t_intersection	*xs;
	t_tuple			dir_cross_e2;

	xs = intersections(intersection(0, NULL), intersection(0, NULL));
	dir_cross_e2 = cross(r.direction, t->triangle->e2);
	calc_xs_tri(dir_cross_e2, t, r, xs);
	return (xs);
}
