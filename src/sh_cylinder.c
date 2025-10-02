/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:49:31 by mmillhof          #+#    #+#             */
/*   Updated: 2025/10/02 11:27:22 by mmillhof         ###   ########.fr       */
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

static bool	check_cap(t_ray r, float t)
{
	float	x;
	float	z;

	x = r.origin.x + t * r.direction.x;
	z = r.origin.z + t * r.direction.z;
	return ((x * x + z * z) < 1 + EPSILON);
}

static void	intersect_caps(t_shape *cyl, t_intersection *xs, t_ray r)
{
	float	t;

	(void)xs;
	if (!cyl->closed || fisequal(r.direction.y, 0))
		return ;
	t = (cyl->minimum - r.origin.y) / r.direction.y;
	if (check_cap(r, t))
		xs = intersections(intersection(t, cyl), intersection(t, cyl));
	t = (cyl->maximum - r.origin.y) / r.direction.y;
	if (check_cap(r, t))
		xs = intersections(intersection(t, cyl), intersection(t, cyl));
	return ;
}

static bool calc_xs_cyl(t_abc abc, t_shape *s, t_ray r, t_intersection *xs)
{
	float			disc;
	float			t0;
	float			t1;
	float			y0;
	float			y1;
	
	abc.b = 2 * r.origin.x * r.direction.x
		+ 2 * r.origin.z * r.direction.z;
	abc.c = r.origin.x * r.origin.x
		+ r.origin.z * r.origin.z - 1;
	disc = abc.b * abc.b - 4 * abc.a * abc.c;
	if (disc < 0)
		return (1);
	t0 = (-abc.b - sqrtf(disc)) / (2 * abc.a);
	t1 = (-abc.b + sqrtf(disc)) / (2 * abc.a);
	if (t0 > t1)
		swapf(&t0, &t1);
	y0 = r.origin.y + t0 * r.direction.y;
	if ((s->minimum) < y0 && y0 < s->maximum)
		xs = intersections(intersection(t0, s), intersection(t0, s));
	y1 = r.origin.y + t1 * r.direction.y;
	if (s->minimum < y1 && y1 < s->maximum)
		xs = intersections(intersection(t1, s), intersection(t1, s));
	return (0);
}

t_intersection	*local_intersect_cyl(t_shape *s, t_ray r)
{
	t_intersection	*xs;
	t_abc			abc;

	abc.a = r.direction.x * r.direction.x
		+ r.direction.z * r.direction.z;
	xs = intersections(intersection(0, NULL), intersection(0, NULL));
	if (!fisequal(abc.a, 0))
		if (calc_xs_cyl(abc, s, r, xs))
			return (xs);
	intersect_caps(s, xs, r);
	return (xs);
}
